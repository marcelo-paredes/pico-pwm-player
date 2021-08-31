#include <string>
#include <algorithm>
#include "Notes.h"

using namespace picoPwm;

Notes::Notes(NoteScale scale, float base) {
    this->baseA4 = base;
    this->buildA();
    switch(scale) {
        case pythagorean: buildPythagorean(); break;
        case just: buildJust(); break;
        case equal: buildGeometric();
        default: buildGeometric();
    }
}

float Notes::f(std::string note) {
    std::for_each(note.begin(), note.end(), [](char & c) {
        c = ::tolower(c);
    });
    float result = this->noteValues[note];
    return result;
}

void Notes::buildA() {
    this->noteValues["a8"] = this->baseA4 * 16;
    this->noteValues["a7"] = this->baseA4 * 8;
    this->noteValues["a6"] = this->baseA4 * 4;
    this->noteValues["a5"] = this->baseA4 * 2;
    this->noteValues["a4"] = this->baseA4;
    this->noteValues["a3"] = this->baseA4 / 2.0;
    this->noteValues["a2"] = this->baseA4 / 4.0;
    this->noteValues["a1"] = this->baseA4 / 8.0;
    this->noteValues["a0"] = this->baseA4 / 16.0;
 }

 void Notes::buildGeometric() {
     float factor = std::pow(2.0, 1.0/12.0);
     for(int octave = 0; octave < 8; octave++) {
        float frequency = this->noteValues["a"+std::to_string(octave)];
         for(int semitone = 1; semitone < 12; semitone++) {
             frequency = frequency * factor;
             switch(semitone) {
                 case  1: this->noteValues["a#" + std::to_string(octave)]     = frequency;
                          this->noteValues["bb" + std::to_string(octave)]     = frequency; break;
                 case  2: this->noteValues["b"  + std::to_string(octave)]     = frequency; break;
                 case  3: this->noteValues["c"  + std::to_string(octave + 1)] = frequency; break;
                 case  4: this->noteValues["c#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["db" + std::to_string(octave + 1)] = frequency; break;
                 case  5: this->noteValues["d"  + std::to_string(octave + 1)] = frequency; break;
                 case  6: this->noteValues["d#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["eb" + std::to_string(octave + 1)] = frequency; break;
                 case  7: this->noteValues["e"  + std::to_string(octave + 1)] = frequency; break;
                 case  8: this->noteValues["f"  + std::to_string(octave + 1)] = frequency; break;
                 case  9: this->noteValues["f#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["gb" + std::to_string(octave + 1)] = frequency; break;
                 case 10: this->noteValues["g"  + std::to_string(octave + 1)] = frequency; break;
                 case 11: this->noteValues["g#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["ab" + std::to_string(octave + 1)] = frequency; break;
             }
         }
     }
 }

void Notes::buildPythagorean() {
    //                                     0  
    // Cb->Gb->Db->Ab->Eb->Bb->F->C->G->D->A->E->B->F#->C#->G#->D#->A#
    float factors[] = {
        1.0,
        2187.0/2048.0,
        9.0/8.0,
        19683.0/16384.0,
        81.0/64.0,
        4.0/3.0,
        729.0/512.0,
        3.0/2.0,
        6561.0/4096.0,
        27.0/16.0,
        59049.0/32768.0,
        243.0/128.0
    };
    for(int octave = 0; octave < 8; octave++) {
        float f0 = this->noteValues["a"+std::to_string(octave)];
        for(int semitone = 1; semitone < 12; semitone++) {
            float frequency = f0 * factors[semitone];
            switch(semitone) {
                 case  1: this->noteValues["a#" + std::to_string(octave)]     = frequency;
                          this->noteValues["bb" + std::to_string(octave)]     = frequency; break;
                 case  2: this->noteValues["b"  + std::to_string(octave)]     = frequency; break;
                 case  3: this->noteValues["c"  + std::to_string(octave + 1)] = frequency; break;
                 case  4: this->noteValues["c#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["db" + std::to_string(octave + 1)] = frequency; break;
                 case  5: this->noteValues["d"  + std::to_string(octave + 1)] = frequency; break;
                 case  6: this->noteValues["d#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["eb" + std::to_string(octave + 1)] = frequency; break;
                 case  7: this->noteValues["e"  + std::to_string(octave + 1)] = frequency; break;
                 case  8: this->noteValues["f"  + std::to_string(octave + 1)] = frequency; break;
                 case  9: this->noteValues["f#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["gb" + std::to_string(octave + 1)] = frequency; break;
                 case 10: this->noteValues["g"  + std::to_string(octave + 1)] = frequency; break;
                 case 11: this->noteValues["g#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["ab" + std::to_string(octave + 1)] = frequency; break;
            }
        }
    }
}

void Notes::buildJust() {
    //                                     0  
    // Cb->Gb->Db->Ab->Eb->Bb->F->C->G->D->A->E->B->F#->C#->G#->D#->A#
    float factors[] = {
        1.0,
        25.0/24.0,
        9.0/8.0,
        6.0/5.0,
        5.0/4.0,
        4.0/3.0,
        45.0/32.0,
        3.0/2.0,
        8.0/5.0,
        5.0/3.0,
        9.0/5.0,
        15.0/8.0
    };
    for(int octave = 0; octave < 8; octave++) {
        float f0 = this->noteValues["a"+std::to_string(octave)];
        for(int semitone = 1; semitone < 12; semitone++) {
            float frequency = f0 * factors[semitone];
            switch(semitone) {
                 case  1: this->noteValues["a#" + std::to_string(octave)]     = frequency;
                          this->noteValues["bb" + std::to_string(octave)]     = frequency; break;
                 case  2: this->noteValues["b"  + std::to_string(octave)]     = frequency; break;
                 case  3: this->noteValues["c"  + std::to_string(octave + 1)] = frequency; break;
                 case  4: this->noteValues["c#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["db" + std::to_string(octave + 1)] = frequency; break;
                 case  5: this->noteValues["d"  + std::to_string(octave + 1)] = frequency; break;
                 case  6: this->noteValues["d#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["eb" + std::to_string(octave + 1)] = frequency; break;
                 case  7: this->noteValues["e"  + std::to_string(octave + 1)] = frequency; break;
                 case  8: this->noteValues["f"  + std::to_string(octave + 1)] = frequency; break;
                 case  9: this->noteValues["f#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["gb" + std::to_string(octave + 1)] = frequency; break;
                 case 10: this->noteValues["g"  + std::to_string(octave + 1)] = frequency; break;
                 case 11: this->noteValues["g#" + std::to_string(octave + 1)] = frequency;
                          this->noteValues["ab" + std::to_string(octave + 1)] = frequency; break;
            }
        }
    }
}