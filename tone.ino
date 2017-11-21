#include "pitches.h"

int LED1 = 12;
int LED2 = 11;
int LED3 = 10;
int melodyLength;
int lightNumber = 0;
int speakerPin = 8;

// notes in the melody:
int lowMelody[] = {
    NOTE_A2, NOTE_B2, NOTE_C3, NOTE_D3, NOTE_E3, 0, NOTE_C3, NOTE_DS3, NOTE_B2, NOTE_D3, NOTE_C3, NOTE_A2, NOTE_B2, NOTE_C3, NOTE_D3, NOTE_E3, 0, NOTE_A3, NOTE_GS3,
    NOTE_A2, NOTE_B2, NOTE_C3, NOTE_D3, NOTE_E3, 0, NOTE_C3, NOTE_DS3, NOTE_B2, NOTE_D3, NOTE_C3,
    NOTE_A3, NOTE_GS3, NOTE_G3, NOTE_FS3, NOTE_F3, 0, 0, NOTE_E3, NOTE_A3};

// notes in the melody:
int highMelody[] = {
    NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, 0, NOTE_C4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, 0, NOTE_A4, NOTE_GS4,
    NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, 0, NOTE_C4, NOTE_DS4, NOTE_B3, NOTE_D4, NOTE_C4,
    NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_FS4, NOTE_F4, 0, 0, NOTE_E4, NOTE_A4};

// notes in the melody:
int superHighMelody[] = {
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, 0, NOTE_C5, NOTE_DS5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, 0, NOTE_A5, NOTE_GS5,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, 0, NOTE_C5, NOTE_DS5, NOTE_B4, NOTE_D5, NOTE_C5,
    NOTE_A5, NOTE_GS5, NOTE_G5, NOTE_FS5, NOTE_F5, 0, 0, NOTE_E5, NOTE_A5};

// notes in the melody:
int ultraHighMelody[] = {
    NOTE_A6, NOTE_B6, NOTE_C7, NOTE_D7, NOTE_E7, 0, NOTE_C7, NOTE_DS7, NOTE_B6, NOTE_D7, NOTE_C7, NOTE_A6, NOTE_B6, NOTE_C7, NOTE_D7, NOTE_E7, 0, NOTE_A7, NOTE_GS7,
    NOTE_A6, NOTE_B6, NOTE_C7, NOTE_D7, NOTE_E7, 0, NOTE_C7, NOTE_DS7, NOTE_B6, NOTE_D7, NOTE_C7,
    NOTE_A7, NOTE_GS7, NOTE_G7, NOTE_FS7, NOTE_F7, 0, 0, NOTE_E7, NOTE_A7};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    8, 16, 8, 16, 8, 16, 6, 6, 6, 6, 6, 8, 16, 8, 16, 8, 16, 6, 2,
    8, 16, 8, 16, 8, 16, 6, 6, 6, 6, 6,
    8, 16, 8, 16, 8, 4, 6, 6, 8};

void setup()
{
  Serial.begin(9000);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  melodyLength = sizeof(noteDurations) / sizeof(int);
}

void loop()
{
  playRandomMelody();
}

void playMelody(int melody[])
{
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < melodyLength; thisNote++)
  {
    int light = nextLight();
    digitalWrite(light, HIGH);
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000 / 8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    noTone(speakerPin);
    digitalWrite(light, LOW);
    lightNumber++;
    if (lightNumber == 3)
    {
      lightNumber = 0;
    }
  }
}

// Plays one of the melodies defined above.
void playRandomMelody()
{
  int random = rand() % 4;
  switch (random)
  {
  case 0:
    playMelody(lowMelody);
    delay(1000);
    break;
  case 1:
    playMelody(highMelody);
    delay(1000);
    break;
  case 2:
    playMelody(superHighMelody);
    delay(1000);
    break;
  case 3:
    playMelody(ultraHighMelody);
    delay(1000);
    break;
  }
}

// chooses the next led in the sequence
int nextLight()
{
  switch (lightNumber)
  {
  case 0:
    return LED1;
  case 1:
    return LED2;
  case 2:
    return LED3;
  }
}
