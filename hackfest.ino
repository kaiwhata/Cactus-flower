//Name: Cactus Flower Indoor Gardening System
//--------------------------------------------------------------
#include <Servo.h> 
#include <dht.h>
#define wtrPin A1  //water sensor pin
#define dht_dpin A0 // Humid and temperature sensor
#define controlPin A5  // connects to raspberry pi for manual watering of plants
#define pumpPin 9  //pin of the pump

//boolean pump = false;  //for furthere development so that it may print if pump is on or not.
dht DHT;  
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
}

void loop()
{
//  if(analogRead(controlPin) > 200){    //for manual watering of plants from raspberry pi
//    waterplant();
//  }
 readSensors();
 checkWater(); 
 checkHumidity();
 checkTemp();
 printData();
 delay(1000);
} 

void printData(){
 //  Serial.println(analogRead(controlPin));
 Serial.print("water Sensor: ");
 Serial.println(wtrVal); // print the value:
 Serial.print("Current humidity = ");
 Serial.print(DHT.humidity);  
 Serial.println("%  ");
 Serial.print("temperature = ");
 Serial.print(DHT.temperature); 
 Serial.println("C  ");
 Serial.println("-----------------------------------------------");
}

void readSensors(){
 wtrVal = analogRead(wtrPin); // read the analog 1 in value:
 DHT.read11(dht_dpin);  
 printData();
}

void checkWater(){
 if (wtrVal > 400){
   Serial.print("pump:");
   Serial.println(wtrVal);
   openPump();
   delay(5000);
   closePump();
 }
 delay(100);
}

void waterplant(){
  openPump();
  delay(500);
  closePump();
  Serial.println("Watering plants");
}

void checkHumidity(){
  readSensors();
 if (DHT.humidity<20 && wtrVal > 200){  //if humidity is too low, and the soil is not too wet, open the
   openPump();                          //water system to increase humidity so the garden isn't too dry
   delay(3000);
   closePump();
 } 
 delay(100);
}

void checkTemp(){        //if the garden is too cold, heat it up to a suitable temperature
  readSensors();
  if (DHT.temperature<13){
   //heater on 
  } else if (DHT.temperature > 20){
   //heater off 
  }
 delay(100);
}

void openPump(){
  digitalWrite(pumpPin, LOW);
}

void closePump(){
   digitalWrite(pumpPin, HIGH);
}

