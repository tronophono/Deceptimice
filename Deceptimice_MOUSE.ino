//#include "/home/lasantos/Desktop/Micromouse/Furios7-Micromouse/Furios7-Libraries/Dispatch/Dispatch.h"
#include "/home/lasantos/Desktop/Micromouse/Furios7-Micromouse/Furios7-Libraries/GyroAccel/GyroAccel.h"
int front_in = 15;
int left_in = 17;
int right_in = 16;

unsigned long interval = 1000;
unsigned long previoustime = 0;
/*
 int MOTOR1PIN1 = 11;
 int MOTOR1PIN2 = 12;
 int MOTOR2PIN1 = 9;
 int MOTOR2PIN2 = 10;
 int ENABLEPIN1 = 8;
 int ENABLEPIN2 = 7;
 */

//Dispatch IR(front_in, left_in, right_in);
GyroAccel gyro;

void setup() {
	Serial.begin(9600);
}

void loop() {


	gyro.recordGyroRegisters();
	gyro.printgyro();
	delay(1000);

}

