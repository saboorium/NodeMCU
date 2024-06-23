bool d1 = HIGH;
bool d2 = LOW;

void motor_direction(){
 d1 = !d1;
 d2 = !d2;
  
}

void setup() {
 Serial.begin(9600);
 pinMode(D5, OUTPUT);  			/* PWM pin for Speed Control */
 pinMode(D6, OUTPUT);  			/* Motor control pin 1 */
 pinMode(D7, OUTPUT);  			/* Motor control pin 2 */
 pinMode(D8, INPUT_PULLUP);  	/* Interrupt pin for direction control */
 attachInterrupt(D8, motor_direction, HIGH);	
 /* call motor direction function on HIGH level at pin 8 */
}

void loop() {
 int pwm_adc;
 pwm_adc = analogRead(A0); 		/* Input from Potentiometer for speed control */
 digitalWrite(D6,d1);
 digitalWrite(D7,d2);
 analogWrite(D5,pwm_adc);
 delay(100);
}
