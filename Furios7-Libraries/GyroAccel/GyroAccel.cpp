/*
 * GyroAccel.cpp
 *
 *  Created on: Dec 21, 2016
 *      Author: lasantos
 */
/*
 * This library lets us read values from the MPU device that has both an accelerometer and a gyroscope integrated in one chip.
 * The code is a bit more complicated because it involves using the registers inside the MPU device, which involves some addresses.
 *
 * This code is from http://eeenthusiast.com/arduino-accelerometer-gyroscope-tutorial-mpu-6050/
 *
 * It is free to use, however if you want to learn more about programming devices like these you will need to reference
 * their respective data sheet.
 *
 * Device : MPU-6050
 * Data Sheet: https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
 *
 *
 * Since the code has been made already we will use it and tweak it to meet our specifications when needed.
 *
 */

#include "GyroAccel.h"
#include "Arduino.h"
#include <Wire.h>
//used for I2C (I squared C), a communication protocol like bluetooth.

//variables to store the values from the MPU.
long accelX = 0;
long accelY = 0;
long accelZ = 0;
long gyroX = 0;
long gyroY = 0;
long gyroZ = 0;
float gForceX = 0;
float gForceY = 0;
float gForceZ = 0;
float rotX = 0;
float rotY = 0;
float rotZ = 0;
float angle = 0;
float average = 0;

/*This constructor will set up the MPU device.
 *
 * ex:
 *
 * 		GyroAccel gyro; //this sets up the device automatically because the constructor is executed even without a parameter
 */
GyroAccel::GyroAccel(void) {
  Serial.print("Gyro Beginning");

}

void GyroAccel::setup(void) {
  Wire.beginTransmission(0b1101000);  //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B);  //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000);  //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);  //I2C address of the MPU
  Wire.write(0x1B);  //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000);  //Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);  //I2C address of the MPU
  Wire.write(0x1C);  //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00000000);  //Setting the accel to +/- 2g
  Wire.endTransmission();
}

//functions to read accelerometer values
void GyroAccel::recordAccelRegisters(void) {
  Wire.beginTransmission(0b1101000);  //I2C address of the MPU
  Wire.write(0x3B);  //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6);  //Request Accel Registers (3B - 40)
  while (Wire.available() < 6)
    ;
  accelX = Wire.read() << 8 | Wire.read();  //Store first two bytes into accelX
  accelY = Wire.read() << 8 | Wire.read();  //Store middle two bytes into accelY
  accelZ = Wire.read() << 8 | Wire.read();  //Store last two bytes into accelZ
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}

//read gyroscope's values
void GyroAccel::recordGyroRegisters(void) {
  Wire.beginTransmission(0b1101000);  //I2C address of the MPU
  Wire.write(0x43);  //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6);  //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6)
    ;
  gyroX = Wire.read() << 8 | Wire.read();  //Store first two bytes into accelX
  gyroY = Wire.read() << 8 | Wire.read();  //Store middle two bytes into accelY
  gyroZ = Wire.read() << 8 | Wire.read();  //Store last two bytes into accelZ

  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
  angle += rotZ / 16 + 0.038;
  for (int i = 0; i < 10; i++) {
    average += angle;
  }
  average /= 10;
}

//print the values of the gyroscope using Serial, which is used to communicate with our computer
void GyroAccel::printgyro(void) {
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

}

//print the values of the gyroscope.
void GyroAccel::printaccel(void) {
  Serial.print(" gForceX=");
  Serial.print(gForceX);
  Serial.print(" gForceY=");
  Serial.print(gForceY);
  Serial.print(" gForceZ=");
  Serial.println(gForceZ);

}
