################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../HbridgeTest1.ino 

CPP_SRCS += \
../.ino.cpp \
../motors.cpp 

LINK_OBJ += \
./.ino.cpp.o \
./motors.cpp.o 

INO_DEPS += \
./HbridgeTest1.ino.d 

CPP_DEPS += \
./.ino.cpp.d \
./motors.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lasantos/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/lasantos/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/home/lasantos/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

HbridgeTest1.o: ../HbridgeTest1.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lasantos/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/lasantos/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/home/lasantos/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

motors.cpp.o: ../motors.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/lasantos/Downloads/sloeber/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR   -I"/home/lasantos/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/home/lasantos/Downloads/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


