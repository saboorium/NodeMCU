/*
Nodemcu esp8266	Seven Segment Display	220 Ohm 2 Resistor 
D2 Pin            	A   Pin	 
D3 Pin	            B   Pin	 
D6 Pin            	C   Pin	 
D5 Pin            	D   Pin	 
D4 Pin             E   Pin	 
D1 Pin            	F   Pin	 
D0 Pin	            G   Pin	 
D7 Pin            	DP Pin	 
                  	Both Common	        Terminal 1
G, GND	 	                              Terminal 2
*/

// Common Cathode Seven Segment
 // TECHATRONIC.COM   
  void setup()   
  {   
  pinMode(16, OUTPUT); // D0 PIN NODEMCU  
  pinMode(5, OUTPUT);  // D1 PIN NODEMCU  
  pinMode(4, OUTPUT);  // D2 PIN NODEMCU  
  pinMode(0, OUTPUT);  // D3 PIN NODEMCU  
  pinMode(2, OUTPUT);  // D4 PIN NODEMCU  
  pinMode(14, OUTPUT); // D5 PIN NODEMCU  
  pinMode(12, OUTPUT); // D6 PIN NODEMCU  
  pinMode(13, OUTPUT); // D7 PIN NODEMCU  
  }   
  void loop()   
  {   
  // ZERO   
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, HIGH);   
  digitalWrite(0, HIGH);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, HIGH);   
  digitalWrite(13, LOW);   
  delay(2000); // Wait for 2000 millisecond(s)   
  // ONE 1   
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, LOW);   
  digitalWrite(0, LOW);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, LOW);   
  digitalWrite(12, LOW);   
  digitalWrite(13, LOW);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 2 TWO    
  digitalWrite(16, LOW);   
  digitalWrite(5, LOW);   
  digitalWrite(4, HIGH);   
  digitalWrite(0, HIGH);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, LOW);   
  digitalWrite(13, HIGH);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 3 THREE    
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, HIGH);   
  digitalWrite(0, LOW);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, LOW);   
  digitalWrite(13, HIGH);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 4 FOUR   
  digitalWrite(15, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, LOW);   
  digitalWrite(0, LOW);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, LOW);   
  digitalWrite(12, HIGH);   
  digitalWrite(13, HIGH);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 5 FIVE   
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, HIGH);   
  digitalWrite(0, LOW);   
  digitalWrite(2, LOW);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, HIGH);   
  digitalWrite(13, HIGH);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 6 SIX   
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, HIGH);   
  digitalWrite(0, HIGH);   
  digitalWrite(2, LOW);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, HIGH);   
  digitalWrite(13, HIGH);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 7 SEVEN   
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, LOW);   
  digitalWrite(0, LOW);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, LOW);   
  digitalWrite(13, LOW);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 8 EIGHT   
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, HIGH);   
  digitalWrite(0, HIGH);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, HIGH);   
  digitalWrite(13, HIGH);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // 9 NINE   
  digitalWrite(16, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(4, HIGH);   
  digitalWrite(0, LOW);   
  digitalWrite(2, HIGH);   
  digitalWrite(14, HIGH);   
  digitalWrite(12, HIGH);   
  digitalWrite(13, HIGH);   
  delay(2000); // Wait for 2000 millisecond(s)   
   // . DOT   
  digitalWrite(16, HIGH);   
  digitalWrite(5, LOW);   
  digitalWrite(4, LOW);   
  digitalWrite(0, LOW);   
  digitalWrite(2, LOW);   
  digitalWrite(14, LOW);   
  digitalWrite(12, LOW);   
  digitalWrite(13, LOW);   
  delay(2000); // Wait for 2000 millisecond(s)   
  } 

