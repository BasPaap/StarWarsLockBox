#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

namespace Bas
{
	// Encapsulates a blinking LED
	class BlinkingLed
	{
		int pin;
		int numMillisecondsOn;
		int numMillisecondsOff;
		bool isRunning = false;
	public:
		BlinkingLed(int pin, int numMillisecondsOn, int numMillisecondsOff);
		void Update();
		void Start();
		void Stop();
	};
}