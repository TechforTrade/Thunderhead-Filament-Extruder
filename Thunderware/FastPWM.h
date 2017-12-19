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
//    enum PinSet {
//      SET_3_14_8 = 0,// wired to auger motor, pins: step(PU-)->6, dir(DR-)->14, enable(MF-)->8 
//      SET_11_15_12,//wired to outfeed motor, pins: step->11, dir->15, enable->12
//      SET_10_16_9,//wired to spooler motor, pins: step->10, dir->16, enable->9
//      //STARVE_FEEDER,
//    };

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
