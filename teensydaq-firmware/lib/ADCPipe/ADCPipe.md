# ADCPipe
ADCPipe takes control of an ADC_Module to asyncronously pipe data from it to the Serial Port.

## Table of Contents
- [Public Fields](#public-fields)
  - ADCReading [reading](#adcreading-reading)
  - int [averages](#int-averages)
  - int [resolution](#int-resolution)
  - ADC_settings::ADC_CONVERSION_SPEED [conversionSpeed](#adc_settingsadc_conversion_speed-conversionspeed)
  - ADC_settings::ADC_SAMPLING_SPEED [samplingSpeed](#adc_settingsadc_sampling_speed-samplingspeed)
- [Public Methods](#public-methods)
  - [ADCPipe(ADC_Module*, Pin, int, int, Pin)](#adcpipeadcpipeadc_module-mod-pin-pin-int-samplerate-int-printrate-pin-clk--11)
  - [~ADCPipe()](#adcpipeadcpipe-1)
  - void [start()](#void-adcpipestart)
  - void [stop()](#void-adcpipestop)
  - void [resetClock()](#void-adcpiperesetclock)
- [Static Public Fields](#static-public-fields)
  - bool [writeEnable](#bool-writeenable)
- [Static Public Methods](#static-public-methods)
  - Pin [clockPin()](#pin-adcpipeclockpin)

## Public Fields
### [ADCReading](ADCReading.md) reading
The last value read from the ADC Module.
### int averages
The number of samples for the ADC Module to take before reporting a final reading.
### int resolution
The bit length of the reading. 8-16 bits.
### ADC_settings::ADC_CONVERSION_SPEED conversionSpeed
Sets the ADC clock speed.

Available options:
- VERY_LOW_SPEED
- LOW_SPEED
- MED_SPEED
- HIGH_SPEED
- VERY_HIGH_SPEED

**Note:** Exact speeds are dependent on the [resolution](#int-resolution) and the system clock speed.
### ADC_settings::ADC_SAMPLING_SPEED samplingSpeed
Selects the number of ADC clock cycles used per sample.

Available options:
- VERY_LOW_SPEED
- LOW_SPEED
- LOW_MED_SPEED
- MED_SPEED
- MED_HIGH_SPEED
- HIGH_SPEED
- HIGH_VERY_HIGH_SPEED
- VERY_HIGH_SPEED
## Public Methods
### ADCPipe::ADCPipe(ADC_Module* mod, [Pin](../../include/Project_Aliases.md) pin, int sampleRate, int printRate, [Pin](../../include/Project_Aliases.md) clk = 11)
Args:
- mod: Pointer to an ADC_Module. These are predefined in ADC.h with adc0 and adc1 being the available options. This arg must never be null, must point to one of the ADC_Module objects, and no two pipes can point to the same module.
- pin: The GPIO pin that the ADC_Module will be attached to.
- sampleRate: The time interval, in microseconds, at which the ADC should be polled for new values.
- printRate: The time interval, in microseconds, at which data should be written to the serial bus, given a new value is available.
- clk: The GPIO pin used as an output clock reference that toggles state whenever new data is written to the serial bus.
### ADCPipe::~ADCPipe()
Calls the stop method.
### void ADCPipe::start()
Configures the ADC Module and starts continuous asyncronous measurements.
### void ADCPipe::stop()
Stops continuous asyncronous measurements.
### void ADCPipe::resetClock()
Sets output clock pin to low.
## Static Public Fields
### bool writeEnable
Enables all ADCPipe objects to write to the serial buffer.
## Static Public Methods
### Pin ADCPipe::clockPin()
Returns the clock pin.