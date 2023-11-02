#include "mpr121.h"
#include "audio.h"
#include "constants.h"

const int numberOfSensors = 2;

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
        if (!playSdRaw1.isPlaying()){
            playSong(currentFile);
            currentFile = (currentFile + 1) % numberOfFiles;
        }
    }

    currtouched1 = mprBoard_A.touched();

    for (uint8_t i=0; i < numberOfSensors; i++) {
        if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
        Serial.print(i); Serial.println(" touched of A");
        
        if (i == START_BUTTON){
            playSong(currentFile);
            currentFile = (currentFile + 1) % numberOfFiles;
            playing = true;
        } else if (i == STOP_BUTTON){
            stopSong();
            playing = false;
        }
        
        }
    }

    lasttouched1 = currtouched1;
    return;
}