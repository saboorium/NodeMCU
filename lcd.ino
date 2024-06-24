#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  lcd.backlight();
  // Additional setup code
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print("THANKS");
  delay(800);

  lcd.clear();

  // Additional LCD control code
}
