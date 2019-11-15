/*
  StepperMotor.h - Library for controlling the 3 stepper motors
  in the extruder. The motors are driven using a fast PWM signal
  (Timer1, Timer2 and Timer4). PWM is used because angular velocity
  is more important than angular position the PWM signal works well
  and frees up the processor for other jobs.

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#ifndef StepperMotor_h
#define StepperMotor_h

#include "definitions.h"
#include "Arduino.h"
#include "FastPWM.h"
#include "Configuration.h"

class Configuration;

class StepperMotor
{
  public:
    int pinSet;
    StepperMotor(Configuration* configuration, int pinSet);//constructor
    void setRPM(double rpm);
    float getRPM();
    void disable();
    void enable();
	void setDirection();
	float getFrequency();
    double _rpm;
    float _ratio;//Stepmode And gear ratio (if it exists)

	
  private:
    FastPWM _timer;

    int _pinSet;
    Configuration* _configuration;
};

#endif
