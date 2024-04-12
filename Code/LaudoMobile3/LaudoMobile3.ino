//Step 3: making it wireless
/*Read and took information from:
https://electrosome.com/interfacing-l298n-motor-driver-arduino-uno/
*/

// arduino uno wifi board
#include <WiFi.h> // Include the WiFiNINA library

char ssid[] = "ROGspot";    //  your network SSID (name)
char pass[] = "Kltown5.";   // your network password
int status = WL_IDLE_STATUS;    // the WiFi status

WiFiServer server(80);  // Create a WiFi server on port 80

/* Motor A connections: 
in1 and in2 pins are used to control the direction of Motor A
connected to pin 13, pin 12*/
int enA = 9;
int in1 = 13;
int in2 = 12;
/* Motor B connections: 
in3 and in4 pins are used to control the direction of Motor B
connected to pin 11, pin 10*/
int enB = 3;
int in3 = 11;
int in4 = 10;

//add joysick macros
// #define JoyX A0
// #define JoyY A1
// const int JoyX = A0;
// const int JoyY = A3;
/*if values get interfered when joysrtick readings get to 1023*/

int joyposV, joyposH;

//only runs once
void setup() {
    Serial.begin(250000);
    // Connect to WiFi network
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        delay(5000);  // Wait 5 seconds for connection
    }

    Serial.println("Connected to WiFi");
    // Print Arduino Uno WiFi board's IP address
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    delay(200);

    // Start the server
    server.begin();
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
    initDrive(90);
}

void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
      return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
      delay(1);
  }

  // Read the joystick values sent over WiFi
  String data = client.readStringUntil('\n');
  int spaceIndex = data.indexOf(' ');
  if (spaceIndex != -1) {
    String vString = data.substring(0, spaceIndex);
    String hString = data.substring(spaceIndex + 1);
    joyposV = vString.toInt();
    joyposH = hString.toInt();
    delay(5);
  }
  // joyposV = analogRead(JoyX);
  // joyposH = analogRead(JoyY);
  int decLim = 1800;
  int incLim = 3000;

  int driveD = map(joyposV, decLim, 0, 90, 255);
  int driveB = map(joyposV, incLim, 4095, 90, 255);

  int driveR = map(joyposH, incLim, 0, 90, 100);
  int driveL = map(joyposH, incLim, 4095, 90, 100);

  delay(5);


  // Serial.print(joyposV);
  // Serial.print("  |  ");
  // Serial.print(driveD);
  // Serial.print("  |  ");
  // Serial.print(driveB);
  // Serial.print("  |||  ");
  // Serial.print(joyposH);
  // Serial.print("  |  ");
  // Serial.print(driveL);
  // Serial.print("  |  ");
  // Serial.println(driveR);
  
  //Forward and Back
  if(joyposV<decLim){
    //map then drive forwards
    analogWrite(enA, driveD);
    analogWrite(enB, driveD);
    // motor A CW ^ (forward)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor B CW ^ (forward)
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  delay(50);
    } else if(joyposV>incLim){
      //moves back
    analogWrite(enA, driveB);
    analogWrite(enB, driveB);
   // motor A CCW (backwards)
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  // motor B CCW (backwards)
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  delay(50);
  } else{
    // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  delay(50);
  }

//Rotation
  if(joyposH<decLim){
    //rot R
    // analogWrite(enA, driveR);
    analogWrite(enB, driveR);
  
    // motor A CCW
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    // motor B CW ^
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(50);
    } else if(joyposH>incLim){
      //rot L
    analogWrite(enA, driveL);
    analogWrite(enB, driveL);
  
   // motor A CW ^ 
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

  // motor B CCW 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(50);
  } 

  delay(50);
}