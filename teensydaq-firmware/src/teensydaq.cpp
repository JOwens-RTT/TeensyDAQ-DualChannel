#include "ADC.h"

#include <ADCPipe>
#include <Arduino.h>
#include <StatusLED>
#include <proj_aliases.hpp>

ADC* adc = new ADC();

TeensyDAQ::StatusLED led;

TeensyDAQ::ADCPipe* adc0Pipe = nullptr;
TeensyDAQ::ADCPipe* adc1Pipe = nullptr;

void setup()
{
    Serial.begin(2000000);
    while (!Serial);

    adc0Pipe = new TeensyDAQ::ADCPipe(adc->adc0, A0, 4, 10);
    adc0Pipe->averages = 0;
    adc0Pipe->resolution = 13;
    adc0Pipe->conversionSpeed = ADC_settings::ADC_CONVERSION_SPEED::HIGH_SPEED;
    adc0Pipe->samplingSpeed = ADC_settings::ADC_SAMPLING_SPEED::VERY_HIGH_SPEED;

    adc1Pipe = new TeensyDAQ::ADCPipe(adc->adc1, A1, 4, 10);
    adc1Pipe->averages = 0;
    adc1Pipe->resolution = 13;
    adc1Pipe->conversionSpeed = ADC_settings::ADC_CONVERSION_SPEED::HIGH_SPEED;
    adc1Pipe->samplingSpeed = ADC_settings::ADC_SAMPLING_SPEED::VERY_HIGH_SPEED;

    adc0Pipe->start();
    adc1Pipe->start();
}

void loop()
{
    if (Serial.available())
    {
        while (Serial.available()) Serial.read();
        led.set(TeensyDAQ::ADCPipe::writeEnable = !TeensyDAQ::ADCPipe::writeEnable);
        adc0Pipe->resetClock();
        adc1Pipe->resetClock();
        digitalWriteFast(TeensyDAQ::ADCPipe::clockPin(), LOW);
    }
}