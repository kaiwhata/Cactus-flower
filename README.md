# Cactus-flower
Code for web enabled, automatic plant watering system

This code was developed by Team Cactus Flowers from the Summer of Tech Wellington Hardware Hackathon on Saturday 15th August 2015. 
Team members were: Divya, Michael, Bonnie and Shaetrun with some mentorship by Elf.

Code uses a rpi as a webserver using first raw html (plot.html) then a Bottle python implementation of a website to
enable external control of the pi. 
The pi communicated to an arduino via serial, reading measurements of temperature, humidity 
and water from relelvant sensors. We also attempted to add control of the arduino by the pi using GPIO communication.
Currently this is bugged (possibly due to PWM on the pin used for comm - currently pin 2).

The main.py file currently polls the arduino serial collection, appends to a text data file, processing the data file
and uses the matplotlib library to generate and save plots of the data.

Arduino code reponds to the water sensor and control a relay system to drive a 12V air pump to pump water into the plants.

Equipment:
DHT22 Temperature and Humidity sensor (https://nicegear.co.nz/sensors/humidity-and-temperature-sensor-dht22/)
Soil Moisture Sensor (https://nicegear.co.nz/sensors/soil-moisture-sensor-arduino-compatible/)
Arduino Uno
RPi 2 -> GPIO output to Arduino on GPIO 18

Suggested edits to come are:
* [COMPLETE] adding some failsafes for the water pumping (i.e. when the sensor is compoletely dry)
* [COMPLETE] Fixing the GPIO comms with the Arduino and RPi
* [COMPLETE] Having the Rpi return the correct serial interface with the arduino
* [COMPLETE] Add list for equipment/specific sensors used.
* Adding an Rpi infra-red camera to the mix to get infragrams of the plants
* Adding control of the arduino program via node.js system and johnny 5.
