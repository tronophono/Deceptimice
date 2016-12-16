#include "Arduino.h"
#include <Wire.h>
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

//---------------------------------------------------

//Variables for button interrupts
int button_left;
int button_right;
int button_back;
int button_forw;
int button_stp;

//--------------------------------------------------------

//Variables for the IR_sensors
float result = 0;
byte ir1Pin1;

//-------------------------------------------------------

//Variables for MPU6050
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ, angle, average;

//--------------------------------------------------------

//Variable for the count of the encoder
volatile long encoder0PosRight = 0;
volatile long encoder0PosLeft = 0;
int encoder0PinA;
int encoder0PinB;
int encoder1PinA;
int encoder1PinB;

//---------------------------------------------------

//Enter the pin that correspond to encoderRight readings
void encoder_ReadRight(int encoder0PA, int encoder0PB) {

	encoder0PinA = encoder0PA;
	encoder0PinB = encoder0PB;
	pinMode(encoder0PinA, INPUT);
	pinMode(encoder0PinB, INPUT);

	enableInterrupt(encoder0PinA, doEncoderRightA, CHANGE);
	enableInterrupt(encoder0PinB, doEncoderRightB, CHANGE);
}

//Enter the pin that correspond to encoderLeft readings
void encoder_ReadLeft(int encoder1PA, int encoder1PB) {

	encoder1PinA = encoder1PA;
	encoder1PinB = encoder1PB;
	pinMode(encoder1PinA, INPUT);
	pinMode(encoder1PinB, INPUT);

	enableInterrupt(encoder1PinA, doEncoderLeftA, CHANGE);
	enableInterrupt(encoder1PinB, doEncoderLeftB, CHANGE);
}

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
void motors_set(int motor1p1, int motor1p2, int motor2p1, int motor2p2,
		int enablep1, int enablep2) {

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

//This is the fuctions that takes care of the count of the encoders Right

void doEncoderRightA() {

	// look for a low-to-high on channel A
	if (digitalRead(encoder0PinA) == HIGH) {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoder0PinB) == LOW) {
			encoder0PosRight = encoder0PosRight + 1;         // CW
		} else {
			encoder0PosRight = encoder0PosRight - 1;         // CCW
		}
	} else // must be a high-to-low edge on channel A
	{
		// check channel B to see which way encoder is turning
		if (digitalRead(encoder0PinB) == HIGH) {
			encoder0PosRight = encoder0PosRight + 1;          // CW
		} else {
			encoder0PosRight = encoder0PosRight - 1;          // CCW
		}
	}
	if (encoder0PosRight >= 100000) {
		stop_it();
		encoder0PosRight = 0;
	}
	// use for debugging - remember to comment out
}

void doEncoderRightB() {

	// look for a low-to-high on channel B
	if (digitalRead(encoder0PinB) == HIGH) {
		// check channel A to see which way encoder is turning
		if (digitalRead(encoder0PinA) == HIGH) {
			encoder0PosRight = encoder0PosRight + 1;         // CW
		} else {
			encoder0PosRight = encoder0PosRight - 1;         // CCW
		}
	}
	// Look for a high-to-low on channel B
	else {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoder0PinA) == LOW) {
			encoder0PosRight = encoder0PosRight + 1;          // CW
		} else {
			encoder0PosRight = encoder0PosRight - 1;          // CCW
		}
	}
	if (encoder0PosRight >= 100000) {
		stop_it();
		encoder0PosRight = 0;
	}
}

//This is the functions that takes care of the count of the encoders left

void doEncoderLeftA() {

	// look for a low-to-high on channel A
	if (digitalRead(encoder1PinA) == HIGH) {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoder1PinB) == LOW) {
			encoder0PosLeft = encoder0PosLeft - 1;         // CW
		} else {
			encoder0PosLeft = encoder0PosLeft + 1;         // CCW
		}
	} else // must be a high-to-low edge on channel A
	{
		// check channel B to see which way encoder is turning
		if (digitalRead(encoder1PinB) == HIGH) {
			encoder0PosLeft = encoder0PosLeft - 1;          // CW
		} else {
			encoder0PosLeft = encoder0PosLeft + 1;          // CCW
		}
	}
	if (encoder0PosLeft >= 100000) {
		stop_it();
		encoder0PosLeft = 0;
	}
	// use for debugging - remember to comment out
}

void doEncoderLeftB() {

	// look for a low-to-high on channel B
	if (digitalRead(encoder1PinB) == HIGH) {
		// check channel A to see which way encoder is turning
		if (digitalRead(encoder1PinA) == HIGH) {
			encoder0PosLeft = encoder0PosLeft - 1;         // CW
		} else {
			encoder0PosLeft = encoder0PosLeft + 1;         // CCW
		}
	}
	// Look for a high-to-low on channel B
	else {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoder1PinA) == LOW) {
			encoder0PosLeft = encoder0PosLeft - 1;          // CW
		} else {
			encoder0PosLeft = encoder0PosLeft + 1;          // CCW
		}
	}
	if (encoder0PosLeft >= 100000) {
		stop_it();
		encoder0PosLeft = 0;
	}
}

//Function for the Gyro and Accelerometer

void setupMPU() {
	Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
	Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
	Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
	Wire.endTransmission();
	Wire.beginTransmission(0b1101000); //I2C address of the MPU
	Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
	Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s
	Wire.endTransmission();
	Wire.beginTransmission(0b1101000); //I2C address of the MPU
	Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
	Wire.write(0b00000000); //Setting the accel to +/- 2g
	Wire.endTransmission();
}

void recordAccelRegisters() {
	Wire.beginTransmission(0b1101000); //I2C address of the MPU
	Wire.write(0x3B); //Starting register for Accel Readings
	Wire.endTransmission();
	Wire.requestFrom(0b1101000, 6); //Request Accel Registers (3B - 40)
	while (Wire.available() < 6)
		;
	accelX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
	accelY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
	accelZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
	gForceX = accelX / 16384.0;
	gForceY = accelY / 16384.0;
	gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
	Wire.beginTransmission(0b1101000); //I2C address of the MPU
	Wire.write(0x43); //Starting register for Gyro Readings
	Wire.endTransmission();
	Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
	while (Wire.available() < 6)
		;
	gyroX = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
	gyroY = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
	gyroZ = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ

	rotX = gyroX / 131.0;
	rotY = gyroY / 131.0;
	rotZ = gyroZ / 131.0;
	angle += rotZ / 16 + 0.038;
	for (int i = 0; i < 10; i++) {
		average += angle;
	}
	average /= 10;
}

//Function for the infrared sensor
/* Reads 1000 times the input and divides it by 1000
 * to get the average.
 * 
 * The printing of values takes place here
 */
void ir_read(int ir1Pin) {
	ir1Pin1 = ir1Pin;

	for (int i; i < 1000; i++) {

		result += analogRead(ir1Pin1);
	}
	result /= 1000;

	Serial.print("IR_sensor:");
	Serial.print(result);
	Serial.print(" encoderRight:");
	Serial.print(encoder0PosRight, DEC);
	Serial.print(" encoderLeft:");
	Serial.print(encoder0PosLeft, DEC);
	Serial.print(" Gyro (deg)");
	Serial.print(" X=");
	Serial.print(rotX);
	Serial.print(" Y=");
	Serial.print(rotY);
	Serial.print(" Z=");
	Serial.print(rotZ);
	Serial.print(" Angle=");
	Serial.print(angle);
	Serial.print(" Average=");
	Serial.println(average);
//	return result;
}

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
	analogWrite(motor1Pin2, 150);

	analogWrite(motor2Pin1, 150);
	analogWrite(motor2Pin2, 0);
}

void forward() {

	analogWrite(motor1Pin1, 0);
	analogWrite(motor1Pin2, 128);

	analogWrite(motor2Pin1, 0);
	analogWrite(motor2Pin2, 255);
}

void backward() {
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

//Use encoders for 90 degree turns for now.

void print() {

}

void turn90_right() {

	while(average <= 30)
	{
		right_turn();
	}

	stop_it();
}

void turn90_left() {
	while(average <= 30)
		{
			left_turn();
		}

		stop_it();

}

void turn180() {
	while(average <= 60)
		{
			right_turn();
		}

		stop_it();
}


void printr()
{
	Serial.print(" Andrew has cookies ");
}
