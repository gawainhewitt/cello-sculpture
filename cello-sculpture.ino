#include "mpr121.h"
#include "audio.h"
#include "constants.h"


const int numberOfSensors = 7;

int currentFile = 0;
bool songPlaying = false;
int stringsPlaying[4] = {0, 0, 0, 0};
bool started = false; // this is a hack to stop the bug where it crashes if strings are played before songs


void setup() {
Serial.begin(115200);
Serial.println("are we functioning?");
init_mpr121();
init_player();
delay(500);
}

void loop() {

    // wTrig.update();

    MPR121.updateAll();

    // if (songPlaying == true) {
    //     if (!playSdRaw2.isPlaying()){
    //         playSong(currentFile);
    //         currentFile = (currentFile + 1) % numberOfFiles;
    //     }
    // }

    for (uint8_t i=0; i < numberOfSensors; i++) {
        if (MPR121.isNewTouch(i)) {
            playSample(i);
            Serial.print("electrode ");
            Serial.print(i, DEC);
            Serial.println(" was just touched");
        } else if (MPR121.isNewRelease(i)) {
            Serial.print("electrode ");
            Serial.print(i, DEC);
            Serial.println(" was just released");
        }
    }
}