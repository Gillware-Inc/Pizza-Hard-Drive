/*
 * Firmware for the Pizza Hard Drive
 *
 * Copyright (c) 2017 Gillware Inc.
 * Website    : www.gillware.com
 * Author     : Nick Stratton
 * Create Time: Oct 10,2017
 * Change Log :
 *
 * The MIT License (MIT)
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include <CheapStepper.h>
#include <Servo.h>

// initialize the LCD/KEYPAD & STEPPER
LCDKeypad lcd;
CheapStepper stepper (8,9,10,11);
Servo myservo;

// let's create a boolean variable to save the direction of our rotation
boolean moveClockwise = true;
unsigned long moveStartTime = 0; // this will save the time (millis()) when we started each new move
int pos = 0;    // variable to store the servo position
void setup() {
  // let's run the stepper at 12rpm (if using 5V power) - the default is ~16 rpm
  stepper.setRpm(12);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  lcd.begin(16,2);
  lcd.clear();
  
  lcd.print("Gillware Pizza Hard Drive");
  
  delay(2000);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.run();
  // case states for the button interface
  switch (lcd.button()) {
    case KEYPAD_LEFT:
      lcd.print("LEFT  ");
      break;
    case KEYPAD_RIGHT:
      lcd.print("RIGHT ");
      break;
    case KEYPAD_DOWN:
      lcd.print("DOWN  ");
      break;
    case KEYPAD_UP:
      lcd.print("UP    ");
      break;
    case KEYPAD_SELECT:
      lcd.print("SELECT");
      break;
    default:
      lcd.print("NONE  ");
      break;
  }
  
  stepper.newMoveDegrees (moveClockwise, 360); // move 180 degrees from current position
  moveStartTime = millis(); // reset move start time
}
