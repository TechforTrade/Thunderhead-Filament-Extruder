/*
  Heater.h - Library for activating the the  heaters.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef Heater_h
#define Heater_h

#include "Arduino.h"
#include "Thermistor.h"
#include "PID_v1.h"
#include "Configuration.h"

class Thermistor;
class PID;
class Configuration;

class Heater
{
public:

  Heater(Configuration::HeatingZone* zone);//constructor
  void activate();
  void setDutyCycle(float dutyCycle);
  double getDutyCycle(); 
  void sampleTemp();
  float getTemp();
  void off();
  void setMode(int mode);
  int getMode();

private:

  Thermistor       _thermistor;
  PID              _pid;
  int*             _timeBase;
  double           _dutyCycle;
  double*          _temp;
  int*			   _heaterPin;
  int*			   _coolerPin;
  boolean*		   _PWM;
  boolean*		   _activeCooling;
  double*		   _maxDutyCycle;
  double*		   _minDutyCycle;
  unsigned long	   _now;
  unsigned long   _durration;
  unsigned long   _startTime;
  boolean	      _boostNeeded;

};

#endif

