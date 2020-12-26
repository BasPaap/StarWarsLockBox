#include "Sound.h"

Bas::Sound::Sound(int speakerPin, unsigned char const* soundData, int soundDataLength) : speakerPin{ speakerPin }, soundData{ soundData }, soundDataLength{ soundDataLength }, sample{ 0 }
{
    if (this->speakerPin != 3 && this->speakerPin != 11)
    {
        Serial.println("ERROR: the speaker pin can only be 3 or 11 because the other PWM pins are taken by two timers.");
    }    
}
   
void Bas::Sound::play()
{
    this->lastSample = pgm_read_byte(&this->soundData[this->soundDataLength - 1]);
    pinMode(this->speakerPin, OUTPUT);

    // Set up Timer 2 to do pulse width modulation on the speaker
    // pin.

    // Use internal clock (datasheet p.160)
    ASSR &= ~(_BV(EXCLK) | _BV(AS2));

    // Set fast PWM mode  (p.157)
    TCCR2A |= _BV(WGM21) | _BV(WGM20);
    TCCR2B &= ~_BV(WGM22);

    if (this->speakerPin == 11) {
        // Do non-inverting PWM on pin OC2A (p.155)
        // On the Arduino this is pin 11.
        TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
        TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
        // No prescaler (p.158)
        TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

        // Set initial pulse width to the first sample.
        OCR2A = pgm_read_byte(&this->soundData[0]);
    }
    else {
        // Do non-inverting PWM on pin OC2B (p.155)
        // On the Arduino this is pin 3.
        TCCR2A = (TCCR2A | _BV(COM2B1)) & ~_BV(COM2B0);
        TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0));
        // No prescaler (p.158)
        TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

        // Set initial pulse width to the first sample.
        OCR2B = pgm_read_byte(&this->soundData[0]);
    }
    // Set up Timer 1 to send a sample every interrupt.
    cli();

    // Set CTC mode (Clear Timer on Compare Match) (p.133)
    // Have to set OCR1A *after*, otherwise it gets reset to 0!
    TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
    TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));

    // No prescaler (p.134)
    TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set the compare register (OCR1A).
    // OCR1A is a 16-bit register, so we have to do this with
    // interrupts disabled to be safe.
    OCR1A = F_CPU / SAMPLE_RATE;    // 16e6 / 8000 = 2000

    // Enable interrupt when TCNT1 == OCR1A (p.136)
    TIMSK1 |= _BV(OCIE1A);

    this->lastSample = pgm_read_byte(&this->soundData[this->soundDataLength - 1]);
    this->sample = 0;
    sei();
}

void Bas::Sound::stopPlayback()
{
    // Disable playback per-sample interrupt.
    TIMSK1 &= ~_BV(OCIE1A);

    // Disable the per-sample timer completely.
    TCCR1B &= ~_BV(CS10);

    // Disable the PWM timer.
    TCCR2B &= ~_BV(CS10);

    digitalWrite(speakerPin, LOW);
}

void Bas::Sound::onInterrupt()
{
    if (this->sample >= this->soundDataLength) {
        if (this->sample == this->soundDataLength + this->lastSample) {
            this->stopPlayback();
        }
        else {
            // Ramp down to zero to reduce the click at the end of playback.
            OCR2A = this->soundDataLength + this->lastSample - this->sample;
        }
    }
    else {
        OCR2A = pgm_read_byte(&this->soundData[this->sample]);
    }

    ++this->sample;
}
