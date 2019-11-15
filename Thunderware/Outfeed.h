/*
  Outfeed.cpp - Library for controlling the outfeed process.
  It consists of a PID controller, DiameterSensor, and a
  StepperMotor.

  Created by Matthew P. Rogge, February 12, 2014.
  Released into the public domain.
*/
#ifndef Outfeed_h
#define Outfeed_h

#include "definitions.h"
#include "Arduino.h"
#include <Wire.h>
#include "Configuration.h"
#include "StepperMotor.h"
#include "PID_v1.h"




class Configuration;

#ifdef MAC_OUTFEED
class StepperMotor;
class PID;
#endif


class Outfeed
{
  public:

    Outfeed(Configuration* configuration);//constructor
//    Outfeed(Configuration::DiaSensorRegMap_u* regMap);//constructor
    float getRPM();
    void setRPM(float rpm);
    void setMode(int mode);
    int getMode();
    void setTunings();
    void changeSetpoint();
    double getKp();
    void setKp(double kp);
    double getKi();
    void setKi(double ki);
    double getKd();
    void setKd(double kd);
    void loadPIDSettings();
    void reset();
    float getMmExtruded();
    double getMPerMin();
    double getFtPerMin();
    double getDia();
    void activate();
    void readDiaAndRPM();
    void disable();

  private:

    Configuration* _configuration;
#ifdef MAC_OUTFEED
    StepperMotor   _motor;
    PID            _pid;
    unsigned long _computeTime;
    unsigned long _computeInterval;

#endif
    void _writeRegister(byte address);
    void _readRegister(byte address);
    float _mmExtruded;
    unsigned long _now;
    unsigned long _previousTime;
    const int slaveAddress = 4;
    Configuration::DiaSensorRegMap_u* _regMap;

};

#endif
