// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Servo.h>
#include <Wire.h>
int x;
Servo Servo1;
void setup() {
  Serial.begin(9600);           // start serial for output
  Serial.println("start slave");
  Wire.begin(0xAB);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Servo1.attach(9);
  
}

void loop() {
  delay(10);
  Serial.println(x);         // print the integer
  Servo1.write(x);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  x = Wire.read();    // receive byte as an integer
}
