#include "mpr121.h"
#include "audio.h"

const int numberOfSensors = 1;

int currentFile = 0;
bool playing = false;

void setup() {
Serial.begin(9600);
init_mpr121();
init_player();
delay(500);
}

void loop() {

    if (playing == true) {
        if (!playSdWav1.isPlaying()){
            playSound(currentFile);
            currentFile = (currentFile + 1) % numberOfFiles;
        }
    }

    currtouched1 = mprBoard_A.touched();

    for (uint8_t i=0; i < numberOfSensors; i++) {
        if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
        Serial.print(i); Serial.println(" touched of A");
        playSound(currentFile);
        currentFile = (currentFile + 1) % numberOfFiles;
        playing = true;
        }
    }

    lasttouched1 = currtouched1;
    return;
}