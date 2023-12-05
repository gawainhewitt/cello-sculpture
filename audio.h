#include <AltSoftSerial.h>    // Arduino build environment requires this
#include <wavTrigger.h>

wavTrigger wTrig;             // Our WAV Trigger object

char gWTrigVersion[VERSION_STRING_LEN];    // WAV Trigger version string


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
  // If the Arduino is powering the WAV Trigger, we should wait for the WAV
  //  Trigger to finish reset before trying to send commands.
  delay(1000);

  // WAV Trigger startup at 57600
  wTrig.start();
  delay(10);
  
  // Send a stop-all command and reset the sample-rate offset, in case we have
  //  reset while the WAV Trigger was already playing.
  wTrig.stopAllTracks();
  wTrig.samplerateOffset(0);
  
  // Enable track reporting from the WAV Trigger
  wTrig.setReporting(true);
  
  // Allow time for the WAV Trigger to respond with the version string and
  //  number of tracks.
  delay(100); 
  
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
  // playSdRaw2.play(songs[file].name.c_str()); 
  setScale(file);
}

void stopSong() {
  Serial.println("stop song");
  // playSdRaw2.stop();
}

void playSample(int file) {
  wTrig.trackPlayPoly(file + 14);
  // playSdRaw1.play(currentScale[file].c_str());
}