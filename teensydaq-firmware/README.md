# TeensyDAQ Firmware
A fast two channel DAQ for the Teensy platform. The DAQ outputs a stream of comma separated data with each entry in the following format: ID:TimeStamp:ADCValue. By default, each channel reads data at 100kHz. To turn the DAQ output on or off, send a non-empty serial command to the device. By default, the serial connection baud rate is 2MHz and the GPIO pins used by the ADC are pins 14 for ADC0 and 15 for ADC1.
# TeensyDAQ Reference
- [Type Aliases](include/Project_Aliases.md)
- [ADCReading](lib/ADCPipe//ADCReading.md)
- [ADCPipe](lib/ADCPipe/ADCPipe.md)
- [StatusLED](lib/StatusLED/StatusLED.md)