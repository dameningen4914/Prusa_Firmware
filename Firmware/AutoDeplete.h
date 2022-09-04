/// @file
#pragma once
#include <stdint.h>
#include "eeprom.h"

// See documentation here: https://help.prusa3d.com/article/spooljoin-mmu2s_134252

namespace SpoolJoin {

class SpoolJoin {
public:
    SpoolJoin();

    enum class EEPROM : uint8_t {
        Unknown, ///< SpoolJoin is unknown while printer is booting up
        Enabled, ///< SpoolJoin is enabled in EEPROM
        Disabled, ///< SpoolJoin is disabled in EEPROM
        NA, ///< SpoolJoin is 'Not Applicable' when Fsensor is faulty
        Empty = 0xFF ///< EEPROM has not been set before and all bits are 1 (0xFF) - either a new printer or user erased the memory
    };

    /// @brief Called when EEPROM is ready to be read
    void initSpoolJoinStatus();

    /// @brief Enable SpoolJoin
    inline void enableSpoolJoin() { updateSpoolJoinStatus(EEPROM::Enabled); };

    /// @brief Disable SpoolJoin
    inline void disableSpoolJoin() { updateSpoolJoinStatus(EEPROM::Disabled); };

    /// @brief Toggle SpoolJoin
    static void toggleSpoolJoin();

    /// @brief Check if SpoolJoin is enabled
    uint8_t isSpoolJoinEnabled();

    /// @brief Fetch the next slot number should count from 0 to 4.
    /// When filament slot 4 is depleted, the next slot should be 0.
    /// @returns the next slot, ranges from 0 to 4
    uint8_t nextSlot();

private:
    /// @brief Update EEPROM
    /// @param newStatus Status to write into EEPROM
    void updateSpoolJoinStatus(EEPROM newStatus);

    /// @brief SpoolJoin status
    enum EEPROM status;

    /// @brief Currently used slot, ranges from 0 to 4
    uint8_t currentMMUSlot;
};

extern SpoolJoin spooljoin;

} // namespace SpoolJoin
