//Step 3: making it wireless
/*Read and took information from:
https://electrosome.com/interfacing-l298n-motor-driver-arduino-uno/
*/

#include <WiFi.h>


// Set your access point network credentials
const char* ssid = "ROGspot";
const char* password = "Kltown5.";
const char* host = "192.168.137.156"; // IP address of the Arduino Uno WiFi board
// joysick1
const int JoyX = A0;
const int JoyY = A3;
//camerajoy
const int camX = A10;
const int camY = A11;
// #define JoyX 25// GPIO35 
// #define JoyY 25// GPIO35 
/*JUST FIGURED IT NOW. the 2 input pins in the esp32 are right 
next to each other and it looks like when one of them was 4095, 
the other one was electromagnetically interferred. 
so I used pin 13 for JoyX and now all works!!*/

int joyposV;
int joyposH;

// only runs once
void setup() {
  Serial.begin(115200);  
  pinMode(JoyY, INPUT);
  pinMode(JoyX, INPUT);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    delay(1000);
}


void loop() {
  joyposV = analogRead(JoyX);
  joyposH = analogRead(JoyY);
  // Send joystick values over WiFi to Arduino Uno WiFi board
    WiFiClient client;
    if (client.connect(host, 80)) {
        client.print(joyposV);
        client.print(" ");
        client.println(joyposH);      
    }
  
    Serial.print(joyposV);
    Serial.print("  |||  ");
    Serial.println(joyposH);
    delay(50);
}


