/*
	Name:       Bas.StarWarsLockBox.ino
	Created:	19-12-2020 00:03:15
	Author:     DESKTOP-BAS\baspa
*/

#include "Sound.h"
#include "BlinkingLed.h"
#include "Led.h"
#include "UnlockSoundData.h"
#include "Button.h"

const int speakerPin = 11;  // Can be either 3 or 11, two PWM outputs connected to Timer 2
const int greenLedPin = 2;
const int redLedPin = 3;
const int buttonPin = 4;
const unsigned long debounceDelay = 50;

Bas::Sound unlockSound(speakerPin, unlockSoundData, sizeof(unlockSoundData));
Bas::Led greenLed{ greenLedPin };
Bas::BlinkingLed redLed{ redLedPin, 200, 400 };
Bas::Button unlockButton{ buttonPin, debounceDelay };

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(9600);	
	
	unlockButton.initialize(onUnlockButtonPressed);
	greenLed.initialize();
	redLed.initialize();
	redLed.turnOn();
}

// Add the main program code into the continuous loop() function
void loop()
{
  unlockButton.update();
	redLed.update();
}


void onUnlockButtonPressed()
{
	redLed.turnOff();
	greenLed.turnOn();
	unlockSound.play();
}

// This is called at 8000 Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {
	unlockSound.onInterrupt();
}
