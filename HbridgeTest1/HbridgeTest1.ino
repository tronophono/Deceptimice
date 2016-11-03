#include "Arduino.h" //Used if you do not use arduino ide
#include "motors.h"
/*
int switchPin = 2; // switch input
int motor1Pin1 = 3; // pin 2 on L293D //left motor
int motor1Pin2 = 4; // pin 7 on L293D
int motor2Pin1 = 5; //right motor
int motor2Pin2 = 6;
int enablePin = 9; // pin 1 on L293D
int enablePin2 = 10;
*/

void setup() {
    // set the switch as an input:
	motors_set(2,3,4,5,6,9,10);
}

void loop()
{
  for(int i=0;i<100;i++)
  {
    forward();
  }
  delay(1000);
  for (int i = 0;i<100;i++)
  {
	  backward();
  }
  delay(1000);
  for(int i = 0 ; i<100;i++)
  {
	  left_turn();
  }
  delay(1000);
  for(int i = 0 ; i<100;i++)
    {
  	  right_turn();
    }
    delay(1000);
}
