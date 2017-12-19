/*
Outfeed.h - Library for activating the the barrel heater.
The barrel heater is a 120 v 130 w heating element powered
by an electro-mechanical relay. The relay coil is optically
isolated from the logic circuits and is activated by pin 7.

Created by Matthew P. Rogge, February 12, 2014.
Released into the public domain.
*/
#ifndef QCDiaSensor_h
#define QCDiaSensor_h

#include "Arduino.h"
#include <Wire.h>
#include "Configuration.h"




class Configuration;


class QCDiaSensor
{
	public:
	QCDiaSensor(Configuration::DiaSensorRegMap_u* regMap);//constructor
	double getDia();
	void readDia();

	private:
	
	Configuration* _configuration;
	void _writeRegister(byte address);
	void _readRegister(byte address);
	const int slaveAddress = 5;
    Configuration::DiaSensorRegMap_u* _regMap;
	
};

#endif
