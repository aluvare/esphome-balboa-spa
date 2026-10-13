#include "spa_init_mode_text_sensor.h"

namespace esphome
{
    namespace balboa_spa
    {
        static const char *TAG = "balboa_spa.text_sensor.init_mode";

        void SpaInitModeTextSensor::set_parent(BalboaSpa *parent)
        {
            this->parent_ = parent;
            parent->register_listener(
                [this](SpaState *spaState)
                {
                    this->update(spaState);
                });
        }

        void SpaInitModeTextSensor::update(SpaState *spaState)
        {
            if (spaState->init_mode == last_init_mode_)
            {
                return;
            }
            if (spaState->init_mode == 255)
            {
                // No status message decoded yet: publish nothing rather than
                // claiming the spa is idle.
                return;
            }

            std::string message;
            switch (spaState->init_mode)
            {
            case 0x00:
                message = "Idle";
                break;
            case 0x01:
                message = "Priming";
                break;
            case 0x02:
                message = "Fault";
                break;
            case 0x03:
                message = "Reminder";
                break;
            case 0x04:
                message = "Stage 1";
                break;
            case 0x05:
                message = "Stage 3";
                break;
            case 0x42:
                message = "Stage 2";
                break;
            default:
                char hex_str[8];
                snprintf(hex_str, sizeof(hex_str), "0x%02X", spaState->init_mode);
                message = std::string("Unknown (") + hex_str + ")";
                break;
            }

            if (spaState->init_mode == 0x02)
            {
                ESP_LOGW(TAG, "Spa reports FAULT state (init mode 0x02); check the panel and the fault log");
            }
            else
            {
                ESP_LOGI(TAG, "Spa state: %s (0x%02X)", message.c_str(), spaState->init_mode);
            }
            this->publish_state(message);
            last_init_mode_ = spaState->init_mode;
        }

    } // namespace balboa_spa
} // namespace esphome
