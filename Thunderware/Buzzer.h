/*
  Buzzer.h - Library for activating the buzzer which
      signals changes in the extruder's state and safety
      errors. The buzzer pin is 17

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer
{
  public:

    enum Message {
      NO_MSG = 0, // no message
      PREHEAT_FINISHED, // The soak period is starting
      SOAK_FINISHED, // The machine is extruding
      LOAD_FILAMENT_TIME_RUNNING_OUT, 
      OUT_OF_TOL, // The filament is out of tolerance
      SAFETY, // A safety shutdown has been triggered
      POWER_ON //Sound to alert that power has been turned on
    };

    Buzzer();//constructor
    void setMsg(Message msg);
    void activate();
	void reset(); //shut off any message that is currently sounding.

  private:
    unsigned long _now;
    unsigned long _changeTime; //the time to turn the buzzer on or off
	int msgIndex;
    Message _currentMsg;
    static int _messages[7][10];

};

#endif
