#ifndef Motors_h
#define Motors_h
//#include "EnableInterrupt.h"
#include "Arduino.h"
class Motors{
	public:
		Motors(int motor1p1, int motor1p2,int motor2p1,int motor2p2,int enablep1,int enablep2);
		boolean motorsState=false;
		void right_turn();
		void left_turn();
		void forward();
		void backward();
		void stop_it();
};

#endif
