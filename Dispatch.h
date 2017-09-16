/*
 * Dispatch.h
 *
 *  Created on: Dec 29, 2016
 *      Author: lasantos
 *
 *
 *  Objective
 *  -----------
 *  	This class allows you to set up three IR sensors and provides logic for wall detection.
 *  	In order for the values to work you must set a constructor with values.
 *
 *   ---------
 *	|Functions|
 *	 ---------
 *	AverageTolly() - Takes the average of the three IR Sensors to set up a upper and lower bound
 *
 *	CheckFront() - Will check the front IR sensor change the state of the state_mid variable
 *
 *	CheckSide() - Checks the side IR sensors and changes the state of the state_left and state_right variables
 *
 *	RawValues() - Prints the values of all the IR sensors with Serial.print, can be seen in Serial Monitor or Plotter
 *					+ This is used for debugging purposes
 *
 */

#ifndef DISPATCH_H_
#define DISPATCH_H_

#include "Arduino.h"

class Dispatch {
 public:

  Dispatch(byte front_in, byte left_in, byte right_in);

  boolean Averagestate = false;
  unsigned int IR_leftavg = 0;
  long int IR_rightavg = 0;
  long int IR_middleavg = 0;
  int MiddleWallPoint = 985; //Can be adjusted based on IR sensor sensetivity
  byte state_mid = 0;
  byte state_left = 0;
  byte state_right = 0;
  int irArray[3];

  void AverageTolly();
  void CheckFront();
  void CheckSides();
  void RawValues();

};

#endif /* FURIOS7_LIBRARIES_DISPATCH_DISPATCH_H_ */
