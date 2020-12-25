/*
	Name:       Bas.StarWarsLockBox.ino
	Created:	19-12-2020 00:03:15
	Author:     DESKTOP-BAS\baspa
*/

#include "Sound.h"
#include "BlinkingLed.h"
#include "Led.h"
#include "UnlockSoundData.h"

const int speakerPin = 11;  // Can be either 3 or 11, two PWM outputs connected to Timer 2
const int greenLedPin = 2;
const int redLedPin = 3;
const int buttonPin = 4;

Bas::Sound unlockSound(speakerPin, unlockSoundData, sizeof(unlockSoundData));
Bas::Led greenLed(greenLedPin);
Bas::BlinkingLed redLed(redLedPin, 200, 400);

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);	
	
	greenLed.Initialize();
	redLed.Initialize();
	redLed.TurnOn();
}

// Add the main program code into the continuous loop() function
void loop()
{
}

// This is called at 8000 Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {
	unlockSound.onInterrupt();
}