# StatusLED
## Table of Contents
- [Public Methods](#public-methods)
  - [StatusLED(Pin)](#statusledstatusledpin-pin--led_builtin)
  - [~StatusLED()](#statusledstatusled)
  - void [on()](#void-statusledon)
  - void [off()](#void-statusledoff)
  - void [toggle()](#void-statusledtoggle)
  - void [set(bool)](#void-statusledsetbool-state)
## Public Methods
### StatusLED::StatusLED([Pin](../../include/Project_Aliases.md) pin = LED_BUILTIN)
Initializes the LED pin. Can be used for any external LED but assumes that a HIGH state coresponds to the LED being on. By default, the built in LED is used, typically pin 13.
### StatusLED::~StatusLED()
Default destructor.
### void StatusLED::on()
Turns on the LED.
### void StatusLED::off()
Turns off the LED.
### void StatusLED::toggle()
Toggles the LED.
### void StatusLED::set(bool state)
Sets the LED to a specific state. True is on (HIGH), and false is off (LOW).