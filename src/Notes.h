#pragma once
#include <string>
#include <map>
#include "math.h"

namespace picoPwm {

    typedef enum {
        equal,
        pythagorean,
        just
    } NoteScale;



    class Notes {
        public:
            Notes(NoteScale scale = equal, float base = 440);
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
