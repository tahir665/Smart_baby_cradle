

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include "HX711.h"


SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int sensorPin = A13;
int sensorValue;
int limit = 300;
String tx_u="";
int a=0;
String Cry_1="0";
#include <dht.h>
#define dht_apin A14 // Analog Pin sensor is connected to

dht DHT;
#define cal1 -7100.0 
#define data1  6
#define sck  7

HX711 scale1;

byte weight;

#define DS18B20 A15
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
float bodytemperature;
int soundSensor=31;
String moist="";
String cry="";



unsigned previous_mills=0;
unsigned long current_mills_2=0;
const long interval=5000;

unsigned previous_mills_2=0;
const long interval_2=30000;

void setup() {
 Serial.begin(115200);
   Serial3.begin(19200);

 mySoftwareSerial.begin(9600);
 pinMode(soundSensor,INPUT);
 delay(1000);//Wait before accessing Sensor
 if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }
 myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  //Play the first mp3
 
scale1.begin(data1, sck);
scale1.set_scale(cal1); 
scale1.tare(); 
}

void loop() {



 DHT.read11(dht_apin);
// Serial.print("Current humidity = ");
// Serial.print(DHT.humidity);
// Serial.print("%  ");
// Serial.print("temperature = ");
// Serial.print(DHT.temperature); 
// Serial.println("C  ");
 sensorValue = analogRead(sensorPin); 
 if (sensorValue<limit) {
// Serial.println("Moisture Detected"); 
 moist="1";
 sendSMS1();
 }
 else {
 //Serial.println("Moisture Not Detected");
 moist="2"; 
 }
 sensors.requestTemperatures();
 bodytemperature = sensors.getTempCByIndex(0);
 if (bodytemperature>38){
  sendSMS2();
 }
 //Serial.println("bodytemperature");
 //Serial.println(bodytemperature);


int SensorData=digitalRead(soundSensor);
if(SensorData==1){
  
    
     cry="1";
     previous_mills_2=current_mills_2;
    if(Cry_1.toInt()==0)
    {
      Cry_1="1";
      }
   //Serial.println("Crying");
   myDFPlayer.play(1);
   sendSMS();
   
   }
//   else{
//     //   Serial.println("Not Crying");
//     //cry="2";  
//     
//    
//    }

weight=scale1.get_units();
if(cry=="1")
{
  current_mills_2=millis();

  if(current_mills_2-previous_mills_2>=interval_2){
  a=0;
  cry="0";
  Cry_1="0";
  myDFPlayer.play(2);
 }
  }
  
    
unsigned long current_mills=millis();

if(current_mills-previous_mills>=interval){
   previous_mills=current_mills;
   senddata();
   
   }
 
   
}
 void senddata(){
   //making data in the form of string for wifimodule// 
tx_u+=String(DHT.humidity);
tx_u+=':';
tx_u+=String(DHT.temperature);
tx_u+=':';
tx_u+=String(moist);
tx_u+=':';
tx_u+=String(bodytemperature);
tx_u+=':';
tx_u+=Cry_1;
tx_u+=':';
tx_u+=String(weight);
tx_u+='$';
Serial.println(tx_u);
tx_u="";
}
void sendSMS() {
  // AT command to set SIM900 to SMS mode
  //Serial.print("tahir");
  Serial3.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  //Serial.print("tahir1");
  Serial3.println("AT + CMGS = \"+923155018656\""); 
  delay(100);
  //Serial3.println("AT+CGSN");
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  //Serial.print("tahir2");
  Serial3.println("Alert! : Baby is crying"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  Serial3.println((char)26); 
  delay(100);
  Serial3.println();
  // Give module time to send SMS
  delay(5000); 
}

void sendSMS1() {
  // AT command to set SIM900 to SMS mode
 // Serial.print("tahir");
  Serial3.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS

  Serial3.println("AT + CMGS = \"+923155018656\""); 
  delay(100);
 //Serial3.println("AT+CGSN");
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  //Serial.print("tahir2");
  Serial3.println("Alert! : Change the Diaper"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  Serial3.println((char)26); 
  delay(100);
  Serial3.println();
  // Give module time to send SMS
  delay(5000); 
}

void sendSMS2() {
  // AT command to set SIM900 to SMS mode
 // Serial.print("tahir");
  Serial3.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS

  Serial3.println("AT + CMGS = \"+923155018656\""); 
  delay(100);
 //Serial3.println("AT+CGSN");
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  //Serial.print("tahir2");
  Serial3.println("Alert! : Baby's body temperature is high"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  Serial3.println((char)26); 
  delay(100);
  Serial3.println();
  // Give module time to send SMS
  delay(5000); 
}
