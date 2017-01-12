#include "Arduino.h"
#include "Dispatch.h"
#include "Motors.h"
#include "GyroAccel.h"
#include "encoder.h"

byte MOTOR1P1=11;
byte MOTOR1P2=6;
byte MOTOR2P1=10;
byte MOTOR2P2=8;
byte enablePin1=12;
byte enablePin2=7;


byte left = A1;
byte right = A3;
byte front = A2;

Dispatch IR(front, left, right);
Motors wheels(MOTOR1P1,MOTOR1P2,MOTOR2P1,MOTOR2P2,enablePin1,enablePin2);
//0-forward, 1-turnleft,2-turnright, 3-all sided blocked
byte directionState = 0;

GyroAccel gyro;


void setup() {

  Serial.begin(9600);
  while (millis() != 1000)
    ;
  while (IR.Averagestate == false) {
    IR.AverageTolly();
    if(IR.Averagestate == true)
    {
      Serial.print("IR Calibrated");
    }
  }

  encoder_ReadRight(2,3);
  encoder_ReadLeft(4,5);
  gyro.setup();


}

void loop() {
  Serial.println("--------------------");
  Serial.println("This are IR values");
  IR.RawValues();
  delay(1000);
  Serial.println("------Gyro Values----");
  gyro.recordGyroRegisters();
  gyro.printgyro();
  delay(1000);

  Serial.println("--------This are encoder values-------");
 printEncoderValues();
}

void checkingStates() {
  if (IR.state_left and IR.state_mid) {
    directionState = 2;
    Serial.println("	Turning Right		");
  } else if (IR.state_left and IR.state_right) {
    directionState = 0;
    Serial.println("			Going Forward		");
  } else if (IR.state_mid and IR.state_right) {
    directionState = 1;
    Serial.println("         Turning left    ");
  } else if (IR.state_mid and IR.state_left and IR.state_right) {
    directionState = 3;
    Serial.println("           Stopping   ");
  }
}
