#include "arduino_secrets.h"

/***********************************************
 * PEO Scarborough Chapter
 * Mechatronics 2023
 * Ontario, Canada
 * Lab 1 - Blinking LED
 * November 7, 2023
 * Mechatronic Mavs
 * Maroof Sulaiman and Ishraq Alam

************************************************/
#define ledPin 13

void setup() {
  
    pinMode(ledPin, OUTPUT);
    
    Serial.begin(9600);
    while(!Serial);
    
}

void loop() {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON");
    
    delay(1000);
    
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
    
    delay(1000);
    
}
