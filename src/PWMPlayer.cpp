#include "pico/stdlib.h"
#include "PWMPlayer.h"

using namespace picoPwm;


NoteEvent::NoteEvent(string note, float figure, uint level, float q) {
    this->figure = figure;
    this->level = level;
    this->note = note;
    this->q = q;
}

PWMPlayer::PWMPlayer(uint gpioPin, uint bpm, Notes *notes, float q) {
    this->q = (q > 1) ? 1 : (q < 0 ? 0 : q);
    this->bpm = bpm;
    this->gpioPin = gpioPin;
    this->pwm = new PWM(gpioPin);
    this->notes = notes;
}

PWMPlayer::PWMPlayer(uint gpioPin, uint bpm, NoteScale scale, float q) {
    this->q = (q > 1) ? 1 : (q < 0 ? 0 : q);
    this->bpm = bpm;
    this->gpioPin = gpioPin;
    this->pwm = new PWM(gpioPin);
    this->notes = new Notes(scale);
    this->ownNotes = true;
}

PWMPlayer::~PWMPlayer() {
    delete this->pwm;
    if(ownNotes) {
        delete this->notes;
    }
}

void PWMPlayer::playSequence(list<NoteEvent> sequence) {
    float whole = 1000 * this->bpm / 60;
    list<NoteEvent>::iterator it;
    for(it = sequence.begin(); it != sequence.end(); it++) {
        string note = it->note;
        uint level = it->level;
        float figure = it->figure;
        float q = (it->q <= 0 || it->q > 1) ? this->q : it->q;

        float freq = notes->f(note);
        float duration = q * whole / figure;
        float silence = (1 - q) * whole / figure;
        pwm->setFrequency((uint16_t)freq);
        pwm->setLevel(level);
        sleep_ms(duration);
        if(q < 1) {
            pwm->setLevel(0);
            sleep_ms(silence);
        }
    }
    pwm->setFrequency(0);
    pwm->setLevel(0);
}