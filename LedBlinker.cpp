#include "LedBlinker.h"


Bas::LedBlinker::LedBlinker(int pin, int numMillisecondsOn, int numMillisecondsOff) : pin{ pin }, numMillisecondsOn{numMillisecondsOn}, numMillisecondsOff{numMillisecondsOff}
{
}

void Bas::LedBlinker::Update()
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


void Bas::LedBlinker::Start()
{
    Serial.print("Turning LedBlinker on on pin ");
    Serial.println(this->pin);
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, LOW);
    this->isRunning = true;
}


void Bas::LedBlinker::Stop()
{
    Serial.print("Turning LedBlinker off on pin ");
    Serial.println(this->pin);
    digitalWrite(this->pin, LOW);
    this->isRunning = false;
}
