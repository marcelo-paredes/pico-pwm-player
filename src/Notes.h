#pragma once
#include <string>
#include <map>
#include "math.h"

namespace picoPwm {

    /**
     * Enumerates the types of chromatic scales to handle
     */
    typedef enum {
        /// Equal temperament
        equal,

        /// Pythagorean (based on the fifth interval being 3/2)
        pythagorean,

        /// Just
        just
    } NoteScale;

    /**
     * Provides a set of notes from A0 to A8 using different (chromatic) scale rules.
     */

    class Notes {
        public:
            /**
             *  Constructs a notes provider
             *  
             *  @param scale The scale to use
             *  @param base The frequency of A4 (440, 432,...)
             */
            Notes(NoteScale scale = equal, float base = 440);


            /**
             *  Retrieves the frequency for a given note
             *  
             *  @param note The note, or "rest".
             *  When "rest", the result will be 0.
             * 
             *  The basic form is <note name><octave>, where note name is one letter in C, D, E, F, G, A, B,
             *  and an optional "accidental" # or b followed by a digit for the octave number.
             * 
             *  The set of admitted notes is C, C#, Db, D, D#, Eb, E, F, F#, Gb, G, G#, Ab, A, A#, Bb, B.
             *  Examples of valid notes are A4, Bb3, C#5, Db3, A5, C8
             */
            float f(std::string note);
            
        private:
            float baseA4 = 440;
            std::map<std::string, float> noteValues;
            void buildGeometric();
            void buildPythagorean();
            void buildJust();
            void buildA();       
    };

}
