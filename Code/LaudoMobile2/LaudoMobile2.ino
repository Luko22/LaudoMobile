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
    initDrive(100);

}

void loop() {
  joyposH = analogRead(JoyY);
  joyposV = analogRead(JoyX);

  int driveD = map(joyposV, 400, 0, 0, 250);
  int driveB = map(joyposV, 600, 1023, 0, 250);

  Serial.print(joyposH);
  Serial.print("  |  ");
  Serial.print(joyposV);
  Serial.print("  |  ");
  Serial.println(driveD);
  Serial.print("  |  ");
  Serial.print(driveB);

  if(joyposV<400){
    //map then drive forwards

    analogWrite(enA, driveD);
    analogWrite(enB, driveD);
  
    // motor A CW ^ (forward)
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    // motor B CW ^ (forward)
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(50);
    } else if(joyposV>600){

    analogWrite(enA, driveB);
    analogWrite(enB, driveB);
  
   // motor A CCW (backwards)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

  // motor B CCW (backwards)
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else{
    // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(50);
  }
  
  //map
  
  
    // directionControl();
    // delay(1000);
    // speedControl();
    // delay(1000);
}

void initDrive(int s){
  analogWrite(enA, s);
  analogWrite(enB, s);
 
  // motor A CW ^ (forward)
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

  // motor B CW ^ (forward)
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    delay(500);

 // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);


 // motor A CCW (backwards)
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

  // motor B CCW (backwards)
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    delay(500);

 // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
}


//function
void directionControl() {
    // Set motors to maximum speed
    // PWM value ranges from 0 to 255
    analogWrite(enA, 255);
    analogWrite(enB, 255);

    // Turn on motor A & B
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(2000);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(2000);
	
    // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}


void speedControl() {
    // Turn on motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
	
    for (int i = 0; i < 256; i++) {
        analogWrite(enA, i);
        analogWrite(enB, i);
        delay(20);
    }
	
    for (int i = 255; i >= 0; --i) {
        analogWrite(enA, i);
        analogWrite(enB, i);
        delay(20);
    }
	
    // Now turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

/*
Concerns:
- very little pmw pins left on arduino
- 
*/