#pragma once
#include "PWM.h"
#include "Notes.h"
#include <list>
#include <string>

namespace picoPwm {
    /**
     * Provides a simple representation of a note event for purposes
     * of playing.
     */
    class NoteEvent {
        public:
            /**
             *  Constructs a NoteEvent
             *  @param note The note name
             *  @param figure The note figure number (1 for whole, 2, 4, 8...)
             *  @param level The volume level 0-10000
             *  @param q The note duration in terms of the figure duration 0 < q <= 1.
             *      The value -1 (the default value) means us the player's default.
             */
            NoteEvent(string note, float figure, uint level, float q = -1);
        
        string note;
        float figure;
        uint level;
        float q;
    };



    /**
     * Configures a gpio pint to play PWM sound and plays
     * sequences of note events.
     */

    class PWMPlayer {
        public:
            /**
             * Constructs a PWMPlayer
             * 
             * @param gpioPin The gpio pin
             * @param bpm The palyer's bpm
             * @param notes The note frequency provider
             * @param q the specified portion of actual note durations to play. The rest of the duration is set to silence.
             */
            PWMPlayer(uint gpioPin, uint bpm, Notes *notes, float q = 0.8);

            /**
             * Constructs a PWMPlayer
             * 
             * @param gpioPin The gpio pin
             * @param bpm The palyer's bpm
             * @param scale The name of the scale to use for constructing a Notes provider
             * @param q the specified portion of actual note durations to play. The rest of the duration is set to silence.
             */
            PWMPlayer(uint gpioPin, uint bpm, NoteScale scale, float q = 0.8);

            /**
             * Destructor
             * 
             * Cleans up resources owned by the PWMPlayer
             */
            ~PWMPlayer();

            /**
             * Plays a notes sequence
             * @param sequence The list of NoteEvents to play
             */
            void playSequence(list<NoteEvent> sequence); 

        private:
            bool ownNotes = false;
            Notes *notes;
            uint gpioPin;
            uint bpm;
            float q;
            PWM *pwm;
    };
}