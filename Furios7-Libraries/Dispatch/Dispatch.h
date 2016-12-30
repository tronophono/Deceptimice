/*
 * Dispatch.h
 *
 *  Created on: Dec 29, 2016
 *      Author: lasantos
 *
 *      This file is like a summary of the library that we made.
 *
 *      This file contains all the functions inside the library file but without needing to look at the details
 *
 *      Unlike C libraries, here we made a library that makes use of classes that is provided in C++
 *
 *      this allows us to to relate this library into a variable name.
 *      --------------------------
 *     	ex:
 *
 *     	Class variable;
 *     	variable.function_name;
 *     	--------------------------
 *
 *     	variable is then made to be in an "object", in which it will attain all the properties of the class
 *     	This is where C++ starts implementing some object oriented programming concepts. Its not that hard once
 *     	you play with it a little.
 *
 *     	Comments will be provided to walk you through the code.
 */

//	The next two lines is just to make sure that the inclusion of the code is no repeated when being compiled
#ifndef FURIOS7_LIBRARIES_DISPATCH_DISPATCH_H_
#define FURIOS7_LIBRARIES_DISPATCH_DISPATCH_H_

// Here we include the Arduino library, in the arduino ide it is included automatically. I use eclipse so I include it.
#include "Arduino.h"

/*	Here we include the gyro library, you basically copy the folder path in which the file is at
 *
 * 	 to keep it simple you can move the GyroAccel.h from the GyroAccel folder to the same folder
 *	 where the MicroMouse.ino file is at. This way you can have:
 *
 *	 #include "GyroAccel.h"
 *
 *	 Instead of the long mess that I have
 *
 */

#include "/home/lasantos/Desktop/Micromouse/Furios7-Micromouse/Furios7-Libraries/GyroAccel/GyroAccel.h"

//Here is where we create the class Dispatch and provide the functions that will go with it.
class Dispatch {
public:

	/*This is called a constructor, it is like a default functions that happens by default, I usually use them to set up the object,
	 * in this case the constructor will assign the pin number given to it in the following order.
	 */
	Dispatch(int front_ir, int left_ir, int right_ir, int front_in, int left_in,
			int right_in);

	//Variables that come with the class
	GyroAccel gyro;
	int irArray[3][2];
	int calibratedArray[3];
	int irValues[3];
	float gyroVal = 0;


	//Functions of the class
	void readSensor(int y, int x);
	void powerUp(int ledPin);
	void powerDown(int ledPin);
	void calibrateSensors();
	int mapCoords(int y, int x);
	int getValue(int index);

	int getAverage(int ledPin, int y, int x);

	void setGyro(double gyroReading);
	long int rawData(int ledPin);

};

#endif /* FURIOS7_LIBRARIES_DISPATCH_DISPATCH_H_ */
