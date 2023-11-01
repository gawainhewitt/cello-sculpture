#include "mpr121.h"
#include "audio.h"

const int numberOfSensors = 1;

void setup() {
Serial.begin(9600);
init_mpr121();
init_player();
delay(500);
}

void loop() {

    currtouched1 = mprBoard_A.touched();

    for (uint8_t i=0; i < numberOfSensors; i++) {
        if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
        Serial.print(i); Serial.println(" touched of A");
        playSound();
        }
    }

    lasttouched1 = currtouched1;
    return;
}