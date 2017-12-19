/*
  Buzzer.cpp - Library for activating the buzzer which
      signals changes in the extruder's state and safety
      errors. The buzzer pin is 17

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Buzzer.h"

//Buzzer messages. The pattern is on, off, on, off ... in milliseconds
int Buzzer::_messages[7][10] = {{0,0,0,0,0,0,0,0,0,0},//NO_MSG
                                {500,500,500,500,0,0,0,0,0,0},//PREAHEAT_FINISHED
                                {2000,500,500,500,500,500,0,0,0,0},//SOAK_FINISHED
                                {50,100,50,1000,50,100,50,1000,0,0},//LOAD_FILAMENT_TIME_RUNNING_OUT
                                {100,500,100,500,100,500,0,0,0,0},//OUT_OF_TOL
                                {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000},//SAFETY
                                {50,100,50,100,0,0,0,0,0,0}//POWER_ON
                                };

Buzzer::Buzzer()
{
  pinMode(17, OUTPUT);
  _currentMsg = NO_MSG;
 }

void Buzzer::setMsg(Message msg)
{
  _currentMsg = msg;
}

void Buzzer::activate()
{
  //static int msgIndex = 0; //the index of the on or off durration of the current message

  if (_currentMsg != NO_MSG && _changeTime <= millis()){
    if (msgIndex%2 == 0){//The buzzer is entering an on state

      //If the end of the message has been reached, reset variables and return
      if (msgIndex>9){
        msgIndex = 0;
        _currentMsg = NO_MSG;
        return;
      }

      PORTH = PORTH | B00000001;//Turn the buzzer on
      _changeTime = millis() + _messages[_currentMsg][msgIndex];
      msgIndex++;

    } else { //The buzzer is entering an off State
      PORTH = PORTH & B11111110;//Turn the buzzer off
      _changeTime = millis() + _messages[_currentMsg][msgIndex];
      msgIndex++;
    }
  }
}

void Buzzer::reset(){
	msgIndex = 0;
	_currentMsg = NO_MSG;
}

