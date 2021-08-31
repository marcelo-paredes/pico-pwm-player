/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "PWM.h"
#include "PWMPlayer.h"
#include "Notes.h"
#include "math.h"

int main() {
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    uint pwmPin = 14;

    using namespace picoPwm;
    picoPwm::Notes *notes = new picoPwm::Notes(picoPwm::equal, 440);
    picoPwm::PWMPlayer *player = new picoPwm::PWMPlayer(pwmPin, 120, notes);

    list<NoteEvent> sequence {
        NoteEvent("C4", 16, 1000), NoteEvent("D4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("F4", 16, 1000),
        NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("F4", 16, 1000),        
        NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("F4", 16, 1000),        
        NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("D4", 16, 1000),        

        NoteEvent("C4", 16, 1000), NoteEvent("D4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("F4", 16, 1000),
        NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("F4", 16, 1000),        
        NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("F4", 16, 1000),        
        NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("D4", 16, 1000),        

        NoteEvent("C4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("G4", 16, 1000), NoteEvent("E4", 16, 1000),        
        NoteEvent("D4", 16, 1000), NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("D4", 16, 1000),        

        NoteEvent("C4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("G4", 16, 1000), NoteEvent("E4", 16, 1000),        
        NoteEvent("D4", 16, 1000), NoteEvent("G4", 16, 1000), NoteEvent("F4", 16, 1000), NoteEvent("D4", 16, 1000),        

        NoteEvent("C4", 16, 1000), NoteEvent("D4", 16, 1000), NoteEvent("E4", 16, 1000), NoteEvent("F4", 16, 1000),
        NoteEvent("G4", 16, 1000), NoteEvent("A4", 16, 1000), NoteEvent("B4", 16, 1000), NoteEvent("C5", 16, 1000),


        NoteEvent("C4", 1, 1000)
    };

    while(true) {
        player->playSequence(sequence);
    }    
    //delete player;

#endif
}