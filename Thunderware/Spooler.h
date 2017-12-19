/*
Spooler.h - Library for controlling the spooling mechanism. A stepper
motor turns the spool. Its speed is determined by the geometry
of the spool, the distance from the center of the spool to the surface
of the filament and the rate at which filament is being extruded.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.
*/
#ifndef Spooler_h
#define Spooler_h

#include "Arduino.h"
#include "StepperMotor.h"
#include "Outfeed.h"
#include "PID_v1.h"

class StepperMotor;
class Outfeed;

class Spooler
{
	public:

	Spooler(Configuration* configuration);//constructor
	void setInitialRPM();
	void setRPM();
	void setMode(int mode);
	float  getRPM();
	void setRPM(float rpm);
	float getRawADC();
	void enable();
	void disable();
	void setDirection();
	void setTunings(double kp, double ki, double kd);
	Outfeed* _outfeed;
        int getMode();
        void on();
        void off();
	
	private:
	PID _pid;
	double _pidSetpoint;
	double _rawADCInput;
	int _wireAddress;
	union RawADC {byte _byte[4]; float _float;} _rawADC;
	double _motorRPM;
	float _diaSetPoint;
	float _filamentSurfaceRaduis;
	Configuration* _configuration;
	float c1;
	float c2;
	float c3;
	float c4;
	StepperMotor _motor;
	float _prevRPM;
	unsigned long _now;
	unsigned long _previousTime;
	unsigned long _interval;
        boolean _startFlag;


};

#endif
