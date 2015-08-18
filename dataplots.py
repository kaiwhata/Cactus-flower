from matplotlib import pylab
import matplotlib.pyplot as plt

ifile = open('flowers.txt', 'r')
temp = []
water = []
humidity = []

for line in ifile.readlines():
    line = line.strip()
    print line[:5]
    if line[:5] == 'water':
        water.append(float(line.split(':')[-1]))
    elif line[:5] == 'Curre':
        humidity.append(float(line.split('=')[-1][:-1]))
    elif line[:5] == 'tempe':
        temp.append(float(line.split('=')[-1][:-1]))

print temp
print water
print humidity

pylab.figure(1)
fig, ax1 = plt.subplots()
pylab.plot(range(len(temp)), temp, 'ko-')
pylab.xlabel('Time')
pylab.ylabel('Temp')
pylab.ylim(0, 100)
ax2 = ax1.twinx()
ax2.plot(range(len(humidity)), humidity, 'bo-')
ax2.set_ylabel('Humidity')
ax2.set_ylim(0, 100)
pylab.savefig('temperature.png')
pylab.show()

pylab.figure(2)
pylab.plot(range(len(water)), water, 'ko-')
pylab.xlabel('Time')
pylab.ylabel('Water')
pylab.ylim(0, 1024)
pylab.savefig('water.png')
pylab.show()

"""
pylab.figure(3)
pylab.plot(range(len(humidity)), humidity, 'ko-')
pylab.xlabel('Time')
pylab.ylabel('Humidity')
pylab.ylim(0, 100)
pylab.savefig('Humidity.png')
pylab.show()
"""      
                    
