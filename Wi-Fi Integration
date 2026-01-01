#include "arduino_secrets.h"

/***********************************************
 * PEO Scarborough Chapter
 * Mechatronics 2023
 * Ontario, Canada
 * Lab 8 - Line Controller with Wi-Fi
 * November 18, 2023
 * Mechatronic Mavs
 * Maroof Sulaiman and Ishraq Alam

************************************************/
#include "WiFi.h"

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
bool motorOverride = false;
String motorState = "Disabled";
String motorDirect = "Forward";
int cycleCount = 0;

const char* ssid = "MECH2023";
const char* password = "rhking123";
String header;
WiFiServer server(80);
IPAddress IP = {0,0,0,0,};
String IPString = "";

void setup() {
    
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(motorFwd, OUTPUT);
    pinMode(motorRev, OUTPUT);
    pinMode(rainPin, INPUT);
    
    Serial.begin(9600);
    while(!Serial);
    
    Serial.println("Setting AP...");
    
    WiFi.softAP(ssid, password);
    
    IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    IPString = IP.toString().c_str();
    
    server.begin();
}

void loop (){
    
  motor_controller();
  WiFiClient client_request = server.available();
    
  if (client_request) {
      
      web_server(client_request);
      
  }
      
}
  
void web_server(WiFiClient client) {
  
  Serial.println("New Client.");
  
  
  String currentLine = "";
  
  while (client.connected()) {
    motor_controller();
    
    if (client.available()) {
      
      char incoming_char = client.read();
      Serial.write(incoming_char);
      header += incoming_char;
      
      if (incoming_char == '\n') {
    
    
        if (current.length() == 0) {
          
          
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          
          client.println("!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          
          client.println("<style>html { background-color: #072339; ; font-family: Calibri; color: white; display: inline-block; margin: 0px auto; text-align: center;}");
          client.println(".button { background-color: #477D94; border: none; color: white; padding: 16px 40px;");
          client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
          client.println(".button2 {background-color: #093255; border: none; color: white;}</style></head>");
          
          
          motor_override();
          
          client.println("<body>");
          client.println("<h1>PEO Scarborough</h1>");
          client.println("<h1>Mechatronics 2023</h1>");
          client.println("<br>");
          client.println("<h2>ESP32 Web Server</h2>");
          client.println("<h3>IP Address: " + IPString + "</h3>");
          client.println("<br>");
          
          
          client.println("<p>Motor State: " + motorState + "</p>");
          
          if (motorState=="Disabled") {
            client.println("<p><a href=\"/motorPin/on\"><button class=\"button\">ON</button><a></p>");
            
          }
          else {
            client.println("<p><a href=\"/motorPin/off\"><button class=\"button button2\">OFF</button><a></p>");
          }
          
          client.println("<br>");
          
          if (motorDirect=="Reverse") {
            client.println("<p><a href=\"/motorPin/fwd\"><button class=\"button\">Forward</button></a></p>");
          }
          
          else { 
            client.println("<p><a href=\"/motorPin/rev\"><button class=\"button button2\">Reverse</button></a></p>");
            
          }
        
         client.println("</body><html>");
         
         client.println();
         
         break;
         
        }
        else {
          
          currentLine = "";
          
        }
        
      }
      else if (incoming_char != '\r') {
        
        currentLine += incoming_char;
        
      }
    }
  }
  
  header = "";
  
  client.stop();
  
  Serial.println("Client disconnected.");
  Serial.println("");
  
}

void motor_override() {
  if (header.indexOf("GET /motorPin/on") >= 0) {
    
    Serial.println("Motor Pin On");
    motorState = "Enabled";
    
    if (motorDirect == "Forward"){
      digitalWrite(motorPin, HIGH);
      digitalWrite(motorFwd, HIGH);
      digitalWrite(motorRev, LOW);
      
    } else if (motorDirect == "Reverse"){
      digitalWrite(motorPin, HIGH);
      digitalWrite(motorFwd, LOW);
      digitalWrite(motorRev, HIGH);
      
    }
  }

  if (header.indexOf("GET /motorPin/off") >= 0) {
    
    Serial.println("Motor Pin Off");
    motorState = "Disabled";
    
    digitalWrite(motorPin, LOW);
    
  }
  
  if (header.indexOf("GET /motorPin/off") >= 0) {
    
    Serial.println("Motor Pin Off");
    motorState = "Disabled";
    
    digitalWrite(motorPin, LOW);
    
  }
  
  if ((header.indexOf("GET /motorPin/fwd") >=0) && motorState == "Enabled") {
    Serial.println("Motor in Forward");
    motorDirect = "Forward";
    digitalWrite(motorPin, HIGH);
    digitalWrite(motorFwd, HIGH);
    digitalWrite(motorRev, LOW);
    
  } else if ((header.indexOf("GET /motorPin/rev") >= 0) && motorState == "Enabled") {
    
    digitalWrite(motorPin, HIGH);
    digitalWrite(motorFwd, LOW);
    digitalWrite(motorRev, HIGH);
    
  }

void motor_controller() {
    
  lightValue_previous = lightValue;
  lightValue = analogRead(lightPin);
    
  rainState_previous = rainState;
  rainState = digitalRead(rainPin);
    
  if ((rainState_previous != rainState)
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
    
    
    
    
    
    
    
    
    

