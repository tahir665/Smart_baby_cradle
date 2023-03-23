int sensorPin = A13; 
int sensorValue;  
int limit = 500; 

void setup() {
 Serial.begin(115200);
 
}

void loop() {

 sensorValue = analogRead(sensorPin); 
 Serial.println("Analog Value : ");
 Serial.println(sensorValue);
 
 if (sensorValue<limit) {
 Serial.println("Detected"); 
 }
 else {
 Serial.println("Not Detected"); 
 }
 
 delay(1000); 
}
