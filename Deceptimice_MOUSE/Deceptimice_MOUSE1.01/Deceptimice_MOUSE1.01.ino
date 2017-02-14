#include "Arduino.h"
#include "Dispatch.h"
#include "Motors.h"
#include "GyroAccel.h"
#include "EnableInterrupt.h"
//#include "EnableInterrupt.h"
int rotDeg = 187;
byte start = 0;
byte MOTOR1P1 = 11;
byte MOTOR1P2 = 6;
byte MOTOR2P1 = 10;
byte MOTOR2P2 = 8;
byte enablePin1 = 12;
byte enablePin2 = 7;

byte left = A6;
byte right = A0;
byte front = A2;
byte diagonalR = A1;
byte diagonalL = A3;

void encoder_ReadRight(int encoder0PA, int encoder0PB);
void encoder_ReadLeft(int encoder1PA, int encoder1PB);

volatile long encoder0PosRight = 0;
volatile long encoder0PosLeft = 0;
int encoder0PinA;
int encoder0PinB;
int encoder1PinA;
int encoder1PinB;

Dispatch IR(front, left, right, diagonalL, diagonalR);
Motors wheels(MOTOR1P1, MOTOR1P2, MOTOR2P1, MOTOR2P2, enablePin1, enablePin2);
GyroAccel gyro;

void setup() {

  Serial.begin(9600);

  encoder_ReadRight(2, 3);
  encoder_ReadLeft(4, 5);
  gyro.setup();
  while (millis() != 1000)
    //used to give time to the IR sensors to adjust
    ;
}

void loop() {/*
wheels.backward(255, 255);delay(5000);
wheels.forward(255, 255);delay(5000);
*/  
  if (analogRead(IR.irArray[0]) < 1000 ){
      if(analogRead(IR.irArray[1]) <= 240){
        byte randNum = random(0,2);
          if(randNum >= 0.5){
            delay(75);
            encoder0PosRight = 0;
            encoder0PosLeft = 0; 
            while (abs(encoder0PosRight) <= (rotDeg) and abs(encoder0PosLeft) <= (rotDeg)) {
              wheels.left_turn(235, 255);
            }
            wheels.stop_it();
            wheels.forward(235, 255);
             
         }
         else {
          wheels.forward(235, 255);
          delay(400);         
         }
     }
     wheels.forward(235, 255);
     
 }
   else {
    wheels.stop_it();
    IR.CheckFront();
    IR.CheckSides();
    checkingStates();
  }
  while (analogRead(IR.irArray[1]) > 1000) {
    wheels.right_turn(200, 0);
  }
  while (analogRead(IR.irArray[2]) > 1000) {
    wheels.left_turn(0, 200);
  }
//Serial.println(random(0,2)); 
 
//IR.RawValues();
}

void checkingStates() {
  encoder0PosRight = 0;
  encoder0PosLeft = 0;
  if (IR.state_left and IR.state_mid) {
    while (abs(encoder0PosRight) <= rotDeg and abs(encoder0PosLeft) <= rotDeg) {
      wheels.right_turn(235, 255);
    }
    wheels.stop_it();
    encoder0PosRight = 0;
    encoder0PosLeft = 0;
    //Serial.println("  Turning Right   ");
  } else if (IR.state_mid and IR.state_right) {
    while (abs(encoder0PosRight) <= rotDeg and abs(encoder0PosLeft) <= rotDeg) {
      wheels.left_turn(235, 255);
    }
    wheels.stop_it();
    encoder0PosRight = 0;
    encoder0PosLeft = 0;
    //Serial.println("         Turning left    ");
  } else if (IR.state_mid and IR.state_left and IR.state_right) {
    wheels.stop_it();
    //Serial.println("           Stopping   ");
  } else if (IR.state_mid) {
    while (abs(encoder0PosRight) <= rotDeg and abs(encoder0PosLeft) <= rotDeg) {
      wheels.right_turn(235, 255);
    }
    wheels.stop_it();
    encoder0PosRight = 0;
    encoder0PosLeft = 0;
  } else if (IR.state_mid and IR.state_left and IR.state_right) {
    while (abs(encoder0PosRight) <= (2*rotDeg) and abs(encoder0PosLeft) <= (2*rotDeg)) {
      wheels.left_turn(235, 255);
    }
    wheels.stop_it();
    encoder0PosRight = 0;
    encoder0PosLeft = 0;

  }

  IR.state_left = 0;
  IR.state_mid = 0;
  IR.state_right = 0;

}

//Code for Encoders

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

