#ifndef TEENSY_DAQ_LIB_STATUS_LED_H
#define TEENSY_DAQ_LIB_STATUS_LED_H

#include <Arduino.h>
#include <proj_aliases.hpp>

namespace TeensyDAQ
{

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

}        // namespace TeensyDAQ

#endif        // TEENSY_DAQ_LIB_STATUS_LED_H