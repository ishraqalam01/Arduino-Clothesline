#include "arduino_secrets.h"

/***********************************************
 * PEO Scarborough Chapter
 * Mechatronics 2023
 * Ontario, Canada
 * Lab 4 - Light Dependant Resistor
 * November 18, 2023
 * Mechatronic Mavs
 * Maroof Sulaiman and Ishraq Alam

************************************************/

#define lightPin 34

int lightValue = 0;

void setup() {
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
    lightValue = analogRead(lightPin);
    
    Serial.println("Current Reading >>");
    Serial.print("ADC Value:");
    Serial.println(lightValue);
    
    delay(5000);
}
