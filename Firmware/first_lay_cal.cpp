//! @file
//! @date Jun 10, 2019
//! @author Marek Bel
//! @brief First layer (Z offset) calibration

#include "first_lay_cal.h"
#include "Configuration_var.h"
#include "language.h"
#include "Marlin.h"
#include "cmdqueue.h"
#include "mmu2.h"
#include <avr/pgmspace.h>
#include <math.h>

//! @brief Count extrude length
//!
//! @param layer_height layer height in mm
//! @param extrusion_width extrusion width in mm
//! @param extrusion_length extrusion length in mm
//! @return filament length in mm which needs to be extruded to form line
static constexpr float count_e(float layer_height, float extrusion_width, float extrusion_length, float filament_diameter=1.75f)
{
    return (extrusion_length * ((M_PI * pow(layer_height, 2)) / 4 + layer_height * (extrusion_width - layer_height))) / ((M_PI * pow(filament_diameter, 2)) / 4);
}

//! @brief Extrusion spacing
//!
//! @param layer_height layer height in mm
//! @param extrusion_width extrusion width in mm
//! @return filament length in mm which needs to be extruded to form line
static constexpr float spacing(float layer_height, float extrusion_width, float overlap_factor=1.f)
{
    return extrusion_width - layer_height * (overlap_factor - M_PI/4);
}

//! @brief Wait for preheat
void lay1cal_wait_preheat()
{
    const char * const preheat_cmd[] =
    {
        PSTR("M107"),
        PSTR("M190"),
        PSTR("M109"),
        PSTR("G28"),
        PSTR("G92 E0.0")
    };

    for (uint8_t i = 0; i < (sizeof(preheat_cmd)/sizeof(preheat_cmd[0])); ++i)
    {
        enquecommand_P(preheat_cmd[i]);
    }
}

//! @brief Load filament
//! @param cmd_buffer character buffer needed to format gcodes
//! @param filament filament to use (applies for MMU only)
//! @returns true if extra purge distance is needed in case of MMU prints (after a toolchange), otherwise false
bool lay1cal_load_filament(char *cmd_buffer, uint8_t filament)
{
    if (MMU2::mmu2.Enabled())
    {
        enquecommand_P(PSTR("M83"));
        enquecommand_P(PSTR("G1 Y-3.0 F1000.0"));
        enquecommand_P(PSTR("G1 Z0.4 F1000.0"));

        uint8_t currentTool = MMU2::mmu2.get_current_tool();
        if(currentTool == filament ){
            // already have the correct tool loaded - do nothing
            return false;
        } else if( currentTool != (uint8_t)MMU2::FILAMENT_UNKNOWN){
            // some other slot is loaded, perform an unload first
            enquecommand_P(PSTR("M702"));
        }
        // perform a toolchange
        // sprintf_P(cmd_buffer, PSTR("T%d"), filament);
        // rewriting the trivial T<filament> g-code command saves 30B:
        cmd_buffer[0] = 'T';
        cmd_buffer[1] = filament + '0';
        cmd_buffer[2] = 0;

        enquecommand(cmd_buffer);
        return true;
    }
    return false;
}

//! @brief Print intro line
//! @param extraPurgeNeeded false if the first MMU-related "G1 E29" have to be skipped because the nozzle is already full of filament
//! @param layer_height the height of the calibration layer
//! @param extrusion_width the width of the extrusion layer 
void lay1cal_intro_line(bool extraPurgeNeeded, float layer_height, float extrusion_width)
{
    static const char cmd_intro_mmu_3[] PROGMEM = "G1 X55.0 E29.0 F1073.0";
    static const char cmd_intro_mmu_4[] PROGMEM = "G1 X5.0 E29.0 F1800.0";
    static const char cmd_intro_mmu_5[] PROGMEM = "G1 X55.0 E8.0 F2000.0";
    static const char cmd_intro_mmu_6[] PROGMEM = "G1 Z0.3 F1000.0";
    static const char cmd_intro_mmu_7[] PROGMEM = "G92 E0.0";
    static const char cmd_intro_mmu_8[] PROGMEM = "G1 X240.0 E25.0  F2200.0";
    static const char cmd_intro_mmu_9[] PROGMEM = "G1 Y-2.0 F1000.0";
    static const char cmd_intro_mmu_10[] PROGMEM = "G1 X55.0 E25 F1400.0";
    static const char cmd_intro_mmu_11[] PROGMEM = "G1 Z0.20 F1000.0";
    static const char cmd_intro_mmu_12[] PROGMEM = "G1 X5.0 E4.0 F1000.0";

    static const char * const intro_mmu_cmd[] PROGMEM =
    {
        // first 2 items are only relevant if filament was not loaded - i.e. extraPurgeNeeded == true
        cmd_intro_mmu_3,
        cmd_intro_mmu_4,

        cmd_intro_mmu_5,
        cmd_intro_mmu_6,
        cmd_intro_mmu_7,
        cmd_intro_mmu_8,
        cmd_intro_mmu_9,
        cmd_intro_mmu_10,
        cmd_intro_mmu_11,
        cmd_intro_mmu_12,
    };

    if (MMU2::mmu2.Enabled())
    {
        for (uint8_t i = (extraPurgeNeeded ? 0 : 2); i < (sizeof(intro_mmu_cmd)/sizeof(intro_mmu_cmd[0])); ++i)
        {
            enquecommand_P(static_cast<char*>(pgm_read_ptr(&intro_mmu_cmd[i])));
        }
    }
    else
    {
        char cmd_buffer[30];
        static const char fmt1[] PROGMEM = "G1 X%d E%-.3f F1000.0";
        sprintf_P(cmd_buffer, fmt1, 60, count_e(layer_height, extrusion_width * 4.f, 60));
        enquecommand(cmd_buffer);
        sprintf_P(cmd_buffer, fmt1, 100, count_e(layer_height, extrusion_width * 8.f, 40));
        enquecommand(cmd_buffer);
    }
}

//! @brief Setup for printing meander
void lay1cal_before_meander()
{
    static const char cmd_pre_meander_0[] PROGMEM = "G92 E0.0";
    static const char cmd_pre_meander_1[] PROGMEM = "G21"; //set units to millimeters TODO unsupported command
    static const char cmd_pre_meander_2[] PROGMEM = "G90"; //use absolute coordinates
    static const char cmd_pre_meander_3[] PROGMEM = "M83"; //use relative distances for extrusion TODO: duplicate
    static const char cmd_pre_meander_4[] PROGMEM = "G1 E-1.50000 F2100.00000";
    static const char cmd_pre_meander_5[] PROGMEM = "G1 Z5 F7200.000";
    static const char cmd_pre_meander_6[] PROGMEM = "M204 S1000"; //set acceleration
    static const char cmd_pre_meander_7[] PROGMEM = "G1 F4000";

    static const char * const cmd_pre_meander[] PROGMEM =
    {
            cmd_pre_meander_0,
            cmd_pre_meander_1,
            cmd_pre_meander_2,
            cmd_pre_meander_3,
            cmd_pre_meander_4,
            cmd_pre_meander_5,
            cmd_pre_meander_6,
            cmd_pre_meander_7,
    };

    for (uint8_t i = 0; i < (sizeof(cmd_pre_meander)/sizeof(cmd_pre_meander[0])); ++i)
    {
        enquecommand_P(static_cast<char*>(pgm_read_ptr(&cmd_pre_meander[i])));
    }
}

//! @brief Print meander start
void lay1cal_meander_start(float layer_height, float extrusion_width)
{
    char cmd_buffer[30];
    enquecommand_P(PSTR("G1 X50 Y155"));

    static const char fmt1[] PROGMEM = "G1 Z%-.3f F7200.000";
    sprintf_P(cmd_buffer, fmt1, layer_height);
    enquecommand(cmd_buffer);

    enquecommand_P(PSTR("G1 F1080"));

    static const char fmt2[] PROGMEM = "G1 X%d Y%d E%-.5f";
    sprintf_P(cmd_buffer, fmt2,  75, 155, count_e(layer_height, extrusion_width * 4.f, 25));
    enquecommand(cmd_buffer);
    sprintf_P(cmd_buffer, fmt2, 100, 155, count_e(layer_height, extrusion_width * 2.f, 25));
    enquecommand(cmd_buffer);
    sprintf_P(cmd_buffer, fmt2, 200, 155, count_e(layer_height, extrusion_width, 100));
    enquecommand(cmd_buffer);
    sprintf_P(cmd_buffer, fmt2, 200, 135, count_e(layer_height, extrusion_width, 20));
    enquecommand(cmd_buffer);
}

//! @brief Print meander
//! @param cmd_buffer character buffer needed to format gcodes
void lay1cal_meander(float layer_height, float extrusion_width)
{
    char cmd_buffer[30];
    static const char fmt1[] PROGMEM = "G1 X%d Y%d E%-.5f";
    const float short_length = 20;
    float long_length = 150;
    const float long_extrusion = count_e(layer_height, extrusion_width, long_length);
    const float short_extrusion = count_e(layer_height, extrusion_width, short_length);

    uint8_t y_pos = 135;
    uint8_t x_pos = 50;
    for(uint8_t i = 0; i <= 4; ++i)
    {
        sprintf_P(cmd_buffer, fmt1, x_pos, y_pos, long_extrusion);
        enquecommand(cmd_buffer);

        y_pos -= short_length;

        sprintf_P(cmd_buffer, fmt1, x_pos, y_pos, short_extrusion);
        enquecommand(cmd_buffer);

        x_pos += long_length;

        long_length = -long_length;
    }

}

//! @brief Print square
//!
//! This function needs to be called 16 times for i from 0 to 15.
//!
//! @param cmd_buffer character buffer needed to format gcodes
//! @param i iteration
void lay1cal_square(char *cmd_buffer, uint8_t i, float layer_height, float extrusion_width)
{
    const float long_length = 20;
    const float short_length = spacing(layer_height, extrusion_width);
    const float long_extrusion = count_e(layer_height, extrusion_width, long_length);
    const float short_extrusion = count_e(layer_height, extrusion_width, short_length);

    static const char fmt1[] PROGMEM = "G1 X%d Y%-.2f E%-.3f";
    sprintf_P(cmd_buffer, fmt1, 70, (35 - i*short_length * 2), long_extrusion);
    enquecommand(cmd_buffer);
    sprintf_P(cmd_buffer, fmt1, 70, (35 - (2 * i + 1)*short_length), short_extrusion);
    enquecommand(cmd_buffer);
    sprintf_P(cmd_buffer, fmt1, 50, (35 - (2 * i + 1)*short_length), long_extrusion);
    enquecommand(cmd_buffer);
    sprintf_P(cmd_buffer, fmt1, 50, (35 - (i + 1)*short_length * 2), short_extrusion);
    enquecommand(cmd_buffer);
}
