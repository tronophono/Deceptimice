#include "Arduino.h"
#include "Dispatch.h"
#include "Motors.h"
#include "GyroAccel.h"
#include "EnableInterrupt.h"
//#include "EnableInterrupt.h"
byte start = 0;
byte MOTOR1P1 = 11;
byte MOTOR1P2 = 6;
byte MOTOR2P1 = 10;
byte MOTOR2P2 = 8;
byte enablePin1 = 12;
byte enablePin2 = 7;

byte left = A1;
byte right = A3;
byte front = A2;

int IRleft,IRright;
volatile long encoder0PosRight = 0;
volatile long encoder0PosLeft = 0;
int encoder0PinA;
int encoder0PinB;
int encoder1PinA;
int encoder1PinB;

Dispatch IR(front, left, right);
Motors wheels(MOTOR1P1, MOTOR1P2, MOTOR2P1, MOTOR2P2, enablePin1, enablePin2);
GyroAccel gyro;
int mouse_angle = 0;


void setup() {

  Serial.begin(9600);

  encoder_ReadRight(2, 3);
  encoder_ReadLeft(4, 5);
  gyro.setup();
  while (millis() != 1000)
    //used to give time to the IR sensors to adjust
    ;
  gyro.recordGyroRegisters();
  if (abs(gyro.rotZ) <= 5)
  {
    mouse_angle = 0;
  }
}

void loop() {

   if ((analogRead(IR.irArray[0]) < 1000)) {
   wheels.forward(200, 200);
   } else {

   wheels.stop_it();
   IR.CheckFront();
   IR.CheckSides();
   checkingStates();
   }
   while (analogRead(IR.irArray[1]) > 1000) {
   wheels.right_turn(140, 250);
   }
   while (analogRead(IR.irArray[2]) > 1000) {
   wheels.left_turn(250, 140);
   }

/*  while (abs(encoder0PosRight) <= 500) {
    Serial.print(encoder0PosRight);
    Serial.print("  ");
    Serial.println(encoder0PosLeft);
    wheels.forward(255, 225);
  }
  wheels.stop_it();
  Serial.print("Final  Right:");
  Serial.print(encoder0PosRight);
  Serial.print("   Left:");
  Serial.println(encoder0PosLeft);
*/
}

void checkingStates() {
  encoder0PosRight = 0;
  encoder0PosLeft = 0;

  if (IR.state_left and IR.state_mid) {
    while (abs(encoder0PosRight) <= 232 and abs(encoder0PosLeft) <= 200) {
      wheels.right_turn(250, 220);
    }
    wheels.stop_it();
    encoder0PosRight = 0;
    encoder0PosLeft = 0;
    //Serial.println("	Turning Right		");
  }

  else if (IR.state_mid and IR.state_right) {

    while (abs(encoder0PosRight) <= 232 and abs(encoder0PosLeft) <= 200) {
      wheels.left_turn(250, 220);
    }
    wheels.stop_it();

    encoder0PosRight = 0;
    encoder0PosLeft = 0;
    //Serial.println("         Turning left    ");
  }

  else if (IR.state_mid) {
    while (abs(encoder0PosRight) <= 232 and abs(encoder0PosLeft) <= 200) {
      wheels.right_turn(250, 230);
    }
    wheels.stop_it();
    encoder0PosRight = 0;
    encoder0PosLeft = 0;
  }

  else if (IR.state_mid and IR.state_left and IR.state_right) {
    while (abs(encoder0PosRight) <= 464 and abs(encoder0PosLeft) <= 398) {
      wheels.left_turn(250, 230);
    }
    wheels.stop_it();
    //wheels.stop_it();
    encoder0PosRight = 0;
    encoder0PosLeft = 0;

  }

  else if (!IR.state_left and !IR.state_mid and IR.state_right) {
    while (abs(encoder0PosRight) <= 232 and abs(encoder0PosLeft) <= 200) {
      wheels.right_turn(250, 220);
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

