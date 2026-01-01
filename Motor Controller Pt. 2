#include "arduino_secrets.h"

/***********************************************
 * PEO Scarborough Chapter
 * Mechatronics 2023
 * Ontario, Canada
 * Lab 6 - Motor Controller
 * November 18, 2023
 * Mechatronic Mavs
 * Maroof Sulaiman and Ishraq Alam

************************************************/

#define rainPin 5
#define ledPin 13
#define buzzerPin 14
#define motorPin 18
#define motorFwd 32
#define motorRev 33
#define lightPin 34

bool rainState = HIGH;
bool rainState_previous = HIGH;
int lightValue = 0;
int lightValue_previous = 0;
int lightThreshold = 500;
int cycleCount = 0;

void setup() {
    
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(motorFwd, OUTPUT);
    pinMode(motorRev, OUTPUT);
    pinMode(rainPin, INPUT);
    
    Serial.begin(9600);
    while(!Serial);
    
}

void loop() {
    
    lightValue_previous = lightValue;
    lightValue = analogRead(lightPin);
    
    rainState_previous = rainState;
    rainState = digitalRead(rainPin);
    
    if ((rainState_previous !=rainState)
      || (lightValue_previous >= lightThreshold && lightValue < lightThreshold)
      || (lightValue_previous < lightThreshold && lightValue >= lightThreshold)) {
      
      Serial.println();
      Serial.println("Printing Sensor Values...");
      
      Serial.print("Light Sensor Value: ");
      Serial.println(lightValue);
      
      if (lightValue < lightThreshold){
        Serial.println("Night time detected");
        cycleCount++;
      } else {
       Serial.println("Day time detected");
      }
      
      
      if (!rainState){
       Serial.println("Rain detected");
       cycleCount++;
      } else {
        Serial.println("No rain detected");
      }
      
      if ((!rainState || lightValue < lightThreshold) && cycleCount == 1) {
        
        
        Serial.println("Bring in the line!");
        
        
        digitalWrite(ledPin, LOW);
        
        
        digitalWrite(buzzerPin, HIGH);
        
        
        Serial.println("Motor On, Reverse");
        digitalWrite(motorPin, HIGH);
        digitalWrite(motorFwd, LOW);
        digitalWrite(motorRev, HIGH);
        
        delay(5000);
        
        
        digitalWrite(buzzerPin, LOW);
        
        Serial.println("Motor off");
        digitalWrite(motorPin, LOW);
        
      }
    
    
    
    else if (rainState && lightValue >= lightThreshold) {
      
      cycleCount = 0;
      
      
      Serial.println("Taking out the line!");
      
      digitalWrite(ledPin, HIGH);
      
      Serial.println("Motor On, Forward");
      digitalWrite(motorPin, HIGH);
      digitalWrite(motorFwd, HIGH);
      digitalWrite(motorRev, LOW);
      
      delay(5000);
      
      
      Serial.println("Motor off");
      digitalWrite(motorPin, LOW);
      
    }
    
  }
    
}  
    
    
    
    
    
    
    
    
    

