/*
 * This library sets up the motors of the mouse and has turn functions
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

void Motors::right_turn() {
  analogWrite(motor1Pin1, 255);
  analogWrite(motor1Pin2, 0);

  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 255);
  Serial.println("Turning right");
}

void Motors::left_turn() {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 128);

  analogWrite(motor2Pin1, 255);
  analogWrite(motor2Pin2, 0);
  Serial.println("Turning left");
}

void Motors::forward() {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 128);

  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 255);
  Serial.println("Moving Forward");
}

void Motors::backward() {
  analogWrite(motor1Pin1, 150);
  analogWrite(motor1Pin2, 0);

  analogWrite(motor2Pin1, 150);
  analogWrite(motor2Pin2, 0);
  Serial.println("Moving Backwards");
}

void Motors::stop_it() {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 0);

  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 0);
  Serial.println("Stopping");
}
