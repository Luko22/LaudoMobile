//Laudo Lukoki
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

//only runs once
void setup() {

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
}

void loop() {

    analogWrite(enA, 100);
    analogWrite(enB, 100);
 
  // motor A CW ^ (forward)
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

  // motor B CW ^ (forward)
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    delay(2000);

//  // Turn off motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
//     digitalWrite(in3, LOW);
//     digitalWrite(in4, LOW);
//     delay(2000);

//   // motor A CCW  (backwards)
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);

//   // motor B CCW (backwards)
//     digitalWrite(in3, LOW);
//     digitalWrite(in4, HIGH);

//     delay(1000);



 // // motor A CW ^
  //   digitalWrite(in1, LOW);
  //   digitalWrite(in2, HIGH);

  // // motor B CCW
  //   digitalWrite(in3, HIGH);
  //   digitalWrite(in4, LOW);
    

    // Turn off motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(2000);


    // directionControl();
    // delay(1000);
    // speedControl();
    // delay(1000);
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

/*Set up function to enable wirless connection*/


/*
Concerns:
- very little pmw pins left on arduino
- 
*/