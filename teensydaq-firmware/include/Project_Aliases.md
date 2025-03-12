# Project Aliases
Common type alias for consistant and more human readable code.
## Table of Contents
- [TimeStamp](#timestamp)
- [ADCValue](#adcvalue)
- [Pin](#pin)
## TimeStamp
A volatile unsigned 32 bit integer. Primarilly to be used with the millis() or micros() functions.
## ADCValue
A volatile unsigned 16 bit integer. This is the minimium required size for any ADC reading on the teensy platform. Typical measurments will be 8-12 bits.
## Pin
An unsigned 8 bit integer. 