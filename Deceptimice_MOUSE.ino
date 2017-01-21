#include "Arduino.h"
#include "Dispatch.h"
#include "Motors.h"
#include "GyroAccel.h"
#include "encoder.h"
#include "math.h"
//#include "EnableInterrupt.h"

byte MOTOR1P1 = 11;
byte MOTOR1P2 = 6;
byte MOTOR2P1 = 10;
byte MOTOR2P2 = 8;
byte enablePin1 = 12;
byte enablePin2 = 7;

byte left = A1;
byte right = A3;
byte front = A2;

Dispatch IR(front, left, right);
Motors wheels(MOTOR1P1, MOTOR1P2, MOTOR2P1, MOTOR2P2, enablePin1, enablePin2);
GyroAccel gyro;

//0-forward, 1-turnleft,2-turnright, 3-all sided blocked
byte directionState = 0;

byte buttonPin = 13;

boolean button_state = false;

double angleX;

void setup() {

  Serial.begin(9600);
  while (millis() != 1000)
    ;
  while (IR.Averagestate == false) {
    IR.AverageTolly();
    if (IR.Averagestate == true) {
//      Serial.print("IR Calibrated");
    }
  }

  encoder_ReadRight(2, 3);
  encoder_ReadLeft(4, 5);
  gyro.setup();

}

void loop() {
   IR.CheckFront();
   if (IR.state_mid != 1) {
   wheels.forward();
   } else {
   wheels.stop_it();
   IR.CheckSides();
   checkingStates();
   }


  //wheels.right_turn();
}

void checkingStates() {
  if (IR.state_left and IR.state_mid) {
    directionState = 2;
    gyro.recordGyroRegisters();
    while (abs(gyro.angle) <= 75) {
      wheels.right_turn();
      gyro.recordGyroRegisters();
    }
    gyro.angle = 0;
    wheels.stop_it();
    //Serial.println("	Turning Right		");
  } else if (IR.state_left and IR.state_right and not IR.state_mid) {
    directionState = 0;
    wheels.forward();
    //Serial.println("			Going Forward		");
  } else if (IR.state_mid and IR.state_right) {
    directionState = 1;
    while (abs(gyro.angle) <= 75) {
      wheels.left_turn();
      gyro.recordGyroRegisters();
    }
    gyro.angle = 0;
    wheels.stop_it();
    //Serial.println("         Turning left    ");
  } else if (IR.state_mid and IR.state_left and IR.state_right) {
    directionState = 3;
    wheels.stop_it();
    //Serial.println("           Stopping   ");
  }
  if (IR.state_mid) {
    gyro.recordGyroRegisters();
    while (abs(gyro.angle) != 85) {
      wheels.left_turn();
      gyro.recordGyroRegisters();
    }
    gyro.angle = 0;
    wheels.stop_it();
  }
}

