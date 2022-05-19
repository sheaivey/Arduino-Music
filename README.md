# Arduino-Music
This library plays basic notes and durations stored in an array using the built in `tone()` function. 
The library is non-blocking by calling `music.loop()` in the main loop of your project.

## Functions
* **Music(int pin)**
* **play(int melody[], int notes, int tempo = 120, int repeat = 0, int pitchShift = 0)** - Starts playing the song.
* **stop()** - Stops playing the song.
* **loop()** - Put in the main loop. Handles the actual note progression and timing.
* **bool isPlaying()** - Returns true or false if a song is currently playing.
* **setRepeat(int repeat)** - 0=play once, -1=forever, 1+= repeat song x number of time.
* **setTempo(int tempo)** - Change the tempo. If already playing the next note will play with the new tempo. This can be a cool effect slowing down the song or seeding it up based on some user interaction.
* **setPitchShift(int offset)** - offset the songs pitch by some ammount. Positive number = higher pitch, negative number = lower pitch. This can be a cool effect raising the pitch up or down based on some user interaction.


## Example
```c++
#include "Music.h"

// An array consisting of a note and duration tuple.
int melody[] = {
  // At Doom's Gate (E1M1)
  // Score available at https://musescore.com/pieridot/doom
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //1
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
  NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
  NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,
  // ... etc
};
int notes = sizeof(melody)/sizeof(melody[0])/2;
int tempo = 225;

#define SPEAKER_PIN 8
Music music(SPEAKER_PIN);

void setup() {
    music.play(melody, notes, tempo, -1); // repeat forever
}

void loop() {
    music.loop(); 
}
```

## Known Issues
Your main loop needs to run often. That means don't use delay() but instead use millis() and check if its time to do something.

Only one tone can play at a time per pin.

## Recognition
This library is based on Arduino Songs: https://github.com/robsoncouto/arduino-songs

You can find more songs there and a blocking version of the song player.


## Licensing 
MIT Open Source - Free to use anywhere. 
