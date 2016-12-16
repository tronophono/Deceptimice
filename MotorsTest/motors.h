//This file is used to make program into multiple files
//The purpose of a header file is more than that but it basically connects the file that contains the function implementations and any other program that can use it.

#ifndef MOTORS_H_
#define MOTORS_H_

void ir_read(int ir1Pin);
void setupMPU();
void recordAccelRegisters();
void recordGyroRegisters();
void encoder_ReadRight(int encoder0PA, int encoder0PB);
void encoder_ReadLeft(int encoder1PA, int encoder1PB);
void doEncoderRightA();
void doEncoderRightB();
void doEncoderLeftA();
void doEncoderLeftB();
void motors_set(int motor1p1, int motor1p2, int motor2p1, int motor2p2,
		int enablep1, int enablep2);
void left_turn();
void right_turn();
void backward();
void forward();
void button_set(int left, int right, int back, int forw, int stps);
void stop_it();
void print();
void printr();
#endif /* MOTORS_H_ */
