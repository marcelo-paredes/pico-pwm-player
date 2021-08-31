#pragma once
#include "pico/stdio.h"
#include "pico/stdio.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

using namespace std;
namespace picoPwm {

class PWM {
    private:
        uint pin = 0;
        uint16_t slice= 0;
        uint8_t channel = 0;
        uint32_t top = 0;
        uint32_t sourceFrequency = 0;
        pwm_config config;

    public:
        PWM(uint pinNumber);
        ~PWM();
        void setFrequency(uint16_t frequuency);
        void setLevel(uint16_t level);

    private:
        void configure();
        void unconfigure();
};
}