#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioPlaySdRaw           playSdRaw1;     //xy=472,335
AudioPlaySdRaw           playSdRaw2;     //xy=479,406
AudioMixer4              mixer3;         //xy=793,406
AudioOutputI2S           audioOutput;    //xy=958,466
AudioConnection          patchCord1(playSdRaw1, 0, mixer3, 0);
AudioConnection          patchCord2(playSdRaw2, 0, mixer3, 1);
AudioConnection          patchCord3(mixer3, 0, audioOutput, 0);
AudioConnection          patchCord4(mixer3, 0, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=972,201
// GUItool: end automatically generated code

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

int major[4] = {0, 4, 7, 12};
int major7[4] = {0, 4, 7, 11};
int dom7[4] = {0, 4, 7, 10};
int major6[4] = {0, 4, 7, 9};
int pentatonic[4] = {0, 2, 4, 7};

struct SongDetails
{ 
  String name;
  int *scale;
  int noteOffset;
};

SongDetails one = {"BB1.RAW", dom7, 10};
SongDetails two = {"C1.RAW", major7, 0};
SongDetails three = {"C2.RAW", pentatonic, 0};
SongDetails four = {"C3.RAW", pentatonic, 0};
SongDetails five = {"C4.RAW", major7, 0};
SongDetails six = {"C5.RAW", major7, 0};
SongDetails seven = {"D1.RAW", major7, 2};
SongDetails eight = {"D2.RAW", major7, 2};
SongDetails nine = {"D3.RAW", major7, 2};
SongDetails ten = {"E1.RAW", major, 4};
SongDetails eleven = {"E2.RAW", major, 4};
SongDetails twelve = {"E_PENT1.RAW", pentatonic, 4};
SongDetails thirteen = {"E_PENT2.RAW", pentatonic, 4};

int currentCelloPlayer = 2;

SongDetails songs[] = {one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen};
int numberOfFiles = 13;

String celloSamples[] = {"CC2.RAW", "CC#2.RAW", "CD2.RAW", "CD#2.RAW", "CE2.RAW", "CF2.RAW", "CF#2.RAW", "CG2.RAW", "CG#2.RAW", "CA2.RAW", "CA#2.RAW", "CB2.RAW", "CC3.RAW", "CC#3.RAW", "CD3.RAW", "CD#3.RAW", "CE3.RAW", "CF3.RAW", "CF#3.RAW", "CG3.RAW", "CG#3.RAW", "CA3.RAW", "CA#3.RAW", "CB3.RAW"};
int numberOfSamples = 24;

String currentScale[4] = {"CA#2.RAW", "CD3.RAW", "CF3.RAW", "CG#3.RAW"};

void init_player() {

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(20);

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

void setScale(int file) {
  for (int i = 0; i < 4; i++) {
    String note = celloSamples[songs[file].scale[i] + songs[file].noteOffset];
    currentScale[i] = note;
  }
}

void playSong(int file) {
  Serial.print("play ");
  Serial.println(songs[file].name.c_str());
  playSdRaw2.play(songs[file].name.c_str()); 
  setScale(file);
}

void stopSong() {
  Serial.println("stop song");
  playSdRaw2.stop();
}

void playSample(int file) {
  Serial.println(currentScale[file].c_str());
  playSdRaw1.play(currentScale[file].c_str());
}