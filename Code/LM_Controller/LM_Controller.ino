//Step 3: making it wireless
/*Read and took information from:
https://electrosome.com/interfacing-l298n-motor-driver-arduino-uno/
*/

#include <WiFi.h>
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "LukoMobile";
const char* password = "KtownGetDown5";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// add joystick macros
#define JoyX A0 // GPIO34 
#define JoyY A1// GPIO35 
/*JUST FIGURED IT NOW. the 2 input pins in the esp32 are right 
next to each other and it looks like when one of them was 4095, 
the other one was electromagnetically interferred. 
so I used pin 13 for JoyX and now all works!!*/

int joyposV;
int joyposH;

// only runs once
void setup() {
    
  pinMode(JoyY, INPUT);
  pinMode(JoyX, INPUT);
  

  Serial.begin(9600);
  Serial.println();
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);

    delay(50);
}

void loop() {
  joyposV = analogRead(JoyX);
  joyposH = analogRead(JoyY);

  server.on("/joyposV", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAnPinVert().c_str());
  });
  server.on("/joyposH", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readAnPinHori().c_str());
  });

  // Start server
  server.begin();

   Serial.print(joyposV);
    Serial.print("  |||  ");
    Serial.println(joyposH);

  delay(50);
}


