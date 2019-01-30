/*
  Timer.h - Library for for setting up timers 1,2 and 4
  for fast PWM which are used for generating the step signal
  for the motors;
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef FastPWM_h
#define FastPWM_h

#include "Arduino.h"


class FastPWM
{
  public:
    FastPWM(int pinSet);
    void setFrequency(float frequency);
    float getFrequency();
    void off();// sets mode to normal.
    
  private:
    int _timerNumber;
    float _frequency;
    int _pinSet;
};

#endif
