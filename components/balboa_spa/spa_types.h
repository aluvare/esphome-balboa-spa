#include "stdint.h"
#include <string>

#ifndef SPA_TYPES_H
#define SPA_TYPES_H

namespace esphome
{
    namespace balboa_spa
    {
        struct SpaFaultLog
        {
            uint8_t total_entries : 5;
            uint8_t current_entry : 5;
            uint8_t fault_code : 6;
            std::string fault_message;
            uint8_t days_ago : 8;
            uint8_t hour : 5;
            uint8_t minutes : 6;
        };

        struct SpaFilterSettings
        {
            // Zero initialised, and `valid` stays 0 until the spa has actually
            // reported its filter schedule. Writers must not build a 0x23
            // payload from these fields before that, or they would overwrite
            // the spa's real schedule with zeros.
            SpaFilterSettings()
                : filter1_hour(0), filter1_minute(0), filter1_duration_hour(0),
                  filter1_duration_minute(0), filter2_enable(0), filter2_hour(0),
                  filter2_minute(0), filter2_duration_hour(0),
                  filter2_duration_minute(0), valid(0) {}

            uint8_t filter1_hour : 5;
            uint8_t filter1_minute : 6;
            uint8_t filter1_duration_hour : 5;
            uint8_t filter1_duration_minute : 6;
            uint8_t filter2_enable : 1;
            uint8_t filter2_hour : 5;
            uint8_t filter2_minute : 6;
            uint8_t filter2_duration_hour : 5;
            uint8_t filter2_duration_minute : 6;
            uint8_t valid : 1; // 1 once the spa has reported the filter schedule
        };

        enum ToggleStateMaybe
        {
            OFF = 0,
            ON,
            HIGH_SPEED,
            DONT_KNOW
        };

        static const char *TOGGLE_STATE_MAYBE_STRINGS[] = {
            "OFF",
            "ON",
            "HIGH",
            "DONT_KNOW"};
    } // namespace balboa_spa
} // namespace esphome

#endif