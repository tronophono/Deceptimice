#ifndef encoder_h
#define encoder_h

class encoder{
	public:
		encoder::encoder(int encoderRp1,int encoderRp2,int encoderLp1,int encoderLp2);
		void addCountR1();
		void addCountR2();
		void addCountL1();
		void addCountL2();
};

#endif