#include "arduino_secrets.h"

/********************************
  PEO Scarborough Chapter
  Mechatronics 2023
  Ontario, Canada
  Lab 8 - Line Controller with Wi-Fi
  Ishraq Alam Maroof Sulaiman
********************************/

#include "WiFi.h"

#define rainPin 5                   // DIGITAL INPUT Pin to read rain sensor
#define ledPin 13                   // DIGITAL OUTPUT Pin to enable LED
#define buzzerPin 14                // DIGITAL OUTPUT Pin to enable buzzer
#define motorPin 18                 // DIGITAL OUTPUT Pin to enable/disable Motor
#define motorFwd 32                 // DIGITAL OUTPUT Pin to move motor forward
#define motorRev 33                 // DIGITAL OUTPUT Pin to move motor in reverse
#define lightPin 34                  // ANALOG INPUT Pin to read light sensor

bool rainState = HIGH;              // When the module detects rain, the digital output goes LOW
bool rainState_previous = HIGH;     // Previous state of rain sensor, used to detect change of state
int lightValue = 0;                 // Value from Analog to Digital Converter (ADC) connected to the Photoresistor
int lightValue_previous = 0;        // Previous value of light sensor, used to detect change of state
int lightThreshold = 500;           // Threshold ADC value to detect night time 
bool motorOverride = false;         // Flag with user override for automatic motor control
String motorState = "Disabled";     // Variable to store the current motor state
String motorDirect = "Forward";     // Variable to store the current motor direction
int cycleCount = 0;                 // Counter to go through motor control once with either rain or light state change

const char* ssid = "PEOSC_ESP32";   // <<< Change the SSID
const char* password = "123456789"; // <<< Password needs to be greater than 8 characters
String header;                      // Variable to store the HTTP request
WiFiServer server(80);              // Set web server port number to 80
IPAddress IP = {0,0,0,0};           // Clear Access Point IP Address
String IPString = "";               // String to store Access Point IP Address

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  
  pinMode(motorPin, OUTPUT);
  pinMode(motorFwd, OUTPUT);
  pinMode(motorRev, OUTPUT);
  pinMode(rainPin, INPUT);

  Serial.begin(9600);
  while(!Serial);
  
  Serial.println("Setting APâ¦");
  
  // Initialize the Access Point SSID and password
  WiFi.softAP(ssid, password);

  // Get the assigned IP address to the Access Point (ESP32)
  IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  IPString = IP.toString().c_str();
  
  server.begin();

}

void loop(){

  motor_controller();
  
  // Listen for incoming clients
  WiFiClient client_request = server.available();   
  
  // If a new client connects,
  if (client_request) {                             
    
    // Call to web server function
    web_server(client_request);
    
  }
      
}

void web_server(WiFiClient client) {
  
  Serial.println("New Client.");  
  
  // Store incoming data from the client into a variable
  String currentLine = "";    
  
  while (client.connected()) {            // Loop while the client is connected
    
    motor_controller();
      
    if (client.available()) {             // If there is incoming characters from the client
      
      char incoming_char = client.read(); // Read a byte
      Serial.write(incoming_char);        // Print it to the serial monitor
      header += incoming_char;            // Append bytes to string called header
      
      if (incoming_char == '\n') {        // If the incoming character is a newline
        
        // If the current line is blank, you got two newline characters in a row.
        // That's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
        
          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          
          // CSS to style the buttons 
          client.println("<style>html { background-color: #072339; ; font-family: Calibri; color: white; display: inline-block; margin: 0px auto; text-align: center;}");
          client.println(".button { background-color: #477D94; border: none; color: white; padding: 16px 40px;");
          client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
          client.println(".button2 {background-color: #093255; border: none; color: white;}</style></head>");
          
          //Call Motor Control
          motor_override();
          
          // Web Page Heading
          client.println("<body>");
          client.println("<h1>PEO Scarborough</h1>");
          client.println("<h1>Mechatronics 2023</h1>");
          client.println("<br>");
          client.println("<h2>ESP32 Web Server</h2>");
          client.println("<h3>IP Address: " + IPString + "</h3>");
          client.println("<br>");
        
          // Display current state 
          client.println("<p>Motor State: " + motorState + "</p>");
          
          // If motorState is OFF, display the ON button instead       
          if (motorState=="Disabled") {
            client.println("<p><a href=\"/motorPin/on\"><button class=\"button\">ON</button></a></p>");
          } 
          else {
            client.println("<p><a href=\"/motorPin/off\"><button class=\"button button2\">OFF</button></a></p>");
          }
          
          client.println("<br>");
          
          // Display direction
          client.println("<p>Motor Direction: " + motorDirect + "</p>");
          
          // If motorDirect is forward, displays the Reverse button instead       
          if (motorDirect=="Reverse") {
            client.println("<p><a href=\"/motorPin/fwd\"><button class=\"button\">Forward</button></a></p>");
          } 
          else {
            client.println("<p><a href=\"/motorPin/rev\"><button class=\"button button2\">Reverse</button></a></p>");
          } 
             
          client.println("</body></html>");
          
          // The HTTP response ends with another blank line
          client.println();
          
          // Break out of the while loop
          break;
        
        } 
        else {                            // If you got a newline, then clear currentLine
          
          currentLine = "";
          
        }
      
      } 
      else if (incoming_char != '\r') {   // if you got anything else but a carriage return character,
        
        currentLine += incoming_char;     // add it to the end of the currentLine
        
      }
    }
  }
  
  // Clear the header variable
  header = "";
  
  // Close the connection
  client.stop();
  
  Serial.println("Client disconnected.");
  Serial.println("");

}

void motor_override() {
  
  // Turn the Motor on, restoring to previous direction
  if (header.indexOf("GET /motorPin/on") >= 0) {
    
    Serial.println("Motor Pin On");
    motorState = "Enabled";
    
    //Revert back to previous state
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
  
  // Turn the Motor off
  if (header.indexOf("GET /motorPin/off") >= 0) {
    
    Serial.println("Motor Pin Off");
    motorState = "Disabled";

    digitalWrite(motorPin, LOW); 
    
  } 
  
  // Change motor direction, only if motor is enabled
  if ((header.indexOf("GET /motorPin/fwd") >= 0) && motorState == "Enabled") {
  
    Serial.println("Motor in Forward");
    motorDirect = "Forward";
    digitalWrite(motorPin, HIGH); 
    digitalWrite(motorFwd, HIGH);
    digitalWrite(motorRev, LOW);
  
  } else if ((header.indexOf("GET /motorPin/rev") >= 0) && motorState == "Enabled") {
    
    Serial.println("Motor in Reverse");
    motorDirect = "Reverse";
    digitalWrite(motorPin, HIGH); 
    digitalWrite(motorFwd, LOW);
    digitalWrite(motorRev, HIGH);
    
  } 
  
}

void motor_controller() {
  
  // Read light value from ADC
  lightValue_previous = lightValue;
  lightValue = analogRead(lightPin);
  
  // Check for rain
  rainState_previous = rainState;
  rainState = digitalRead(rainPin);
  
  // Execute code upon state change
  if ((rainState_previous != rainState) 
    || (lightValue_previous >= lightThreshold && lightValue < lightThreshold) 
    || (lightValue_previous < lightThreshold && lightValue >= lightThreshold)) {

    // Print sensor values
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
  
    // Motor control based on rain state and light intensity
    // Run code if rain detected or light value is below day time threshold
    if ((!rainState || lightValue < lightThreshold) && cycleCount == 1) {

      // Print to serial monitor
      Serial.println("Bring in the line!");
          
      // Turn off LED
      digitalWrite(ledPin, LOW);
      
      // Turn on buzzer
      digitalWrite(buzzerPin, HIGH);
  
      // Reverse motor to pull in laundry line for 10 seconds
      Serial.println("Motor On, Reverse");
      digitalWrite(motorPin, HIGH); 
      digitalWrite(motorFwd, LOW);
      digitalWrite(motorRev, HIGH);
      
      delay(5000);
      
      // Turn off buzzer
      digitalWrite(buzzerPin, LOW);
      
      // Turn off motor
      Serial.println("Motor off");
      digitalWrite(motorPin, LOW); 
      
    } 
    // Else when rain is not detected and light value is above day time threshold
    else if (rainState && lightValue >= lightThreshold) {
          
      cycleCount = 0;
            
      // Print to serial monitor
      Serial.println("Taking out the line!");
          
      // Turn on LED
      digitalWrite(ledPin, HIGH);
      
      // Turn off buzzer
      digitalWrite(buzzerPin, LOW);
  
      // Forward motor to take out laundry line for 10 seconds
      Serial.println("Motor On, Forward");
      digitalWrite(motorPin, HIGH); 
      digitalWrite(motorFwd, HIGH);
      digitalWrite(motorRev, LOW);
      
      delay(5000);
      
      // Turn off motor
      Serial.println("Motor off");
      digitalWrite(motorPin, LOW); 
      
    }
    
  }
  
}

