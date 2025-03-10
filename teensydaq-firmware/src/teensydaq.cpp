#include "ADC.h"
#include "Arduino.h"

using TimeStamp = volatile uint32_t;
using ADCValue = volatile uint16_t;
using Pin = uint8_t;

ADC* adc = new ADC();

struct ADCReading
{
    TimeStamp timestamp;
    ADCValue value;
};

class StatusLED
{
public:        // Constructor and Destructor
    StatusLED(Pin pin = LED_BUILTIN) : m_pin(pin) { pinMode(m_pin, OUTPUT); }

    ~StatusLED() = default;

public:        // Methods
    void on() { digitalWrite(m_pin, HIGH); }

    void off() { digitalWrite(m_pin, LOW); }

    void toggle() { digitalWrite(m_pin, !digitalRead(m_pin)); }

    void set(bool state) { digitalWrite(m_pin, state); }

private:        // Fields
    const Pin m_pin;
};

StatusLED led;

class ADCPipe
{
    typedef void (*Callback)(void);

public:        // Constructor and Destructor
    ADCPipe(ADC_Module* mod, Pin pin, int sampleRate, int printRate, Callback sampleCallback, Callback printCallback,
            Pin clk = 11)
        : m_mod(mod),
          m_pin(pin),
          m_sampleRate(sampleRate),
          m_printRate(printRate),
          m_clock(false),
          m_newData(false),
          m_sampleCallback(sampleCallback),
          m_printCallback(printCallback)
    {
        pinMode(m_pin, INPUT);
        initClock(clk);
    }

    ~ADCPipe() = default;

public:        // Fields
    ADCReading reading;
    int averages = 0;
    int resolution = 13;
    ADC_settings::ADC_CONVERSION_SPEED conversionSpeed;
    ADC_settings::ADC_SAMPLING_SPEED samplingSpeed;
    static bool writeEnable;

public:        // Methods
    void start()
    {
        m_mod->setAveraging(averages);
        m_mod->setResolution(resolution);
        m_mod->setConversionSpeed(conversionSpeed);
        m_mod->setSamplingSpeed(samplingSpeed);
        m_mod->startContinuous(m_pin);

        m_sampleTimer.begin(m_sampleCallback, m_sampleRate);
        m_printTimer.begin(m_printCallback, m_printRate);
    }

    void stop()
    {
        m_sampleTimer.end();
        m_printTimer.end();
        m_mod->stopContinuous();
    }

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

    const Callback m_sampleCallback;
    const Callback m_printCallback;
    IntervalTimer m_sampleTimer;
    IntervalTimer m_printTimer;

private:        // Methods
    static void initClock(Pin p)
    {
        if (!s_clkInit)
        {
            s_clkPin = p;
            pinMode(s_clkPin, OUTPUT);
            s_clkInit = true;
        }
    }
};

Pin ADCPipe::s_clkPin = 0;
bool ADCPipe::s_clkInit = false;
bool ADCPipe::writeEnable = false;

ADCPipe* adc0Pipe = nullptr;
ADCPipe* adc1Pipe = nullptr;

void sample0()
{
    adc0Pipe->sample();
}

void print0()
{
    adc0Pipe->print();
}

void sample1()
{
    adc1Pipe->sample();
}

void print1()
{
    adc1Pipe->print();
}

void setup()
{
    Serial.begin(2000000);
    while (!Serial);

    adc0Pipe = new ADCPipe(adc->adc0, A0, 4, 10, sample0, print0);
    adc0Pipe->averages = 0;
    adc0Pipe->resolution = 13;
    adc0Pipe->conversionSpeed = ADC_settings::ADC_CONVERSION_SPEED::HIGH_SPEED;
    adc0Pipe->samplingSpeed = ADC_settings::ADC_SAMPLING_SPEED::VERY_HIGH_SPEED;

    adc1Pipe = new ADCPipe(adc->adc1, A1, 4, 10, sample1, print1);
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
        led.set(ADCPipe::writeEnable = !ADCPipe::writeEnable);
        adc0Pipe->resetClock();
        adc1Pipe->resetClock();
        digitalWriteFast(ADCPipe::clockPin(), LOW);
    }
}