//Step 3: making it wireless
/*Read and took information from:
https://electrosome.com/interfacing-l298n-motor-driver-arduino-uno/
*/
#include <esp_now.h>
#include <WiFi.h>
// Must match the receiver structure
typedef struct struct_message {
  int joyposV;
  int joyposH;
  
  // float c;
  // bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.print("Bytes received: ");
  // Serial.print(myData.joyposV);
  // Serial.print("  |||  ");
  // Serial.println(myData.joyposH);
}
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


// only runs once
void setup() {
    Serial.begin(9600);
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
    }
    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);
    
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
  int joyposV = myData.joyposV;
  int joyposH = myData.joyposH;


  int decLim = 400;
  int incLim = 700;

  int driveD = map(joyposV, decLim, 0, 90, 255);
  int driveB = map(joyposV, incLim, 4095, 90, 255);

  int driveR = map(joyposH, incLim, 0, 90, 120);
  int driveL = map(joyposH, incLim, 4095, 90, 120);

delay(50);


  Serial.print(joyposV);
  Serial.print("  |  ");
  Serial.print(driveD);
  Serial.print("  |  ");
  Serial.print(driveB);
  Serial.print("  |||  ");
  Serial.print(joyposH);
  Serial.print("  |  ");
  Serial.print(driveL);
  Serial.print("  |  ");
  Serial.println(driveR);
  
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