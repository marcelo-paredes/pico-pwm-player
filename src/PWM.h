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
        /**
         * Constructs a PWM object and associates related pwm data to the pin number
         * 
         * @param pinNumber The gpio pin number to use for PWM
         */
        PWM(uint pinNumber);

        /**
         * Destructor
         */
        ~PWM();

        /**
         * Sets the PWNM frequency on the associated pin
         * 
         * @param frequency The frequency
         */
        void setFrequency(uint16_t frequency);

        /**
         * Sets the volume level on the associated pin
         * 
         * @param level The volume level - value in range of 0..10000
         */
        void setLevel(uint16_t level);

    private:
        void configure();
        void unconfigure();
};
}