#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <stdlib.h>
LiquidCrystal_PCF8574 lcd(0x3F);
int LastVR_position = 0;
int ServoPosition = 0;
int Threshold = 2;
void setup() {
  Wire.begin();
  Serial.begin(19200);     // setup baud rate
  lcd.begin(16, 2);       // LCD16x2
  lcd.setBacklight(1);
  lcd.clear();
  Serial.println("I2Cmaster begins");
}

void loop() {
  int VR_position = analogRead(A0);
  if (abs(LastVR_position - VR_position) > Threshold)
  {
    LastVR_position = VR_position;
    Serial.println(VR_position);
    ServoPosition = map(VR_position, 0, 1023, 1, 180);
    display_LCD(ServoPosition);
    Wire.beginTransmission(3);
    Wire.write(ServoPosition);
    Wire.endTransmission();
  }
  delay(50);
}

void display_LCD(int ServoPosition) {
    Serial.println(ServoPosition);
    lcd.setCursor(0, 0);
    lcd.print("Position: ");
    lcd.setCursor(0, 11);
    lcd.print(ServoPosition);
    lcd.print(" ");
    Wire.beginTransmission(0xAB); // transmit to device #8
    Wire.write("ServoPosition is ");        // sends five bytes
    Wire.write(ServoPosition);              // sends one byte
    Wire.endTransmission();    // stop transmitting
}
