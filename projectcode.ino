#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))
#include <SoftwareSerial.h>
SoftwareSerial softSerial(2,3);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

const int trigPin = 9;
const int echoPin = 8;
long duration;
int distanceCm, distanceInch;
void setup()
{ 
 Serial.begin(9600); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 pinMode(5, OUTPUT); //led  
 pinMode(6, OUTPUT);//buzzer1
 pinMode(4, OUTPUT);//buzzer2

  #if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1,D3,D2);
  #else
  FPSerial.begin(9600);
  #endif
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(FPSerial,true, true)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0);
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
}
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  distanceInch = duration*0.0133/2;
  Serial.println("Distance: ");
  Serial.println(distanceCm);
  delay (1000);

if(distanceCm <= 110 && distanceCm >= 80)
{
  myDFPlayer.volume(30);
  myDFPlayer.play(1);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  delay(500);
}
else if(distanceCm < 80 && distanceCm >= 50)
{
    myDFPlayer.volume(30);
    myDFPlayer.play(3);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    delay(500);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH); 
    delay(500);
    digitalWrite(5,LOW);
}
else if(distanceCm < 50 && distanceCm >= 0)
{
    myDFPlayer.volume(30);
    myDFPlayer.play(2);
    digitalWrite(6,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    delay(500);
    digitalWrite(5,LOW);
    delay(500);
    digitalWrite(5,HIGH);
    delay(500);
    digitalWrite(5,LOW);
    delay(500);
    digitalWrite(5,HIGH);
    delay(500);
}
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(4,LOW);

}
