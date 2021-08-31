#include "PWM.h"
#define TOP_MAX 65534

using namespace picoPwm;

PWM::PWM(uint pinNumber) {
    this->pin = pinNumber;
    this->configure();
}

PWM::~PWM() {
    this->unconfigure();
}

void PWM::configure() {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    this->slice = pwm_gpio_to_slice_num(this->pin);
    this->channel = pwm_gpio_to_channel(this->pin);
    this->sourceFrequency = clock_get_hz(clk_sys);
    this->config = pwm_get_default_config();
}

void PWM::unconfigure() {
    pwm_set_gpio_level(this->pin, 0);
    pwm_set_enabled(this->slice, false);
}

void PWM::setFrequency(uint16_t frequency) {
    float div =  (float)this->sourceFrequency / (frequency * 10000);
    pwm_config_set_clkdiv(&this->config, div);
    pwm_config_set_wrap(&this->config, 10000);
    pwm_init(this->slice, &config, false);
}

void PWM::setLevel(uint16_t level) {
    if(level == 0) {
        pwm_set_enabled(this->slice, false);
    } else {
        pwm_set_gpio_level(this->pin, level);
        pwm_set_enabled(this->slice, true);
    }
}


