#include "arduino_secrets.h"

/***********************************************
 * PEO Scarborough Chapter
 * Mechatronics 2023
 * Ontario, Canada
 * Lab 2 - Active Buzzer
 * November 18, 2023
 * Mechatronic Mavs
 * Maroof Sulaiman and Ishraq Alam

************************************************/

#define buzzerPin 14

void setup() {
    
    pinMode(buzzerPin, OUTPUT);
    
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Buzzer ON");
    
    delay(1000);
    
    digitalWrite(buzzerPin, LOW);
    Serial.println("Buzzer OFF");
    
    delay(1000);
}
