# TeensyDAQ-DualChannel
A modified version of [TeensyDAQ-Fast](https://github.com/kongmunist/TeensyDAQ-Fast) that allows for two signals to be recorded simultainiously. 

## Brief summary
The project contains Teensy firmware in a [PlatformIO project](teensydaq-firmware/README.md) and a set of [Python UI applications](teensydaq-ui/README.md) for recording and viewing the data.

 # Usage
1. Clone this repo. 
2. Open the VSCode workspace.
3. Install the recommended plugins.
4. Flash the firmware to your desired Teensy. You will need to edit the [configuration file](teensydaq-firmware/platformio.ini) if you are not using a Teensy 4.1.
5. Connect your signals to pins 14 (Channel 0) and 15 (Channel 1). Make sure your signals stay in the 0 to 3.3V range. Extra hardware may be required.
6. Run SerialGUI.py. 
7. Click the "Start Recording" button to start and stop the recording. If you want a custom file name, type it in the box and hit enter. The GUI is slightly bugged and may not update correctly.
 
Alternatively, you can use just the Teensy code and record the serial output on the computer any way you want. A convenient tool for Mac/Linux computers [here](https://medium.com/@kongmunist/serial-logging-in-processing-using-shell-commands-183ea8be6791).

 # Output clock
The Teensy toggles pin 11 whenever it sends a measurement to the computer. This will likely be split into two pins, one for each channel.
