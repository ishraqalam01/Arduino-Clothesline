#include "arduino_secrets.h"

/***********************************************
 * PEO Scarborough Chapter
 * Mechatronics 2023
 * Ontario, Canada
 * Lab 5 - Motor Controller
 * November 18, 2023
 * Mechatronic Mavs
 * Maroof Sulaiman and Ishraq Alam

************************************************/
#define motorPin 18     //Pin to enable/disable motor
#define motorFwd 32     //Pin to move motor forward
#define motorRev 33     //Pin to move motor in reverse

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(motorFwd, OUTPUT);
  pinMode(motorRev, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  Serial.println("Motor On, Forward");
  digitalWrite(motorPin, HIGH);
  digitalWrite(motorFwd, HIGH);
  digitalWrite(motorRev, LOW);
  
  delay(5000);
  
  Serial.println("Motor Off");
  digitalWrite(motorPin, LOW);
  
  delay(5000);
  
  Serial.println("Motor On, Reverse");
  digitalWrite(motorPin, HIGH);
  digitalWrite(motorFwd, LOW);
  digitalWrite(motorRev, HIGH);
  
  delay(5000);
  
  Serial.println("Motor Off");
  digitalWrite(motorPin, LOW);
  
  delay(5000);
  
  
}
