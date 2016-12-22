#include "Arduino.h"
#include "motors.h"

void setup() {
  // put your setup code here, to run once:
motors_set(11,12,9,10,15,14);
button();
Left_Enc(16,17);
Right_Enc(7,8);
SetupMPU();
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
read_Accel();
read_Gyro();
read_IR(7);
}
