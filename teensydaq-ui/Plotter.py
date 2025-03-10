import sys
import os

from matplotlib.figure import Figure
import matplotlib 
import matplotlib.pyplot as plt

class Plotter:
    def __init__(self: any, 
                 frequency: float, 
                 filename: str, 
                 minV: float, 
                 maxV: float, 
                 resolution: int):
        self.frequency = frequency
        self.filename = filename
        self.min = minV
        self.max = maxV
        self.resolution = resolution
        self.data = []
    
    def scale(self: any, value: float) -> float:
        m = (self.max - self.min) / ((2**self.resolution) - 1)
        return m * value + self.min
    
    def usToS(self: any, us: int) -> float:
        return us / 1000000
    
    def load(self: any) -> None:
        with open(self.filename, 'r') as f:
            # read up to ','
            self.data = [x for x in f.read().split(',')]
    
    def plot(self: any) -> None:
        # Data entries are in the format ID:Time(us):Value
        # Split the data into x and y for each ID
        x = []
        y = []
        idMin = 0
        idMax = 1
        for i in range(idMin, idMax + 1):
            x.append([])
            y.append([])
        for i in range(0, len(self.data)):
            entry = self.data[i].split(':')
            # print("Entry: ", entry)
            index = int(entry[0])
            if index < idMin or index > idMax:
                continue
            if len(entry) != 3:
                print("Invalid entry: ", entry)
                continue
            x[index].append(self.usToS(float(entry[1])))
            y[index].append(self.scale(float(entry[2])))

        # create plot
        fig, ax = plt.subplots(idMax - idMin + 1)
        for i in range(idMin, idMax + 1):
            print("Plotting ", len(x[i]), " points for ADC ", i)
            ax[i].plot(x[i], y[i], label='ADC ' + str(i))
        plt.show()

def main():
    if len(sys.argv) != 6:
        print("Usage: python3 Plotter.py <frequency> <filename> <min> <max> <resolution>")
        sys.exit(1)
    frequency = float(sys.argv[1])
    filename = sys.argv[2]
    minV = float(sys.argv[3])
    maxV = float(sys.argv[4])
    resolution = int(sys.argv[5])
    plotter = Plotter(frequency, filename, minV, maxV, resolution)
    plotter.load()
    plotter.plot()

if __name__ == "__main__":
    main()