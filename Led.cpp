#include "Led.h"

Bas::Led::Led(int pin) : pin{ pin }
{
}

void Bas::Led::initialize()
{
    pinMode(this->pin, OUTPUT);
}

void Bas::Led::turnOn()
{    
    digitalWrite(this->pin, HIGH);
}


void Bas::Led::turnOff()
{    
    digitalWrite(this->pin, LOW);
}
