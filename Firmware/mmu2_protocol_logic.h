#pragma once
#include <stdint.h>
#include <avr/pgmspace.h>
// #include <array> //@@TODO Don't we have STL for AVR somewhere?
template<typename T, uint8_t N>
class array {
    T data[N];
public:
    array() = default;
    inline constexpr T* begin()const { return data; }
    inline constexpr T* end()const { return data + N; }
    static constexpr uint8_t size() { return N; }
    inline T &operator[](uint8_t i){
        return data[i];
    }
};

#include "mmu2/error_codes.h"
#include "mmu2/progress_codes.h"
#include "mmu2/buttons.h"
#include "mmu2_protocol.h"

#include "mmu2_serial.h"

/// New MMU2 protocol logic
namespace MMU2 {

using namespace modules::protocol;

class ProtocolLogic;

/// ProtocolLogic stepping statuses
enum StepStatus : uint_fast8_t {
    Processing = 0,
    MessageReady, ///< a message has been successfully decoded from the received bytes
    Finished, ///< Scope finished successfully
    Interrupted, ///< received "Finished" message related to a different command than originally issued (most likely the MMU restarted while doing something)
    CommunicationTimeout, ///< the MMU failed to respond to a request within a specified time frame
    ProtocolError,        ///< bytes read from the MMU didn't form a valid response
    CommandRejected,      ///< the MMU rejected the command due to some other command in progress, may be the user is operating the MMU locally (button commands)
    CommandError,         ///< the command in progress stopped due to unrecoverable error, user interaction required
    VersionMismatch,      ///< the MMU reports its firmware version incompatible with our implementation
    CommunicationRecovered,
    ButtonPushed, ///< The MMU reported the user pushed one of its three buttons.
};

static constexpr uint32_t linkLayerTimeout = 2000;                 ///< default link layer communication timeout
static constexpr uint32_t dataLayerTimeout = linkLayerTimeout * 3; ///< data layer communication timeout
static constexpr uint32_t heartBeatPeriod = linkLayerTimeout / 2;  ///< period of heart beat messages (Q0)

static_assert(heartBeatPeriod < linkLayerTimeout && linkLayerTimeout < dataLayerTimeout, "Incorrect ordering of timeouts");

///< Filter of short consecutive drop outs which are recovered instantly
class DropOutFilter {
    StepStatus cause;
    uint8_t occurrences;
public:
    static constexpr uint8_t maxOccurrences = 10; // ideally set this to >8 seconds -> 12x heartBeatPeriod
    static_assert(maxOccurrences > 1, "we should really silently ignore at least 1 comm drop out if recovered immediately afterwards");
    DropOutFilter() = default;

    /// @returns true if the error should be reported to higher levels (max. number of consecutive occurrences reached)
    bool Record(StepStatus ss);

    /// @returns the initial cause which started this drop out event
    inline StepStatus InitialCause() const { return cause; }

    /// Rearms the object for further processing - basically call this once the MMU responds with something meaningful (e.g. S0 A2)
    inline void Reset() { occurrences = maxOccurrences; }
};

/// Logic layer of the MMU vs. printer communication protocol
class ProtocolLogic {
public:
    ProtocolLogic(MMU2Serial *uart, uint8_t extraLoadDistance);

    /// Start/Enable communication with the MMU
    void Start();

    /// Stop/Disable communication with the MMU
    void Stop();

    // Issue commands to the MMU
    void ToolChange(uint8_t slot);
    void Statistics();
    void UnloadFilament();
    void LoadFilament(uint8_t slot);
    void EjectFilament(uint8_t slot);
    void CutFilament(uint8_t slot);
    void ResetMMU();
    void Button(uint8_t index);
    void Home(uint8_t mode);
    void ReadRegister(uint8_t address);
    void WriteRegister(uint8_t address, uint16_t data);

    /// Sets the extra load distance to be reported to the MMU.
    /// Beware - this call doesn't send anything to the MMU.
    /// The MMU gets the newly set value either by a communication restart or via an explicit WriteRegister call
    inline void PlanExtraLoadDistance(uint8_t eld_mm){
        initRegs8[0] = eld_mm;
    }
    /// @returns the currently preset extra load distance
    inline uint8_t ExtraLoadDistance()const {
        return initRegs8[0];
    }

    /// Step the state machine
    StepStatus Step();

    /// @returns the current/latest error code as reported by the MMU
    ErrorCode Error() const { return errorCode; }

    /// @returns the current/latest process code as reported by the MMU
    ProgressCode Progress() const { return progressCode; }

    /// @returns the current/latest button code as reported by the MMU
    Buttons Button() const { return buttonCode; }

    uint8_t CommandInProgress() const;

    inline bool Running() const {
        return state == State::Running;
    }

    inline bool FindaPressed() const {
        return regs8[0];
    }

    inline uint16_t FailStatistics() const {
        return regs16[0];
    }

    inline uint8_t MmuFwVersionMajor() const {
        return mmuFwVersion[0];
    }

    inline uint8_t MmuFwVersionMinor() const {
        return mmuFwVersion[1];
    }

    inline uint8_t MmuFwVersionRevision() const {
        return mmuFwVersion[2];
    }
#ifndef UNITTEST
private:
#endif
    StepStatus ExpectingMessage();
    void SendMsg(RequestMsg rq);
    void SendWriteMsg(RequestMsg rq);
    void SwitchToIdle();
    StepStatus SuppressShortDropOuts(const char *msg_P, StepStatus ss);
    StepStatus HandleCommunicationTimeout();
    StepStatus HandleProtocolError();
    bool Elapsed(uint32_t timeout) const;
    void RecordUARTActivity();
    void RecordReceivedByte(uint8_t c);
    void FormatLastReceivedBytes(char *dst);
    void FormatLastResponseMsgAndClearLRB(char *dst);
    void LogRequestMsg(const uint8_t *txbuff, uint8_t size);
    void LogError(const char *reason_P);
    void LogResponse();
    StepStatus SwitchFromIdleToCommand();
    void SwitchFromStartToIdle();

    enum class State : uint_fast8_t {
        Stopped,      ///< stopped for whatever reason
        InitSequence, ///< initial sequence running
        Running       ///< normal operation - Idle + Command processing
    };

    // individual sub-state machines - may be they can be combined into a union since only one is active at once
    // or we can blend them into ProtocolLogic at the cost of a less nice code (but hopefully shorter)
//    Stopped stopped;
//    StartSeq startSeq;
//    DelayedRestart delayedRestart;
//    Idle idle;
//    Command command;
//    ProtocolLogicPartBase *currentState; ///< command currently being processed
    
    enum class Scope : uint_fast8_t {
        Stopped,
        StartSeq,
        DelayedRestart,
        Idle,
        Command
    };
    Scope currentScope;

    // basic scope members
    /// @returns true if the state machine is waiting for a response from the MMU
    bool ExpectsResponse() const { return ((uint8_t)scopeState & (uint8_t)ScopeState::NotExpectsResponse) == 0; }

    /// Common internal states of the derived sub-automata
    /// General rule of thumb: *Sent states are waiting for a response from the MMU
    enum class ScopeState : uint_fast8_t {
        S0Sent, // beware - due to optimization reasons these SxSent must be kept one after another
        S1Sent,
        S2Sent,
        S3Sent,
        QuerySent,
        CommandSent,
        FilamentSensorStateSent,
        Reading8bitRegisters,
        Reading16bitRegisters,
        WritingInitRegisters,
        ButtonSent,
        ReadRegisterSent, // standalone requests for reading registers - from higher layers
        WriteRegisterSent,

        // States which do not expect a message - MSb set
        NotExpectsResponse = 0x80,
        Wait = NotExpectsResponse + 1,
        Ready = NotExpectsResponse + 2,
        RecoveringProtocolError = NotExpectsResponse + 3,
    };

    ScopeState scopeState; ///< internal state of the sub-automaton

    /// @returns the status of processing of the FINDA query response
    /// @param finishedRV returned value in case the message was successfully received and processed
    /// @param nextState is a state where the state machine should transfer to after the message was successfully received and processed
    // StepStatus ProcessFINDAReqSent(StepStatus finishedRV, State nextState);

    /// @returns the status of processing of the statistics query response
    /// @param finishedRV returned value in case the message was successfully received and processed
    /// @param nextState is a state where the state machine should transfer to after the message was successfully received and processed
    // StepStatus ProcessStatisticsReqSent(StepStatus finishedRV, State nextState);

    /// Called repeatedly while waiting for a query (Q0) period.
    /// All event checks to report immediately from the printer to the MMU shall be done in this method.
    /// So far, the only such a case is the filament sensor, but there can be more like this in the future.
    void CheckAndReportAsyncEvents();
    void SendQuery();
    void StartReading8bitRegisters();
    void ProcessRead8bitRegister();
    void StartReading16bitRegisters();
    ScopeState ProcessRead16bitRegister(ProtocolLogic::ScopeState stateAtEnd);
    void StartWritingInitRegisters();
    /// @returns true when all registers have been written into the MMU
    bool ProcessWritingInitRegister();
    void SendAndUpdateFilamentSensor();
    void SendButton(uint8_t btn);
    void SendVersion(uint8_t stage);
    void SendReadRegister(uint8_t index, ScopeState nextState);
    void SendWriteRegister(uint8_t index, uint16_t value, ScopeState nextState);

    StepStatus ProcessVersionResponse(uint8_t stage);

    /// Top level split - calls the appropriate step based on current scope
    StepStatus ScopeStep();

    static constexpr uint8_t maxRetries = 6;
    uint8_t retries;

    void StartSeqRestart();
    void DelayedRestartRestart();
    void IdleRestart();
    void CommandRestart();

    StepStatus StartSeqStep();
    StepStatus DelayedRestartWait();
    StepStatus IdleStep();
    StepStatus IdleWait();
    StepStatus CommandStep();
    StepStatus CommandWait();
    StepStatus StoppedStep() { return Processing; }

    StepStatus ProcessCommandQueryResponse();

    inline void SetRequestMsg(RequestMsg msg) {
        rq = msg;
    }
    inline const RequestMsg &ReqMsg() const { return rq; }
    RequestMsg rq = RequestMsg(RequestMsgCodes::unknown, 0);

    /// Records the next planned state, "unknown" msg code if no command is planned.
    /// This is not intended to be a queue of commands to process, protocol_logic must not queue commands.
    /// It exists solely to prevent breaking the Request-Response protocol handshake -
    /// - during tests it turned out, that the commands from Marlin are coming in such an asynchronnous way, that
    /// we could accidentally send T2 immediately after Q0 without waiting for reception of response to Q0.
    ///
    /// Beware, if Marlin manages to call PlanGenericCommand multiple times before a response comes,
    /// these variables will get overwritten by the last call.
    /// However, that should not happen under normal circumstances as Marlin should wait for the Command to finish,
    /// which includes all responses (and error recovery if any).
    RequestMsg plannedRq;

    /// Plan a command to be processed once the immediate response to a sent request arrives
    void PlanGenericRequest(RequestMsg rq);
    /// Activate the planned state once the immediate response to a sent request arrived
    bool ActivatePlannedRequest();

    uint32_t lastUARTActivityMs; ///< timestamp - last ms when something occurred on the UART
    DropOutFilter dataTO;        ///< Filter of short consecutive drop outs which are recovered instantly

    ResponseMsg rsp; ///< decoded response message from the MMU protocol

    State state; ///< internal state of ProtocolLogic

    Protocol protocol; ///< protocol codec

    array<uint8_t, 16> lastReceivedBytes; ///< remembers the last few bytes of incoming communication for diagnostic purposes
    uint8_t lrb;

    MMU2Serial *uart; ///< UART interface

    ErrorCode errorCode;       ///< last received error code from the MMU
    ProgressCode progressCode; ///< last received progress code from the MMU
    Buttons buttonCode;        ///< Last received button from the MMU.

    uint8_t lastFSensor; ///< last state of filament sensor

    // 8bit registers
    static constexpr uint8_t regs8Count = 3;
    static_assert(regs8Count > 0); // code is not ready for empty lists of registers
    static const uint8_t regs8Addrs[regs8Count] PROGMEM;
    uint8_t regs8[regs8Count];

    // 16bit registers
    static constexpr uint8_t regs16Count = 2;
    static_assert(regs16Count > 0); // code is not ready for empty lists of registers
    static const uint8_t regs16Addrs[regs16Count] PROGMEM;
    uint16_t regs16[regs16Count];

    // 8bit init values to be sent to the MMU after line up
    static constexpr uint8_t initRegs8Count = 1;
    static_assert(initRegs8Count > 0); // code is not ready for empty lists of registers
    static const uint8_t initRegs8Addrs[initRegs8Count] PROGMEM;
    uint8_t initRegs8[initRegs8Count];

    uint8_t regIndex;

    uint8_t mmuFwVersion[3];
    uint16_t mmuFwVersionBuild;

    friend class ProtocolLogicPartBase;
    friend class Stopped;
    friend class Command;
    friend class Idle;
    friend class StartSeq;
    friend class DelayedRestart;

    friend class MMU2;
};

} // namespace MMU2
