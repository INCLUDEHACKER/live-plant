
#define BLYNK_PRINT Serial
#include <DFRobot_DHT20.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "SoftwareSerial.h"
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

// sd player
SoftwareSerial mySD(D5, D6); // tx, rx of sd module
DFRobotDFPlayerMini myDFPlayer;

char auth[] = "L0blzCG4hVCcyazVGkchrBZxXR5qJRa0";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Pixel 4";
char pass[] = "123456789";

// hygro 
const int hygrometer = A0;  //Hygrometer sensor analog pin output at pin A0 of Arduino
int value;
DFRobot_DHT20 dht20; 

void setup() {
   Blynk.begin(auth, ssid, pass); 
  while(dht20.begin()){
    Serial.println("Initialize sensor failed");
    delay(1000);
  }
  mySD.begin(9600); 
  if (!myDFPlayer.begin(mySD)) { 
    while(true);
  }
   delay(0);
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
} 
  

void loop() 
{ 
  
  // Get soil moisture 
  value = analogRead(hygrometer);   //Read analog value 
  value = constrain(value,400,1023);  //Keep the ranges!
  value = map(value,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
   if (value <=30){
    myDFPlayer.volume(30);  //Set volume value. From 0 to 30
    myDFPlayer.play(2);  //Play the first mp3
 delay(5000);
   }
    if (value >=90){
      myDFPlayer.volume(30);  //Set volume value. From 0 to 30
      myDFPlayer.play(3);  //Play the first mp3
  delay(5000);   
    }
  Blynk.virtualWrite(V2, value);
  delay(1000); //Read every 2 sec.
  
  Blynk.virtualWrite(V0, dht20.getTemperature()); 
  Blynk.virtualWrite(V1, dht20.getHumidity()*100);
 delay(1000); 
   if (dht20.getTemperature()>=27){
    myDFPlayer.volume(30);  //Set volume value. From 0 to 30
    myDFPlayer.play(5);  //Play the first mp3
   delay(5000);
   }
    if (dht20.getTemperature()<=15){
      myDFPlayer.volume(30);  //Set volume value. From 0 to 30
      myDFPlayer.play(4);  //Play the first mp3
    delay(5000);  
    }
  
    } 



  
