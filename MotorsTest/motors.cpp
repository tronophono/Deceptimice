#include "Arduino.h"
#include "motors.h"
#include "EnableInterrupt.h"
/*
 Refer to the L293D pinout png file
 */

//Variables for H-bridge pins
int motor1Pin1; //Pin connected to Input 1
int motor1Pin2; //Pin connected to Input 2
int motor2Pin1; //Pin connected to Input 3
int motor2Pin2; //Pin connected to input 4
int enablePin; //Pin connected to Enable pin 1
int enablePin2; //Pin connected to Enable pin 2

//-----------------------------------------------------

//Variables for button interrupts
int button_left;
int button_right;
int button_back;
int button_forw;
int button_stp;
//--------------------------------------------------------

//Enter the pins that correspond to your buttons in this order
void button_set(int left, int right, int back, int forw, int stop) {
	/*Sets up the button variables used to control motors.*/
	button_left = left;
	button_right = right;
	button_back = back;
	button_forw = forw;
	button_stp = stop;

	enableInterrupt(button_left, left_turn, RISING);
	enableInterrupt(button_right, right_turn, RISING);
	enableInterrupt(button_back, backward, RISING);
	enableInterrupt(button_forw, forward, RISING);
	enableInterrupt(button_stp, stop_it, RISING);

}


//Enter the pin numbers in which you connected pins of the H-bridge
void motors_set(int motor1p1, int motor1p2, int motor2p1, int motor2p2,int enablep1,int enablep2) {

	motor1Pin1 = motor1p1;
	motor1Pin2 = motor1p2;
	motor2Pin1 = motor2p1;
	motor2Pin2 = motor2p2;
	enablePin = enablep1;
	enablePin2 = enablep2;


	// set all the other pins you're using as outputs:
	pinMode(motor1Pin1, OUTPUT);
	pinMode(motor1Pin2, OUTPUT);
	pinMode(motor2Pin1, OUTPUT);
	pinMode(motor2Pin2, OUTPUT);
	pinMode(enablePin, OUTPUT);
	pinMode(enablePin2, OUTPUT);

	// set enablePin high so that motor can turn on:
	digitalWrite(enablePin, HIGH);
	digitalWrite(enablePin2, HIGH);
}
//-------------------------------------------------------


//The following is writing an analog signal to the motors to move at a certain direction
/*NOTE
 * 			For the actual motor control, the functions will be dependent on the input of the
 * 			IR receivers. The larger the IR values the faster the motors will go.
 */


void left_turn() {

	analogWrite(motor1Pin1, 150);
	analogWrite(motor1Pin2, 0);

	analogWrite(motor2Pin1, 0);
	analogWrite(motor2Pin2, 150);

}

void right_turn() {

	analogWrite(motor1Pin1, 0);
	analogWrite(motor1Pin2, 200);

	analogWrite(motor2Pin1, 150);
	analogWrite(motor2Pin2, 0);
}

void backward() {

	analogWrite(motor1Pin1, 0);
	analogWrite(motor1Pin2, 150);

	analogWrite(motor2Pin1, 0);
	analogWrite(motor2Pin2, 150);
}

void forward() {
	analogWrite(motor1Pin1, 150);
	analogWrite(motor1Pin2, 0);

	analogWrite(motor2Pin1, 150);
	analogWrite(motor2Pin2, 0);
}

void stop_it() {
	analogWrite(motor1Pin1, 0);
	analogWrite(motor1Pin2, 0);

	analogWrite(motor2Pin1, 0);
	analogWrite(motor2Pin2, 0);
}

