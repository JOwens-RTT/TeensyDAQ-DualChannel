#include "adc_pipe.hpp"

using namespace TeensyDAQ;

Pin ADCPipe::s_clkPin = 0;
bool ADCPipe::s_clkInit = false;
bool ADCPipe::writeEnable = false;

ADCPipe::ADCPipe(ADC_Module* mod, Pin pin, int sampleRate, int printRate, Pin clk)
    : m_mod(mod), m_pin(pin), m_sampleRate(sampleRate), m_printRate(printRate), m_clock(false), m_newData(false)
{
    pinMode(m_pin, INPUT);
    initClock(clk);
}

void ADCPipe::start()
{
    m_mod->setAveraging(averages);
    m_mod->setResolution(resolution);
    m_mod->setConversionSpeed(conversionSpeed);
    m_mod->setSamplingSpeed(samplingSpeed);
    m_mod->startContinuous(m_pin);

    m_sampleTimer.begin([this]() { sample(); }, m_sampleRate);
    m_printTimer.begin([this]() { print(); }, m_printRate);
}

void ADCPipe::stop()
{
    m_sampleTimer.end();
    m_printTimer.end();
    m_mod->stopContinuous();
}

void ADCPipe::initClock(Pin p)
{
    if (!s_clkInit)
    {
        s_clkPin = p;
        pinMode(s_clkPin, OUTPUT);
        s_clkInit = true;
    }
}