#include "Arduino.h"
#include "motors.h"    //This library will contain the motors_set and button_set functions

//float ir_front = 0;
//float ir_frontt= 0;

void setup() {

	motors_set(11, 12, 9, 10, 15, 14);
	button_set(2, 3, 4, 5, 6);
	encoder_ReadRight(7, 8);
	encoder_ReadLeft(16, 17);
//	ir_front = ir_read(7);
	setupMPU();
	Serial.begin(9600);

}

void loop() {
	//The buttons are controlled via interrupts so there loop is empty.
	recordAccelRegisters();
	recordGyroRegisters();
//	ir_frontt = ir_read(7);
	print();

/*	if (ir_frontt < ir_front*.5)
	{
		printr();
	}*/



}
