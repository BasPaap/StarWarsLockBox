#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#define SAMPLE_RATE 8000;

namespace Bas
{
	class Sound
	{
		int speakerPin;
		unsigned char const* soundData = 0;
		int soundDataLength = 0;
		byte lastSample;
		volatile uint16_t sample;
		
		void stopPlayback();
		
	public:
		Sound(int speakerPin, unsigned char const* soundData, int soundDataLength);
		void play();
		void onInterrupt();
	};
}
