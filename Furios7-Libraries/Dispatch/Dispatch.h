/*
 * Dispatch.h
 *
 *  Created on: Dec 20, 2016
 *      Author: lasantos
 */

#include "Arduino.h"
#include "/home/lasantos/GeneralWorkspace/MicromouseProject/Furios7-Libraries/GyroAccel/GyroAccel.h"

#ifndef FURIOS7_LIBRARIES_DISPATCH_DISPATCH_H_
#define FURIOS7_LIBRARIES_DISPATCH_DISPATCH_H_

class Dispatch {
public:

	Dispatch(int front_ir, int left_ir, int right_ir, int front_in, int left_in,int right_in);
	void readSensor(int y, int x);
	void powerUp(int ledPin); //Uss if want led as indicator
	void powerDown(int ledPin);
	void calibrateSensors();
	int mapCoords(int y, int x);
	int getValue(int index);
	int irArray[2][1];
	int calibratedArray[6];
	int irValues[6];
	int getAverage(int ledPin, int y, int x);
	GyroAccel gyro;
	float gyroVal=0;
	void setGyro(double gyroReading);

};

#endif /* FURIOS7_LIBRARIES_IR_IR_H_ */
