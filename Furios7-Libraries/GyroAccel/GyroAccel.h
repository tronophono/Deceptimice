/*
 * GyroAccel.h
 *
 *  Created on: Dec 21, 2016
 *      Author: lasantos
 */

/*
 * This library reads the gyroscope and returns a value, can be translated to a angle of course
 *
 * This is yet to be optimized but the functions work
 *
 * Ex:
 * ----------------------------
 * 	GyroAccel gyro;
 *
 * 	gyro.recordGyroRegisters();
 * 	---------------------------
 *
 * 	You can read the accelerometer values as well and print the values with printgyro() or printaccel().
 *
 *
 *
 */

#ifndef FURIOS7_LIBRARIES_GYROACCEL_GYROACCEL_H_
#define FURIOS7_LIBRARIES_GYROACCEL_GYROACCEL_H_
#include "Arduino.h"
#include <Wire.h>
class GyroAccel {
public:
	GyroAccel(void);

	long accelX = 0;
	long accelY = 0;
	long accelZ = 0;
	long gyroX = 0;
	long gyroY = 0;
	long gyroZ = 0;
	float gForceX = 0;
	float gForceY = 0;
	float gForceZ = 0;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;
	float angle = 0;
	float average = 0;
	void recordAccelRegisters(void);
	void recordGyroRegisters(void);
	void printgyro(void);
	void printaccel(void);

};

#endif /* FURIOS7_LIBRARIES_GYROACCEL_GYROACCEL_H_ */
