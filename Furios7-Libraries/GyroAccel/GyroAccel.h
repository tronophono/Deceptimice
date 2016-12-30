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

class GyroAccel {
public:
	GyroAccel();

	void recordAccelRegisters();
	void recordGyroRegisters();
	void printgyro();
	void printaccel();

};

#endif /* FURIOS7_LIBRARIES_GYROACCEL_GYROACCEL_H_ */
