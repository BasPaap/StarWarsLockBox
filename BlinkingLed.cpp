#include "BlinkingLed.h"


Bas::BlinkingLed::BlinkingLed(int pin, int numMillisecondsOn, int numMillisecondsOff) : pin{ pin }, numMillisecondsOn{numMillisecondsOn}, numMillisecondsOff{numMillisecondsOff}
{
}

void Bas::BlinkingLed::Initialize()
{
    pinMode(this->pin, OUTPUT);
}

void Bas::BlinkingLed::Update()
{
    static int millisToSpendInState = this->numMillisecondsOn;
    static long previousMillis;

    if (this->isRunning && (millis() - previousMillis) >= millisToSpendInState)
    {
        if (digitalRead(this->pin) == HIGH)
        {
            millisToSpendInState = this->numMillisecondsOff;
        }
        else
        {
            millisToSpendInState = this->numMillisecondsOn;
        }

        digitalWrite(this->pin, !digitalRead(this->pin));
        previousMillis = millis();
    }
}

void Bas::BlinkingLed::TurnOn()
{
    Serial.print("Turning BlinkingLed on on pin ");
    Serial.println(this->pin);
    digitalWrite(this->pin, LOW);
    this->isRunning = true;
}


void Bas::BlinkingLed::TurnOff()
{
    Serial.print("Turning BlinkingLed off on pin ");
    Serial.println(this->pin);
    digitalWrite(this->pin, LOW);
    this->isRunning = false;
}
