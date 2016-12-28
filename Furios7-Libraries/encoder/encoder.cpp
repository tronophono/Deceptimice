#include "/home/lasantos/GeneralWorkspace/MicromouseProject/Furios7-Libraries/Motors/Motors.h"
#include "EnableInterrupt.h"
#include "encoder.h"


static int encoderRp1, encoderRp2, encoderLp1, encoderLp2;
int encoderRightCount, encoderLeftCount;

static void encoder::addCountR1() {

	// look for a low-to-high on channel A
	if (digitalRead(encoderRp1) == HIGH) {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoderRp2) == LOW) {
			encoderRightCount = encoderRightCount + 1;         // CW
		} else {
			encoderRightCount = encoderRightCount - 1;         // CCW
		}
	} else // must be a high-to-low edge on channel A
	{
		// check channel B to see which way encoder is turning
		if (digitalRead(encoderRp2) == HIGH) {
			encoderRightCount = encoderRightCount + 1;          // CW
		} else {
			encoderRightCount = encoderRightCount - 1;          // CCW
		}
	}
	// use for debugging - remember to comment out
}

static void encoder::addCountR2() {

	// look for a low-to-high on channel B
	if (digitalRead(encoderRp2) == HIGH) {
		// check channel A to see which way encoder is turning
		if (digitalRead(encoderRp1) == HIGH) {
			encoderRightCount = encoderRightCount + 1;         // CW
		} else {
			encoderRightCount = encoderRightCount - 1;         // CCW
		}
	}
	// Look for a high-to-low on channel B
	else {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoderRp1) == LOW) {
			encoderRightCount = encoderRightCount + 1;          // CW
		} else {
			encoderRightCount = encoderRightCount - 1;          // CCW
		}
	}
}

//This is the fuctions that takes care of the count of the encoders left

static void encoder::addCountL1() {

	// look for a low-to-high on channel A
	if (digitalRead(encoderLp1) == HIGH) {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoderLp2) == LOW) {
			encoderLeftCount = encoderLeftCount - 1;         // CW
		} else {
			encoderLeftCount = encoderLeftCount + 1;         // CCW
		}
	} else // must be a high-to-low edge on channel A
	{
		// check channel B to see which way encoder is turning
		if (digitalRead(encoderLp2) == HIGH) {
			encoderLeftCount = encoderLeftCount - 1;          // CW
		} else {
			encoderLeftCount = encoderLeftCount + 1;          // CCW
		}
	}
	// use for debugging - remember to comment out
}

static void encoder::addCountL2() {

	// look for a low-to-high on channel B
	if (digitalRead(encoderLp2) == HIGH) {
		// check channel A to see which way encoder is turning
		if (digitalRead(encoderLp1) == HIGH) {
			encoderLeftCount = encoderLeftCount - 1;         // CW
		} else {
			encoderLeftCount = encoderLeftCount + 1;         // CCW
		}
	}
	// Look for a high-to-low on channel B
	else {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoderLp1) == LOW) {
			encoderLeftCount = encoderLeftCount - 1;          // CW
		} else {
			encoderLeftCount = encoderLeftCount + 1;          // CCW
		}
	}
}

encoder::encoder(int encoderRp1, int encoderRp2, int encoderLp1,
		int encoderLp2) {

	pinMode(encoderRp1, INPUT);
	pinMode(encoderRp2, INPUT);
	pinMode(encoderLp1, INPUT);
	pinMode(encoderLp2, INPUT);

	enableInterrupt(encoderRp1, encoder::addCountR1, CHANGE);
	enableInterrupt(encoderRp2, encoder::addCountR2, CHANGE);
	enableInterrupt(encoderLp1, encoder::addCountL1, CHANGE);
	enableInterrupt(encoderLp2, encoder::addCountL2, CHANGE);
}
