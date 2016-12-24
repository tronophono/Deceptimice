/*
 * GyroAccel.h
 *
 *  Created on: Dec 21, 2016
 *      Author: lasantos
 */




#ifndef FURIOS7_LIBRARIES_GYROACCEL_GYROACCEL_H_
#define FURIOS7_LIBRARIES_GYROACCEL_GYROACCEL_H_

class GyroAccel {
public:
	GyroAccel();
//	long accelX,accelY,accelZ,gyroX,gyroY,gyroZ;
//	float gForceX,gForceY,gForceZ,rotX,rotY,rotZ,angle,average;

	void recordAccelRegisters();
	void recordGyroRegisters();
	void printgyro();
	//void printaccel();


};

#endif /* FURIOS7_LIBRARIES_GYROACCEL_GYROACCEL_H_ */
