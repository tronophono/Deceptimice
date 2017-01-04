/*
 * Dispatch.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: lasantos
 *
 *      This library contains all the functions you can use to an object of type Dispatch.
 *
 *		This functions include setting up the pins in which the IR sensors are connected, and be able to read
 *
 *		the analog values of the sensor.
 */

#include "Dispatch.h"

/*This is the constructor, it is code that will be executed when you make an object in C++.
 * In this case we are setting up the IR sensors.
 */



Dispatch::Dispatch(int front_in, int left_in, int right_in) {

	pinMode(front_in, INPUT);
	pinMode(left_in, INPUT);
	pinMode(right_in, INPUT);

	irArray[0] = front_in;
	irArray[1] = left_in;
	irArray[2] = right_in;
}

//This function has not been tested, but it is there until there is a need for it.
void Dispatch::readSensor(int y,int x) {
	int returnVal = analogRead(irArray[y]);
	irValues[Dispatch::mapCoords(y, x)] = returnVal;
}

//This function has not been tested, but it is there until there is a need for it.
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

//This will power up the selected IR sensor, a simple digitalWrite.
void Dispatch::powerUp(int ledPin) {
	digitalWrite(ledPin, HIGH);
}

void Dispatch::powerDown(int ledPin) {
	digitalWrite(ledPin, LOW);
}

//gets an average reading of 1 sensor
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

//gets value that is stored on irValues array
int Dispatch::getValue(int index) {
	int value = irValues[index] - calibratedArray[index];
	if (value < 0) {
		value = 0;
	}
	return value;
}

//Used to calibrate sensors, yet to be tested
void Dispatch::calibrateSensors() {
	for (int i = 0; i < 3; i++) {
		for (int j = i; j < 3; j++) {
			calibratedArray[Dispatch::mapCoords(i, j)] = Dispatch::getAverage(irArray[i], i, j);
		}
	}
}

//Temporary function to read raw values of sensor, it returns a value so make sure to have it stored in another variable
long int Dispatch::rawData(int ledPin) {
	long int value = analogRead(ledPin);
	return value;
}

