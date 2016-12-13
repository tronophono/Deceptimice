#include "Arduino.h"
#include "motors.h"    //This library will contain the motors_set and button_set functions

void setup() {

	motors_set(11, 12, 9, 10, 15, 14);
	button_set(2, 3, 4, 5, 6);
	encoder_read(7, 8);
	setupMPU();
	Serial.begin(9600);

}

void loop() {
	
	recordAccelRegisters();
	recordGyroRegisters();
	ir_read(7);

}
