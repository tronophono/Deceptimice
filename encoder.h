/*
 * encoder.h
 *
 *  Created on: Jan 11, 2017
 *      Author: lasantos
 */


#ifndef ENCODER_H_
#define ENCODER_H_

#include "Arduino.h"
//#include "EnableInterrupt.h"

void encoder_ReadRight(int encoder0PA, int encoder0PB);
void encoder_ReadLeft(int encoder1PA, int encoder1PB);
void doEncoderRightA();
void doEncoderRightB();
void doEncoderLeftA();
void doEncoderLeftB();
void printEncoderValues();


#endif /* ENCODER_H_ */
