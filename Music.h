#include "Arduino.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

class Music
{
  public:
    Music(int pin);
    void play(int melody[], int notes, int tempo = 120, int repeat = 0, int pitchShift = 0);
    void stop();
    void loop();
    bool isPlaying();
    void setPitchShift(int offset) { _pitchShift = offset; }; // + higher pitch, - lower pitch, 0 no change
    void setRepeat(int repeat) { _repeat = repeat; }; // 0=play once, -1=forever, 1+= repeat x number of times
    void setTempo(int tempo) { _tempo = tempo < 50 ? 50 : tempo > 800 ? 800 : tempo; };
  private:
    int _pin;
    bool _isPlaying;
    int _tempo;
    int _notes;
    int _wholenote;
    int _currentNote;
    int _pitchShift;
    int _repeat; 
    unsigned long _noteStartTime;
    int *_melody;
};

Music::Music(int pin){
    _pin = pin;
}

bool Music::isPlaying(){
    return _isPlaying;
}



void Music::play(int melody[], int notes, int tempo, int repeat, int pitchShift){
    _isPlaying = true;
    _tempo = tempo;
    _melody = melody;
    _notes = notes;
    _currentNote = 0;
    _noteStartTime = 0;
    _repeat = repeat;
    _pitchShift = pitchShift;
}

void Music::stop(){
  if(_isPlaying) {
    noTone(_pin);
  }
  _isPlaying = false;
}

void Music::loop(){
  unsigned long now = millis();
  int divider = 0;
  int noteDuration = 0;
  if(!_isPlaying) {
    return;
  }
  if(_currentNote < _notes * 2) {
    // iterate over the notes of the melody. 
    // Remember, the array is twice the number of notes (notes + durations)
    // calculates the duration of each note
    _wholenote = (60000 * 4) / _tempo;
    divider = _melody[_currentNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (_wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (_wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    if(_noteStartTime == 0) {
      // we only play the note for 90% of the duration, leaving 10% as a pause
      int freq = _melody[_currentNote] + _pitchShift;
      if(freq < 50) {
        freq = 50;
      }
      if(freq > 15000) {
        freq = 15000;
      }
      tone(_pin, freq, noteDuration*0.9);
      _noteStartTime = millis();
    }
    else if(millis()-_noteStartTime > noteDuration) {
      // Wait for the specief duration before playing the next note.
      // stop the waveform generation before the next note.
      noTone(_pin);
      _currentNote += 2;
      _noteStartTime = 0;
    }
  }
  else if(_repeat != 0) {
    if(_repeat > 0) {
      _repeat--;
    }
    _currentNote = 0;
  }
}
