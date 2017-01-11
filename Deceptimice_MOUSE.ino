#include "Arduino.h"
#include "Dispatch.h"
byte left = A0;
byte right = A2;
byte front = A1;

Dispatch IR(front, left, right);

//0-forward, 1-turnleft,2-turnright, 3-all sided blocked
byte directionState = 0;

void setup() {

  Serial.begin(9600);
  while (millis() != 1000)
    ;
  while (IR.Averagestate == false) {
    Serial.print("IR Calibrated");
    IR.AverageTolly();
  }

}

void loop() {
  Serial.print(IR.IR_middleavg);
  delay(1000);
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

