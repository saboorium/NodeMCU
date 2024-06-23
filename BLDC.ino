#include <Servo.h>
/*
   Define Constants
*/
#define VARIABLE  speed // variable
#define MotorPin D5 //NodeMCU pin where the signal for the ESC comes out
Servo ESC;
float value=0; // To store incoming value.

void lesgo() {
  value = map(analogRead(A0)/2, 0, 1023, 0, 180); //Map the 0-100 values from the slider to the 0-180 to use the servo lib.
  ESC.write(value); //Send the value (PWM) to the ESC
  Serial.println(value);
   delay(100);
   
}

/****************************************
   Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ESC.attach(MotorPin,1000,2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  lesgo();
}
