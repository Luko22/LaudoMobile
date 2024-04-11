//Step 3: making it wireless
/*Read and took information from:
https://electrosome.com/interfacing-l298n-motor-driver-arduino-uno/
*/
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

// add joystick macros
#define JoyX 34 // GPIO34 (Analog A2)
#define JoyY 35 // GPIO35 (Analog A3)

int joyposV, joyposH;

// only runs once
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
    joyposV = analogRead(JoyX);
    joyposH = analogRead(JoyY);

    int driveD = map(joyposV, 2000, 0, 0, 255);
    int driveB = map(joyposV, 3000, 4096, 0, 255);

    int driveR = map(joyposH, 2000, 0, 0, 250);
    int driveL = map(joyposH, 3000, 4096, 0, 250);

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

    // Forward and Back
    if (joyposV < 2000) {
        // map then drive forwards
        analogWrite(enA, driveD);
        analogWrite(enB, driveD);
        delay(5);
        // motor A CW ^ (forward)
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        // motor B CW ^ (forward)
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        delay(50);
    } else if (joyposV > 3000) {
        // moves back
        analogWrite(enA, driveB);
        analogWrite(enB, driveB);
        delay(5);
        // motor A CCW (backwards)
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
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
    if (joyposH < 2000) {
        // rot R
        analogWrite(enB, driveR);
        // motor A CCW
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        // motor B CW ^
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        delay(50);
    } else if (joyposH > 3000) {
        // rot L
        analogWrite(enA, driveL);
        analogWrite(enB, driveL);
        // motor A CW ^ 
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        // motor B CCW 
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        delay(50);
    }
}


