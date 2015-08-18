from bottle import route, run, template, static_file
from matplotlib import pylab
import matplotlib.pyplot as plt
import serial, os
from time import sleep
import RPi.GPIO as GPIO


@route('/')
def hello():
    return "Hello World!"

@route('/getdata')
def get_data():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(18, GPIO.OUT)
    GPIO.output(18, False)
    
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600)
    except:
        print 'could not find arduino'
    try:
        my_file = open("flowers.txt", 'a')
        count = 0
        while count < 25:
            line = ser.readline()
            my_file.write(line)
            print(line)
            count = count + 1
        my_file.close()
    except:
        print 'couldnt write data to file'
    
    
    ifile = open('flowers.txt', 'r')
    temp = []
    water = []
    humidity = []

    for line in ifile.readlines():
        line = line.strip()
        print line
        if line[:5] == 'Water':
            try:
                water.append(float(line.split(':')[-1]))
            except:
                print 'serial error'
        elif line[:5] == 'Curre':
            try:
                humidity.append(float(line.split('=')[-1][:-1]))
            except:
                print 'serial error'
        elif line[:5] == 'tempe':
            try:
                temp.append(float(line.split('=')[-1][:-1]))
            except:
                print 'serial error'

    print temp
    print water
    print humidity

    pylab.figure(1)
    fig, ax1 = plt.subplots()
    pylab.plot(range(len(temp)), temp, 'ro-')
    pylab.xlabel('Time')
    pylab.ylabel('Temp')
    pylab.ylim(0, 100)
    ax2 = ax1.twinx()
    ax2.plot(range(len(humidity)), humidity, 'go-')
    ax2.set_ylabel('Humidity')
    ax2.set_ylim(0, 100)
    pylab.savefig('temperature.png')
    pylab.close()
    
    pylab.figure(2)
    pylab.plot(range(len(water)), water, 'bo-')
    pylab.xlabel('Time')
    pylab.ylabel('Water')
    pylab.ylim(0, 1024)
    pylab.savefig('water.png')
    
    ifile.close()
    
    return template("plot")

@route('/water')
def water():
    return static_file('water.png', root="/home/pi/Cactus_flowers")

@route('/temperature')
def temp():
    return static_file('temperature.png', root="/home/pi/Cactus_flowers")

@route('/flowers')
def flower():
    return static_file('flowers.txt', root="/home/pi/Cactus_flowers")

@route('/waterplants')
def waterplant():
    

    print "Pump On\n"
    GPIO.output(18, True)
    sleep(5)

    print "Pump Off\n"
    GPIO.output(18, False)
    return "Plant's have been watered. Go back to see new data!"
    

run(host='192.168.1.7', port=8080, debug=True)
