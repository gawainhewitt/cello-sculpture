#include "mpr121.h"
#include "audio.h"
#include "constants.h"
#include "reboot.h"


const int numberOfSensors = 7;

int currentFile = 0;
bool playing = false;
bool started = false; // this is a hack to stop the bug where it crashes if strings are played before songs


void setup() {
Serial.begin(9600);
init_mpr121();
init_player();
pinMode(rebootButton, INPUT_PULLUP);
delay(500);
}

void loop() {


    if (playing == true) {
        if (!playSdRaw2.isPlaying()){
            playSong(currentFile);
            currentFile = (currentFile + 1) % numberOfFiles;
        }
    }

    // Serial.println(mprBoard_A.filteredData(0));


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
            } else if (i == CHANGE_BUTTON) {
                Serial.println("change");
            } else {
                if (!started){
                    playSong(currentFile); // this is a hack to stop the bug where it crashes if strings are played before songs
                    started = true;
                } else {
                    playSample(i - 3);
                }
            }
        }
    }

    if(digitalRead(rebootButton) == LOW){
      Serial.print("reboot");
      doReboot();
    }

    lasttouched1 = currtouched1;
    return;
}