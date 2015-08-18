//Name: Cactus Flower Indoor Gardening System
//--------------------------------------------------------------
#include <Servo.h> 
#include "DHT.h"
#define wtrPin A1  //water sensor pin
#define DHTPIN 2
#define controlPin A5  // connects to raspberry pi for manual watering of plants
#define pumpPin 9  //pin of the pump

//boolean pump = false;  //for furthere development so that it may print if pump is on or not.
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);
int wtrVal = 0;
//-------------------------------------------------------------
void setup()
{
// initialize serial communications at 9600 bps:
 Serial.begin(9600);
 pinMode(wtrPin, INPUT);
 pinMode(pumpPin, OUTPUT);
 pinMode(controlPin, INPUT);
 closePump();
 pinMode(13, OUTPUT);
 dht.begin();
}

void loop()
{
  if(analogRead(controlPin) > 700){    //for manual watering of plants from raspberry pi
//    waterplant();
    Serial.println('Control Pin High');
    digitalWrite(13, HIGH); //signal light
    delay(10);
 } 
 readSensors();
 checkWater(); 
 checkHumidity();
 printData();
 delay(2000);
 digitalWrite(13, LOW); //signal light
} 

void printData(){
 //  Serial.println(analogRead(controlPin));
 Serial.print("Water Sensor: ");
 Serial.println(wtrVal); // print the value:
 Serial.print("Current humidity = ");
 Serial.print(dht.readHumidity());  
 Serial.println("%  ");
 Serial.print("temperature = ");
 Serial.print(dht.readTemperature()); 
 Serial.println("C  ");
 Serial.print("Pi Control Pin: ");
 Serial.println(analogRead(controlPin)); 
 Serial.println("-----------------------------------------------");
}

void readSensors(){
 wtrVal = analogRead(wtrPin); // read the analog 1 in value: 
 //printData();
}

void checkWater(){
  if (wtrVal == 0){
   Serial.println("Pump (failsafe)");
   closePump();
   delay(2000);
 }
 else if (wtrVal < 200){
   Serial.println("Pump (water ind.)");
   openPump();
   delay(2000);
   closePump();
 }
 delay(100);
}

void waterplant(){
  openPump();
  delay(5000);
  closePump();
  Serial.println("Pump (RPi)");
}

void checkHumidity(){
 //readSensors();
 if (dht.readHumidity()<20 && wtrVal < 400){  //if humidity is too low, and the soil is not too wet, open the
   Serial.println("Pump (Humidity)");
   openPump();                          //water system to increase humidity so the garden isn't too dry
   delay(3000);
   closePump();
 } 
 delay(100);
}

void openPump(){
  digitalWrite(pumpPin, LOW);
}

void closePump(){
   digitalWrite(pumpPin, HIGH);
}
