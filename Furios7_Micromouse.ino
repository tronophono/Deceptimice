/*
 * This code is simply testing Dispatch set up.
 *
 * It will turn on all the ir sensors and read an value from the front IR sensor.
 */




#include "/home/lasantos/GeneralWorkspace/MicromouseProject/Furios7-Libraries/Motors/Motors.h"    //This library will contain the motors_set and button_set functions
#include "/home/lasantos/Desktop/Micromouse/Furios7-Micromouse/Furios7-Libraries/Dispatch/Dispatch.h"
#include "/home/lasantos/Desktop/Micromouse/Furios7-Micromouse/Furios7-Libraries/GyroAccel/GyroAccel.h"




/*int MOTOR1PIN1 = 11;
 int MOTOR1PIN2 = 12;
 int MOTOR2PIN1 = 9;
 int MOTOR2PIN2 = 10;
 int ENABLEPIN1 = 15;
 int ENABLEPIN2 = 14;
 */

int front_ir = 7;
int left_ir = 8;
int right_ir = 6;

int front_in = 17;
int left_in = 16;
int right_in = 18;

Dispatch ir(front_ir, left_ir, right_ir, front_in, left_in, right_in);

int left = ir.irArray[1][0];
int front = ir.irArray[0][0];
int right = ir.irArray[2][0];
byte state = 0;
void setup() {

	/*
	 motors_set(11, 12, 9, 10, 15, 14);
	 button_set(2, 3, 4, 5, 6);*/
//	wheels.Motors(MOTsOR1PIN1,MOTOR1PIN2,MOTOR2PIN1,10,15,14);
	for (int i=0;i<2;i++)
	{
		ir.powerUp(ir.irArray[i][0]);
	}
	Serial.begin(9600);
}

void loop() {
	//ir.powerUp(ir.irArray[1][0]);
	long data;
	data = ir.rawData(ir.irArray[0][1]);
	Serial.println(data);

}
