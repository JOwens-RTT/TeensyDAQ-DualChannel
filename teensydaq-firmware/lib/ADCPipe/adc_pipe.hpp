#ifndef TEENSY_DAQ_LIB_ADC_PIPE_H
#define TEENSY_DAQ_LIB_ADC_PIPE_H

#include <ADC.h>
#include <Arduino.h>
#include <proj_aliases.hpp>

namespace TeensyDAQ
{

struct ADCReading
{
    TimeStamp timestamp;
    ADCValue value;
};

class ADCPipe
{
    typedef void (*Callback)(void);

public:        // Constructor and Destructor
    ADCPipe(ADC_Module* mod, Pin pin, int sampleRate, int printRate, Pin clk = 11);

    ~ADCPipe() = default;

public:        // Fields
    ADCReading reading;
    int averages = 0;
    int resolution = 13;
    ADC_settings::ADC_CONVERSION_SPEED conversionSpeed;
    ADC_settings::ADC_SAMPLING_SPEED samplingSpeed;
    static bool writeEnable;

public:        // Methods
    void start();

    void stop();

    inline void sample()
    {
        TimeStamp t = micros();
        if (m_mod->isComplete())
        {
            reading.timestamp = t;
            reading.value = m_mod->analogReadContinuous();
            m_newData = true;
        }
    }

    inline void print()
    {
        if (m_newData && writeEnable)
        {
            digitalWriteFast(s_clkPin, m_clock = !m_clock);
            m_newData = false;
            Serial.print(m_mod->ADC_num);
            Serial.print(':');
            Serial.print(reading.timestamp);
            Serial.print(':');
            Serial.println(reading.value);
        }
    }

    static Pin clockPin() { return s_clkPin; }

    void resetClock() { m_clock = false; }

private:        // Fields
    ADC_Module* m_mod;
    const Pin m_pin;
    const int m_sampleRate;
    const int m_printRate;
    static Pin s_clkPin;
    static bool s_clkInit;
    bool m_clock;
    bool m_newData;

    IntervalTimer m_sampleTimer;
    IntervalTimer m_printTimer;

private:        // Methods
    static void initClock(Pin p);
};

extern ADCPipe* adc0Pipe;
extern ADCPipe* adc1Pipe;

}        // namespace TeensyDAQ

#endif        // TEENSY_DAQ_LIB_ADC_PIPE_H