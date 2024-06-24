#include <Wire.h>

#include <LiquidCrystal_I2C.h>
/*GND pin of I2C is connected Ground pin (GND) of the NodeMCU.

VCC pin of I2C is connected Vin pin of the NodeMCU. (Because we need to supply 5v to LCD)

SDA pin of I2C is connected D4 of the NodeMCU.

SCL pin of I2C is connected D3 pin of the NodeM*/
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup(){
  Wire.begin(D4,D3);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.print(" Hello Makers "); // Start Printing
}
void loop(){
  // Nothing Absolutely Nothing!
}
