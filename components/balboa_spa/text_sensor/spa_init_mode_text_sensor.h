#pragma once

#include "esphome/components/text_sensor/text_sensor.h"
#include "../balboaspa.h"

namespace esphome
{
    namespace balboa_spa
    {
        // Exposes the Initialization Mode field of the status update (argument
        // 1), which is where the spa reports a fault state. Before this existed
        // that byte was read as the reminder type and surfaced as
        // "Unknown (0x02)" on the reminder sensor, so a spa in fault looked
        // like an unrecognised reminder.
        class SpaInitModeTextSensor : public text_sensor::TextSensor
        {
        public:
            void set_parent(BalboaSpa *parent);
            void update(SpaState *spaState);

        private:
            BalboaSpa *parent_;
            uint8_t last_init_mode_ = 254;
        };
    } // namespace balboa_spa
} // namespace esphome
