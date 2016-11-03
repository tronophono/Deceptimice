#include "Arduino.h"
#include "motors.h"

int switchPin; // switch input
int motor1Pin1; // pin 2 on L293D //left motor
int motor1Pin2; // pin 7 on L293D
int motor2Pin1; //right motor
int motor2Pin2;
int enablePin; // pin 1 on L293D
int enablePin2;

void motors_set(int a, int b,int c, int d, int e, int f, int g)
{
	switchPin = a; // switch input
	motor1Pin1 = b; // pin 2 on L293D //left motor
	motor1Pin2 = c; // pin 7 on L293D
	motor2Pin1 = d; //right motor
	motor2Pin2 = e;
	enablePin = f; // pin 1 on L293D
	enablePin2 = g;

    pinMode(switchPin, INPUT);

    // set all the other pins you're using as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(enablePin2,OUTPUT);
    // set enablePin high so that motor can turn on:
    digitalWrite(enablePin, HIGH);
    digitalWrite(enablePin2, HIGH);
}

void left_turn()
{
  //Motor to turn left for 10 seconds
  analogWrite(motor1Pin1,50);
  analogWrite(motor1Pin2,0);

  analogWrite(motor2Pin1,0);
  analogWrite(motor2Pin2,50);

}

void right_turn()
{
  //Motor to turn left for 10 seconds
  analogWrite(motor1Pin1,0);
  analogWrite(motor1Pin2,200);

  analogWrite(motor2Pin1,0);
  analogWrite(motor2Pin2,50);
}

void backward()
{

  analogWrite(motor1Pin1,50);
  analogWrite(motor1Pin2,0);

  analogWrite(motor2Pin1,0);
  analogWrite(motor2Pin2,50);
}

void forward()
{
	analogWrite(motor1Pin1,0);
    analogWrite(motor1Pin2,50);

    analogWrite(motor2Pin1,50);
    analogWrite(motor2Pin2,0);
}

