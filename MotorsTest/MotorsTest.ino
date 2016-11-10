#include "Arduino.h"
#include "motors.h"    //This library will contain the motors_set and button_set functions

void setup() {

	motors_set(12, 11, 9, 10, 13, 2);
	button_set(7, 6, 5, 4, 3);
}

void loop() {
	//The buttons are controlled via interrupts so there loop is empty.
}
