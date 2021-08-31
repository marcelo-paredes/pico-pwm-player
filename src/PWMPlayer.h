#pragma once
#include "PWM.h"
#include "Notes.h"
#include <list>
#include <string>

namespace picoPwm {
    class NoteEvent {
        public:
            // note is the note name i uppercase, optionally a # or lowecase b, and the octave
            //  "rest" or null are interpreted as a rest.
            // figure is the inverse of the note duration fraction, 1 = full, 2, 4, 8,...  
            //     using float so a dotted note could still be passed
            // 0 <= q <= 1 is the note duration as a fraction of the whole note duration
            //  i.e.: play onlu during 0.8 of the length of the figure
            // -1 means use the default from the player
            NoteEvent(string note, float figure, uint level, float q = -1);
        
        string note;
        float figure;
        uint level;
        float q;
    };



    class PWMPlayer {
        public:
            PWMPlayer(uint gpioPin, uint bpm, Notes *notes, float q = 0.8);
            ~PWMPlayer();
            void playSequence(list<NoteEvent> sequence); 

        private:
            Notes *notes;
            uint gpioPin;
            uint bpm;
            float q;
            PWM *pwm;
    };
}