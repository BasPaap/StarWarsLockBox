#pragma once
namespace Bas
{
	class Led
	{
		int pin;
	public:
		Led(int pin);
		void initialize();
		void turnOn();
		void turnOff();
	};
}

