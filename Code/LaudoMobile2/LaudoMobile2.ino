//Step 2: making it controllable
/*Read and took information from:
https://electrosome.com/interfacing-l298n-motor-driver-arduino-uno/
*/

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
#define JoyX A0
#define JoyY A1
/*if values get interfered when joysrtick readings get to 1023*/

int joyposV, joyposH;

//only runs once
void setup() {
    Serial.begin(9600);

    pinMode(JoyX, INPUT);
    pinMode(JoyY, INPUT);

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
  joyposV = analogRead(JoyX);
  joyposH = analogRead(JoyY);
  
  int driveD = map(joyposV, 400, 0, 90, 255);
  int driveB = map(joyposV, 700, 1024, 90, 255);

  int driveR = map(joyposH, 400, 0, 90, 255);
  int driveL = map(joyposH, 700, 1024, 90, 255);
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
  if(joyposV<400){
    //map then drive forwards
    analogWrite(enA, driveD);
    analogWrite(enB, driveD);
  delay(5);
    // motor A CW ^ (forward)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor B CW ^ (forward)
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  delay(50);
    } else if(joyposV>700){
      //moves back
    analogWrite(enA, driveB);
    analogWrite(enB, driveB);
  delay(5);
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
  if(joyposH<400){
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
    } else if(joyposH>700){
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
  // else{
  //   // Turn off motors
  //   digitalWrite(in1, LOW);
  //   digitalWrite(in2, LOW);
  //   digitalWrite(in3, LOW);
  //   digitalWrite(in4, LOW);
  //   delay(50);
  // } //this is superfluous

}


