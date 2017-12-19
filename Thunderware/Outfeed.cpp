/*
Outfeed.cpp - Library for controlling the outfeed process.
It consists of a PID controller, DiameterSensor, and a
StepperMotor.

Created by Matthew P. Rogge, February 12, 2014.
Released into the public domain.
*/

#include "Arduino.h"
#include "Outfeed.h"

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

Outfeed::Outfeed(Configuration::DiaSensorRegMap_u* regMap)
{
	_regMap = regMap;
}


//revise so that the outfeed reports mm/s
float Outfeed::getRPM() {
	return _regMap->s.rpm;
}

double Outfeed::getDia() {
	return _regMap->s.diameter;
}

void Outfeed::setRPM(float rpm)
{
  _regMap->s.rpm = rpm;
  _writeRegister(RPM);
}

void Outfeed::disable()
{
  _regMap->s.rpm = 0.0;
  _writeRegister(RPM);
}

void Outfeed::changeSetpoint()
{
	_writeRegister(DIA_SETPOINT);
}

void Outfeed::setMode(int mode) {
	_regMap->s.mode = mode;
	_writeRegister(MODE);
}

int Outfeed::getMode() {
	return _regMap->s.mode;
}

void Outfeed::setTunings() {
	_writeRegister(KP);
	_writeRegister(KI);
	_writeRegister(KD);
}

double Outfeed::getKp() {
	return _regMap->s.kp;
}

void Outfeed::setKp(double kp) {
	_regMap->s.kp = kp;
	_writeRegister(KP);
}

double Outfeed::getKi() {
	return _regMap->s.ki;
}

void Outfeed::setKi(double ki) {
	_regMap->s.ki = ki;
_writeRegister(KI);}

double Outfeed::getKd() {
	return _regMap->s.kd;
}

void Outfeed::setKd(double kd) {
	_regMap->s.kd = kd;
	_writeRegister(KD);
}

void Outfeed::loadPIDSettings() {
	_writeRegister(KP);
	_writeRegister(KI);
	_writeRegister(KD);
	_writeRegister(OUTPUT_MIN);
	_writeRegister(OUTPUT_MAX);
	_writeRegister(SAMPLE_TIME);
}


float Outfeed::getMmExtruded()
{
	return _mmExtruded;
}

double Outfeed::getMPerMin()
{
	return getRPM() * 2.0 * PI * _configuration->physical.outfeedRollerRadius * 0.001;
}

double Outfeed::getFtPerMin()
{
	return getRPM() * 2.0 * PI * _configuration->physical.outfeedRollerRadius * 0.00328;
}

void Outfeed::reset()
{
	_mmExtruded = 0.0;
	_previousTime = millis();
}

//Idea: set update to call sample until a sample is ready. Reset sampleNum after the pid is computed
// put the mmExtruded into the compute time part. So then update can be called as rapidly as possible
void Outfeed::activate()
{
	//_now = millis();
	//
	//if (_now >= _computeTime) {
	//_mmExtruded += _configuration->physical.outfeedRollerRadius * _motor.getRPM() * 2.0 * PI / 60.0 * (_now - _previousTime) / 1000.0;
	//_caliper1.update();
	//_caliper2.update();
	//if (_pid.GetMode() == AUTOMATIC) {
	//_pid.Compute();
	//_motor.setRPM(_motor._rpm);
	//} else if (reduceSpeedFlag && _now >= reduceSpeedTime) {
	//reduceSpeedTime += 1000;
	//_motor.setRPM(_motor._rpm - (_configuration->profile.outfeedInitialRPM - _configuration->profile.outfeedRPM) / 60);
	//if (_motor._rpm <  61.0 / 60.0 * _configuration->profile.outfeedRPM) {
	//_motor.setRPM (_configuration->profile.outfeedRPM);
	//reduceSpeedFlag = false;
	//}
	//}
	//_computeTime = _now + (long) * _computeInterval;
	//}
	//_previousTime = _now;
}




void Outfeed::_writeRegister(byte address) {
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

void Outfeed::_readRegister(byte address) {
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

void Outfeed::readDiaAndRPM() {
    Wire.beginTransmission(slaveAddress); // transmit to slave
  Wire.write(DIAMETER);
  Wire.endTransmission();    // stop transmitting
  
	Wire.requestFrom(slaveAddress, 8);// request valueLength bytes from slave device #4
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
