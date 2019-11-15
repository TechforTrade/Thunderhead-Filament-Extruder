/*
QCDiaSensor.cpp - Library for controlling the QCDiaSensor process.
It consists of a PID controller, DiameterSensor, and a
StepperMotor.

Created by Matthew P. Rogge, February 12, 2014.
Released into the public domain.
*/

#include "definitions.h"
#include "Arduino.h"
#include "QCDiaSensor.h"

//Offsets of the register members
#define DIAMETER 0
#define RPM 4
#define DIA_SETPOINT 8
#define MODE 12
#define SAMPLE_TIME 13
#define KP 15
#define KI 19
#define KD 23
#define OUTPUT_MIN 27
#define OUTPUT_MAX 31
#define LASER_ON 35
#define VERSION 36

QCDiaSensor::QCDiaSensor(Configuration::DiaSensorRegMap_u* regMap)
{
	_regMap = regMap;
}


double QCDiaSensor::getDia() {
	return _regMap->s.diameter;
}

void QCDiaSensor::_writeRegister(byte address) {
	int valueLength;
	switch (address) {
		//    case DIAMETER:
		case RPM:
		case DIA_SETPOINT:
		case KP:
		case KI:
		case KD:
		case OUTPUT_MIN:
		case OUTPUT_MAX:
		valueLength = 4;
		break;
		case SAMPLE_TIME:
		valueLength = 2;
		break;
		case LASER_ON:
		case MODE:
		valueLength = 1;
		break;
		//    case VERSION:
		//      valueLength = 8;
		//      break;
	}

	Wire.beginTransmission(slaveAddress);
	Wire.write(address);
	byte* bytePtr = &_regMap->b[address];
	for (int i = 0; i < valueLength; i++) {
		Wire.write(*bytePtr);
		bytePtr++;
	}
	Wire.endTransmission();    // stop transmitting
}

void QCDiaSensor::_readRegister(byte address) {
	//get length of register
	int valueLength;
	switch (address) {
		case DIAMETER:
		case RPM:
		case DIA_SETPOINT:
		case KP:
		case KI:
		case KD:
		case OUTPUT_MIN:
		case OUTPUT_MAX:
		valueLength = 4;
		break;
		case SAMPLE_TIME:
		valueLength = 2;
		break;
		case LASER_ON:
		case MODE:
		valueLength = 1;
		case VERSION:
		valueLength = 8;
		break;
	}

	Wire.beginTransmission(slaveAddress); // transmit to slave
	Wire.write(address);
	Wire.endTransmission();    // stop transmitting

	Wire.requestFrom(slaveAddress, valueLength);// request valueLength bytes from slave device #4
	byte* bytePtr = &_regMap->b[address];
	while (Wire.available()) { // slave may send less than requested
		*bytePtr = Wire.read(); // receive a byte as character
		bytePtr++;
	}
}

void QCDiaSensor::readDia() {
		Wire.beginTransmission(slaveAddress); // transmit to slave
		Wire.write(DIAMETER);
		Wire.endTransmission();    // stop transmitting

	Wire.requestFrom(slaveAddress, 4);// request valueLength bytes from slave device #4
	byte* bytePtr = &_regMap->b[DIAMETER];
	while (Wire.available()) { // slave may send less than requested
		*bytePtr = Wire.read(); // receive a byte as character
		bytePtr++;
	}
}

//Offsets of the register members
#undef DIAMETER
#undef RPM
#undef DIA_SETPOINT
#undef MODE
#undef SAMPLE_TIME
#undef KP
#undef KI
#undef KD
#undef OUTPUT_MIN
#undef OUTPUT_MAX
#undef LASER_ON
#undef VERSION
