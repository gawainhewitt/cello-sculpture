#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdRaw           playSdRaw1;     //xy=411,454
AudioOutputI2S           audioOutput;    //xy=687,423
AudioConnection          patchCord1(playSdRaw1, 0, audioOutput, 0);
AudioConnection          patchCord2(playSdRaw1, 0, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=911,320
// GUItool: end automatically generated code


#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

String songNames[] = {"BB1.RAW", "C1.RAW", "C2.RAW", "C3.RAW", "C4.RAW", "C5.RAW", "D1.RAW", "D2.RAW", "D3.RAW", "E1.RAW", "E2.RAW", "E_PENT1.RAW", "E_PENT2.RAW"};
int numberOfFiles = 13;

String celloSamples[] = {"CC2.RAW", "CC#2.RAW", "CD2.RAW", "CD#2.RAW", "CE2.RAW", "CF2.RAW", "CF#2.RAW", "CG2.RAW", "CG#2.RAW", "CA2.RAW", "CA#2.RAW", "CB2.RAW", "CC3.RAW", "CC#3.RAW", "CD3.RAW", "CD#3.RAW", "CE3.RAW", "CF3.RAW", "CF#3.RAW", "CG3.RAW", "CG#3.RAW", "CA3.RAW", "CA#3.RAW", "CB3.RAW"};
int numberOfSamples = 24;

void init_player() {

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void playSong(int file) {
    Serial.print("play ");
    Serial.println(songNames[file].c_str());
    playSdRaw1.play(songNames[file].c_str());
}

void stopSong() {
    Serial.println("stop song");
    playSdRaw1.stop();
}

void playSample(int file) {
    Serial.print("play note");
    Serial.println(celloSamples[file].c_str());
    playSdRaw1.play(celloSamples[file].c_str());
}