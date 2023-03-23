#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>


#define FIREBASE_HOST "arduino-test-825d0.firebaseio.com" //Without http:// or https:// schemes

#define FIREBASE_AUTH "5Pw7cfImmluIaGIKV6aK9fTaewEzqN0QNYMpTPo4"
#define WIFI_SSID "Abc"
#define WIFI_PASSWORD "qwertyuiop"

String body_temp="";
String env_temp="";
String humidity="";
String moisture="";
String weight="";
String baby_cried=""; 
String saj="";
String d1="";
String d2="";
int chk_1=0;
int chk=0;
int d=0;
FirebaseData firebaseData;
FirebaseData getdata1;

FirebaseJson json;

void setup() {
Serial.begin(115200);
 //Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
delay(1000);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Firebase.reconnectWiFi(true);

Firebase.setString(firebaseData,"/temp_body","0");
Firebase.setString(firebaseData,"/humidity","0");
Firebase.setString(firebaseData,"/baby_cried","0");
Firebase.setString(firebaseData,"/weight","0");
Firebase.setString(firebaseData,"/moist","0");
Firebase.setString(firebaseData,"/temp_e","0");
Firebase.setString(firebaseData,"/fan","0");
Firebase.setString(firebaseData,"/music_set","0");

pinMode(D0,OUTPUT);
pinMode(D1,OUTPUT);
pinMode(D4,OUTPUT);

digitalWrite(D0,HIGH);
digitalWrite(D1,HIGH);

}

void loop() {
  Firebase.getString(getdata1,"fan");
   d1=getdata1.stringData();
   Serial.println(d1);
   if(d1==String(1)||(chk_1==1)){


    digitalWrite(D0,LOW);
   }
   else{
   digitalWrite(D0,HIGH);}
   
   Firebase.getString(getdata1,"cradle");
   d2=getdata1.stringData();
   Serial.println(d2);
   if((d2=="1") || (chk==1)){
    digitalWrite(D1,LOW);
   }
   else{
   digitalWrite(D1,HIGH);
   } 
  if(Serial.available()>0)
  {
      
        saj=Serial.readStringUntil('$');
       Serial.println(saj);
        
       for(int i=0;i<saj.length();i++)
       {
        char f1=saj[i];
        
        if(f1==':')
        {
          d=d+1;
          }
         if(d==0)
         {
          humidity+=saj[i];
          }
         else if(d==1)
         {
          env_temp+=saj[i];
          
          }
         else if(d==2)
         {
          moisture+=saj[i];
          }
         else if(d==3)
         {
          body_temp+=saj[i];
          }
         else if(d==4)
         {
          baby_cried+=saj[i];
          }

         else if(d==5)
         {
          weight+=saj[i];
          }
        } 
    
    env_temp=env_temp.substring(1,env_temp.length());
    body_temp=body_temp.substring(1,body_temp.length());
   // humidity=humidity.substring(1,humidity.length());
    moisture=moisture.substring(1,moisture.length());
    baby_cried=baby_cried.substring(1,baby_cried.length());
    weight=weight.substring(1,weight.length());

    if(body_temp.length()>=1 && humidity.length()>=1 && moisture.length()>=1 && env_temp.length()>=1 && baby_cried.length()>=1&& weight.length()>=1)
    {
   
    Serial.println(body_temp);
    Serial.println(humidity); 
    Serial.println(moisture);
    Serial.println(baby_cried);
    Serial.println(weight);
    Serial.println(env_temp);

    Firebase.setInt(firebaseData, "temp_body", body_temp.toInt());
    Firebase.setInt(firebaseData, "humidity", humidity.toInt());
    Firebase.setInt(firebaseData, "baby_cried", baby_cried.toInt());
    Firebase.setInt(firebaseData, "weight", weight.toInt());
    Firebase.setInt(firebaseData, "moist", moisture.toInt());
    Firebase.setInt(firebaseData, "temp_e", env_temp.toInt());
    if (env_temp.toInt()>=38){
      chk_1=1;
   }
   else if(env_temp.toInt()<=33){
   chk_1=0;
   }
   if (baby_cried.toInt()==1){
      chk=1;
   }
   else if (baby_cried.toInt()==0){
   chk=0;
   }
      }
   
        
    }
body_temp="";
env_temp="";
humidity="";
moisture="";
weight="";
baby_cried="";
saj="";
d=0;

Serial.println(".............");
}
