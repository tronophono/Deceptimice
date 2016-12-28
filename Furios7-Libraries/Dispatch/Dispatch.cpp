/*
 * Dispatch.cpp
 *
 *  Created on: Dec 20, 2016
 *      Author: lasantos
 */

#include "Dispatch.h"

int irValues[3];
int gyroReading;
int calibrateArray[3];
int irArray[2][1];

//probably will be changed because our IR sensors are not the same as Micromau5 (
Dispatch::Dispatch(int front_ir, int left_ir, int right_ir, int front_in,
		int left_in, int right_in) {
	pinMode(front_ir, OUTPUT);
	pinMode(left_ir, OUTPUT);
	pinMode(right_ir, OUTPUT);
	pinMode(front_in, INPUT);
	pinMode(left_in, INPUT);
	pinMode(right_in, INPUT);

	irArray[0][0] = front_ir;
	irArray[0][1] = front_in;
	irArray[1][0] = left_ir;
	irArray[1][1] = left_in;
	irArray[2][0] = right_ir;
	irArray[2][1] = right_in;
}

void Dispatch::readSensor(int y, int x) {
	int returnVal = analogRead(irArray[y][x]);
	irValues[Dispatch::mapCoords(y, x)] = returnVal;
}

int Dispatch::mapCoords(int y, int x) {
	int returnVal = 0;
	if (y == 0) {
		returnVal = x + y - 1;
	} else if (y & 1) {
		returnVal = x + y;
	} else if (y & 2) {
		returnVal = x + y + 1;
	}
	return returnVal;
}

void Dispatch::powerUp(int ledPin) {
	digitalWrite(ledPin, HIGH);
}

void Dispatch::powerDown(int ledPin) {
	digitalWrite(ledPin, LOW);
}

int Dispatch::getAverage(int ledPin, int y, int x) {
	int runningTally = 0;
	for (int a = 0; a < 10; a++) {
		Dispatch::powerUp(ledPin);
		delayMicroseconds(80);
		Dispatch::readSensor(y, x);
		runningTally += irValues[Dispatch::mapCoords(y, x)];
		Dispatch::powerDown(ledPin);
		delayMicroseconds(80);
	}
	int avgTally = runningTally / 10;
	return avgTally;
}

int Dispatch::getValue(int index) {
	int value = irValues[index] - calibratedArray[index];
	if (value < 0) {
		value = 0;
	}
	return value;
}

//Going to have to modift for limited IR
void Dispatch::calibrateSensors() {
	for (int i = 0; i < 3; i++) {
		for (int j = i; j < 3; j++) {
			calibratedArray[Dispatch::mapCoords(i, j)] = Dispatch::getAverage(
					irArray[i][0], i, j);
		}
	}
}


