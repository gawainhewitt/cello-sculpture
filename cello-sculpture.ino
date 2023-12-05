#include "mpr121.h"
#include "audio.h"

#define START_BUTTON 4

const int numberOfSensors = 4;

long lastDebounceTime = 0;  
long debounceDelay = 100;

bool buttonState = false;

void setup() {
Serial.begin(115200);
Serial.println("are we functioning?");
pinMode(START_BUTTON, INPUT_PULLUP);
init_mpr121();
init_player();
delay(500);
}

void loop() {

    // wTrig.update();

    MPR121.updateAll();

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
    
    if ( (millis() - lastDebounceTime) > debounceDelay) {
        if (buttonState == false) {
            if (digitalRead(START_BUTTON) == LOW) {
                toggleSong();
                buttonState = true;
                Serial.println("button is low!");
            }
        }
        lastDebounceTime = millis();
    }

    if (buttonState == true) {
        if (digitalRead(START_BUTTON) == HIGH) {
            buttonState = false;
        }
    }

     // if (songPlaying == true) {
    //     if (!playSdRaw2.isPlaying()){
    //         playSong(currentFile);
    //         currentFile = (currentFile + 1) % numberOfFiles;
    //     }
    // }
}