import serial
import time
import csv
import matplotlib
matplotlib.use("tkAgg")
import matplotlib.pyplot as plt
import numpy as np

ser = serial.Serial('/dev/ttyUSB0')
ser.flushInput()

plot_window = 6000
y_var = np.array(np.zeros([plot_window]))

plt.ion()
fig, ax = plt.subplots()
line, = ax.plot(y_var)

while True:
    try:
        ser_bytes = ser.readline()
        try:
            temp = float(int(ser_bytes.decode("utf-8")))/10
            set_point = 80
            erro = set_point-temp

            print("T:{:10.2f}\tST:{:10.2f}\tER:{:10.2f}".format(temp, set_point, erro))
        except:
            continue
        with open("pid_10_10_5.csv","a") as f:
            writer = csv.writer(f,delimiter=",")
            writer.writerow([time.time(),temp,set_point,erro])

        y_var = np.append(y_var,temp)
        y_var = y_var[1:plot_window+1]

        line.set_ydata(y_var)

        ax.relim()
        ax.autoscale_view()
        fig.canvas.draw()
        fig.canvas.flush_events()
    except:
        print("Keyboard Interrupt")
        break