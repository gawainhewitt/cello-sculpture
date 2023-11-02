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

String fileNames[] = {"BB1.RAW", "C1.RAW", "C2.RAW", "C3.RAW", "C4.RAW", "C5.RAW", "D1.RAW", "D2.RAW", "D3.RAW", "E1.RAW", "E2.RAW", "E_PENT1.RAW", "E_PENT2.RAW"};
int numberOfFiles = 13;

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
    Serial.println(fileNames[file].c_str());
    playSdRaw1.play(fileNames[file].c_str());
}

void stopSong() {
    Serial.println("stop song");
    playSdRaw1.stop();
}