# TeensyDAQ User Interfaces
Utilities for controlling the DAQ and for viewing data files. A python virtual environment is provided in the TeensyDAQ folder. Data files are stored in the output folder. If the output folder is missing, it will be generated when a new data file is created.
## Applications
- SerialGUI.py: Utility for communicating with the teensy. Used to view and record raw data.
- Plotter.py: Utility for viewing previously recorded data. Provides tools for the raw data to be scaled from ADC values to actual voltages.
- SerialUtils.py: For internal use of SerialGUI.py