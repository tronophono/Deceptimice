/*
 * encoder.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: lasantos
 */

#include "Arduino.h"
#include "EnableInterrupt.h"

volatile long encoder0PosRight = 0;
volatile long encoder0PosLeft = 0;
int encoder0PinA;
int encoder0PinB;
int encoder1PinA;
int encoder1PinB;

void doEncoderRightA() {

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0PosRight = encoder0PosRight + 1;         // CW
    } else {
      encoder0PosRight = encoder0PosRight - 1;         // CCW
    }
  } else  // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0PosRight = encoder0PosRight + 1;          // CW
    } else {
      encoder0PosRight = encoder0PosRight - 1;          // CCW
    }
  }
  if (encoder0PosRight >= 100000) {
    //stop_it();
    encoder0PosRight = 0;
  }
  // use for debugging - remember to comment out
}

void doEncoderRightB() {

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0PosRight = encoder0PosRight + 1;         // CW
    } else {
      encoder0PosRight = encoder0PosRight - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0PosRight = encoder0PosRight + 1;          // CW
    } else {
      encoder0PosRight = encoder0PosRight - 1;          // CCW
    }
  }
  if (encoder0PosRight >= 100000) {
    //stop_it();
    encoder0PosRight = 0;
  }
}

//This is the functions that takes care of the count of the encoders left

void doEncoderLeftA() {

  // look for a low-to-high on channel A
  if (digitalRead(encoder1PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder1PinB) == LOW) {
      encoder0PosLeft = encoder0PosLeft - 1;         // CW
    } else {
      encoder0PosLeft = encoder0PosLeft + 1;         // CCW
    }
  } else  // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder1PinB) == HIGH) {
      encoder0PosLeft = encoder0PosLeft - 1;          // CW
    } else {
      encoder0PosLeft = encoder0PosLeft + 1;          // CCW
    }
  }
  if (encoder0PosLeft >= 100000) {
    //stop_it();
    encoder0PosLeft = 0;
  }
  // use for debugging - remember to comment out
}

void doEncoderLeftB() {

  // look for a low-to-high on channel B
  if (digitalRead(encoder1PinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoder1PinA) == HIGH) {
      encoder0PosLeft = encoder0PosLeft - 1;         // CW
    } else {
      encoder0PosLeft = encoder0PosLeft + 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder1PinA) == LOW) {
      encoder0PosLeft = encoder0PosLeft - 1;          // CW
    } else {
      encoder0PosLeft = encoder0PosLeft + 1;          // CCW
    }
  }
  if (encoder0PosLeft >= 100000) {
    //stop_it();
    encoder0PosLeft = 0;
  }
}

void encoder_ReadRight(int encoder0PA, int encoder0PB) {

  encoder0PinA = encoder0PA;
  encoder0PinB = encoder0PB;
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  enableInterrupt(encoder0PinA, doEncoderRightA, CHANGE);
  enableInterrupt(encoder0PinB, doEncoderRightB, CHANGE);
}

//Enter the pin that correspond to encoderLeft readings
void encoder_ReadLeft(int encoder1PA, int encoder1PB) {

  encoder1PinA = encoder1PA;
  encoder1PinB = encoder1PB;
  pinMode(encoder1PinA, INPUT);
  pinMode(encoder1PinB, INPUT);

  enableInterrupt(encoder1PinA, doEncoderLeftA, CHANGE);
  enableInterrupt(encoder1PinB, doEncoderLeftB, CHANGE);
}

void printEncoderValues() {
  Serial.print("Right Encoder: ");
  Serial.println(encoder0PosRight);
  Serial.print("Left Encoder: ");
  Serial.println(encoder0PosLeft);
}

