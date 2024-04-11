//Step 3: making it wireless
/*Read and took information from:
https://electrosome.com/interfacing-l298n-motor-driver-arduino-uno/
*/
#include <Wire.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Set your access point network credentials
const char* ssid = "LukoMobile";
const char* password = "KtownGetDown5";

//Your IP address or domain name with URL path
const char* serverVert = "http://192.168.4.1/VertJoy";
const char* serverHori = "http://192.168.4.1/HoriJoy";
  

/* Motor A connections: 
in1 and in2 pins are used to control the direction of Motor A
connected to pin 13, pin 12 */
int enA = 32; // GPIO32
int in1 = 33; // GPIO33
int in2 = 25; // GPIO25
/* Motor B connections: 
in3 and in4 pins are used to control the direction of Motor B
connected to pin 11, pin 10 */
int enB = 27; // GPIO27 
int in3 = 14; // GPIO14 
int in4 = 12 ; // GPIO12

// // add joystick macros
// #define JoyX 34 // GPIO34 
// #define JoyY 13 // GPIO35 
/*JUST FIGURED IT NOW. the 2 input pins in the esp32 are right 
next to each other and it looks like when one of them was 4095, 
the other one was electromagnetically interferred. 
so I used pin 13 for JoyX and now all works!!*/

int joyposV, joyposH;

unsigned long previousMillis = 0;
const long interval = 10; 

// only runs once
void setup() {
    Serial.begin(9600);

    // pinMode(JoyX, INPUT);
    // pinMode(JoyY, INPUT);

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    delay(1000);
    
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
  
    while(WiFi.status() != WL_CONNECTED) {
      Serial.println(".");
      delay(100);
    }

    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    delay(500);
    initDrive(90);
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
    String VJoyString = httpGETRequest(serverVert);
    String HJoyString = httpGETRequest(serverHori);
    // joyposV = analogRead(JoyX);
    // joyposH = analogRead(JoyY);
    int driveD = map(VJoyString.toInt(), 2000, 0, 90, 255);
    int driveB = map(VJoyString.toInt(), 3000, 4095, 90, 255);

    int driveR = map(HJoyString.toInt(), 2000, 0, 90, 255);
    int driveL = map(HJoyString.toInt(), 3000, 4095, 90, 255);

    delay(50);

    // Serial.print(joyposV);
    Serial.print("  |  ");
    Serial.print(driveD);
    Serial.print("  |  ");
    Serial.print(driveB);
    Serial.print("  |||  ");
    // Serial.print(joyposH);
    Serial.print("  |  ");
    Serial.print(driveL);
    Serial.print("  |  ");
    Serial.println(driveR);

    // Forward and Back
    if (VJoyString.toInt() < 2000) {
        // map then drive forwards
        analogWrite(enA, driveD);
        analogWrite(enB, driveD);
        delay(10);
        // motor A CW ^ (forward)
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        // motor B CW ^ (forward)
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        delay(50);
    } else if (VJoyString.toInt() > 3000) {
        // moves back
        analogWrite(enA, driveB);
        analogWrite(enB, driveB);
        delay(10);
        // motor A CCW (backwards)
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        // motor B CCW (backwards)
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        delay(50);
    } else {
        // Turn off motors
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        delay(50);
    }

    // Rotation
    if (HJoyString.toInt() < 2000) {
        // rot R
        analogWrite(enA, driveR);
        analogWrite(enB, driveR);
        delay(10);
        // motor A CCW
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        // motor B CW ^
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        delay(50);
    } else if (HJoyString.toInt() > 3000) {
        // rot L
        analogWrite(enA, driveL);
        analogWrite(enB, driveL);
        delay(10);
        // motor A CW ^ 
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        // motor B CCW 
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        delay(50);
    }

    // save the last HTTP GET Request
      previousMillis = currentMillis;
    }else{
      Serial.println("Wifi disconnected");
    }
  }
}


