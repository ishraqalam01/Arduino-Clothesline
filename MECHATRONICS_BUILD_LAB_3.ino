#include "arduino_secrets.h"

/***********************************************
 * PEO Scarborough Chapter
 * Mechatronics 2023
 * Ontario, Canada
 * Lab 3 - Rain Detector Sensor
 * November 18, 2023
 * Mechatronic Mavs
 * Maroof Sulaiman and Ishraq Alam

************************************************/

#define rainPin 5

//When the module detects rain, the digital output goes LOW
bool rainState = HIGH;

void setup() {
    pinMode(rainPin, INPUT);
    
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
    rainState = digitalRead(rainPin);
    
    if (!rainState) {
      
      Serial.println("Rain Detected");
      
      delay(5000);
    }
}
