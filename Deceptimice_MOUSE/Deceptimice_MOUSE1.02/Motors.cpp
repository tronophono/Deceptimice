/*
 * This library sets up the motors of the mouse and has turn functions
 *
 *
 * Updated functions to take a speed as an int. This way we can adjust speed as we need it.
 */


#include "Motors.h"
#include "Arduino.h"

int motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, EnablePin1, EnablePin2;

Motors::Motors(int motor1p1, int motor1p2, int motor2p1, int motor2p2,
               int enablep1, int enablep2) {

  // set all the other pins you're using as outputs:
  pinMode(motor1p1, OUTPUT);
  pinMode(motor1p2, OUTPUT);
  pinMode(motor2p1, OUTPUT);
  pinMode(motor2p2, OUTPUT);
  pinMode(enablep1, OUTPUT);
  pinMode(enablep2, OUTPUT);

  motor1Pin1 = motor1p1;
  motor1Pin2 = motor1p2;
  motor2Pin1 = motor2p1;
  motor2Pin2 = motor2p2;
  EnablePin1 = enablep1;
  EnablePin2 = enablep2;

  // set enablePin high so that motor can turn on:
  digitalWrite(EnablePin1, HIGH);
  digitalWrite(EnablePin2, HIGH);
  motorsState=1;
}

void Motors::right_turn(int speedL, int speedR) {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, speedL); // left wheel work

  analogWrite(motor2Pin1, 0); // right wheen no work
  analogWrite(motor2Pin2, speedR);
  //Serial.println("Turning right");
}

void Motors::left_turn(int speedL, int speedR) {
  analogWrite(motor1Pin1, speedL); // left wheel = no work
  analogWrite(motor1Pin2, 0);

  analogWrite(motor2Pin1, speedR); //right wheel = works
  analogWrite(motor2Pin2, 0);
 // Serial.println("Turning left");
}

void Motors::forward(int speedL, int speedR) {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, speedL);

  analogWrite(motor2Pin1, speedR);
  analogWrite(motor2Pin2, 0);
 // Serial.println("Moving Forward");
}

void Motors::backward(int speedL, int speedR) {
  analogWrite(motor1Pin1, speedL); //no work
  analogWrite(motor1Pin2, 0);

  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, speedR); //no work
  //Serial.println("Moving Backwards");
}

void Motors::stop_it() {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 0);

  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 0);
  //Serial.println("Stopping");
}
