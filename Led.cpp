#include "Led.h"

Bas::Led::Led(int pin) : pin{ pin }
{
}

void Bas::Led::Initialize()
{
    pinMode(this->pin, OUTPUT);
}

void Bas::Led::TurnOn()
{    
    digitalWrite(this->pin, HIGH);
}


void Bas::Led::TurnOff()
{    
    digitalWrite(this->pin, LOW);
}
