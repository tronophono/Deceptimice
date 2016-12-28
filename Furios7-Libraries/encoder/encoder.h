#include "Arduino.h"


#ifndef FURIOS7_LIBRARIES_encoder_h
#define FURIOS7_LIBRARIES_encoder_h


class encoder {
public:
	encoder(int encoderRp1, int encoderRp2, int encoderLp1, int encoderLp2);
	static void addCountR1();
	static void addCountR2();
	static void addCountL1();
	static void addCountL2();
};

#endif
