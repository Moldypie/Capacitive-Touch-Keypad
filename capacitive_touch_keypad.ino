/*
 *works with adafruit MPR121 capacitive touch sensor
 *https://www.adafruit.com/product/1982

 *the keypad was set up with an edited library for the MPR121
 *https://github.com/adafruit/Adafruit_MPR121_Library
 *make sure to change the sensitivity within the library file Adafruit_MPR121.cpp
 *setThreshholds(2, 0);
 
 *Arduino HID Keyboard Library
 *https://github.com/arduino-libraries/Keyboard
 */

#include <Wire.h>
#include <Keyboard.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found");
    while (1);
  }
  
  Serial.println("MPR121 found!");
  pinMode(currtouched, INPUT);
  digitalWrite(currtouched, HIGH);
}

void loop() {
  Keyboard.begin();
  currtouched = cap.touched();
  
  for (int i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if(i == 0){
        Keyboard.press(234);
        delay(50);
        Keyboard.release(234);
      }else{
        Keyboard.press(224 + i);
        delay(50);
        Keyboard.release(224 + i);
      }
    }
    digitalWrite(currtouched, HIGH);
  }
  lasttouched = currtouched;
  return;
}
