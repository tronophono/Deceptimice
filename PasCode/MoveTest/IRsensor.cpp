#include "Arduino.h"

int frontDistance;
int rightDistance;
int leftDistance;

IRread(int irFront,int irRight, int irLeft){
	pinMode( irFront, INPUT );
    pinMode( irRight, INPUT );
    pinMode( irLeft, INPUT );
    
	  for(int i;i<1000; i++){

    	frontDistance += analogRead(irFront);
	  }
	  frontDistance /= 1000;

	  for(int i;i<1000; i++){

    	rightDistance += analogRead(irRight);
	  }
	  rightDistance /= 1000;

	  for(int i;i<1000; i++){

    	leftDistance += analogRead(irLeft);
	  }
	  leftDistance /= 1000;
}
