int soundSensor=2;
int LED=4;
boolean LEDStatus=false;

void setup() {
  Serial.begin(115200);
 pinMode(soundSensor,INPUT);
 pinMode(LED,OUTPUT);

}

void loop() {

  int SensorData=digitalRead(soundSensor); 
  if(SensorData==1){
        Serial.println("Crying");
    }
   else{
        Serial.println("Not Crying");
        
    }
  
  delay(200);
 } 
