#include "Arduino.h"
#include "Motors.h"
#include "EnableInterrupt.h"

Motors::Motors(int motor1p1, int motor1p2,int motor2p1,int motor2p2,int enablep1,int enablep2){

	// set all the other pins you're using as outputs:
	pinMode(motor1p1, OUTPUT);
	pinMode(motor1p2, OUTPUT);
	pinMode(motor2p1, OUTPUT);
	pinMode(motor2p2, OUTPUT);
	pinMode(enablep, OUTPUT);
	pinMode(enablep2, OUTPUT);

	// set enablePin high so that motor can turn on:
	digitalWrite(enablePin, HIGH);
	digitalWrite(enablePin2, HIGH);

}

void Motors::right_turn(){
	analogWrite(motor1Pin1, 255);
	analogWrite(motor1Pin2, 0);

	analogWrite(motor2Pin1, 0);
	analogWrite(motor2Pin2, 255);
}

void Motors::left_turn(){
	analogWrite(motor1Pin1, 0);
	analogWrite(motor1Pin2, 128);

	analogWrite(motor2Pin1, 255);
	analogWrite(motor2Pin2, 0);
}

void Motors::forward(){
	analogWrite(motor1Pin1, 0);
	analogWrite(motor1Pin2, 128);

	analogWrite(motor2Pin1, 0);
	analogWrite(motor2Pin2, 255);
}

void Motors::backward(){
	analogWrite(motor1Pin1, 150);
	analogWrite(motor1Pin2, 0);

	analogWrite(motor2Pin1, 150);
	analogWrite(motor2Pin2, 0);
}

void Motors::stop_it(){
	analogWrite(motor1Pin1, 0);
	analogWrite(motor1Pin2, 0);

	analogWrite(motor2Pin1, 0);
	analogWrite(motor2Pin2, 0);
}
