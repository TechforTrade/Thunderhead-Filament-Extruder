/*
  Safety.cpp - Library for the safety functions of the
  filament extruder

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Safety.h"

Safety::Safety(Configuration* configuration)
{
  _enabled = true;
  _configuration = configuration;

 }

void Safety::check()
{
  _now = millis();
  //The following safety checks are always done when check() is called
  
  //Check barrel plastic overtemp
//   if (_barrel->getTemp()>_configuration->profile.maxTemp){
//     strcpy(_safetyMsg1, "The max Plastic Temp");
//     strcpy(_safetyMsg2, "has been exceeded.");
//     shutDown(_safetyMsg1, _safetyMsg2);
//   }
//   //Check for barrel overtemp
//   if (_barrel->getTemp()>_configuration->physical.maxTemp){
//     strcpy(_safetyMsg1, "The max barrel Temp");
//     strcpy(_safetyMsg2, "has been exceeded.");
//     shutDown(_safetyMsg1, _safetyMsg2);
//   }
//   //Check for nozzle plastic overtemp
//   if (_nozzle->getTemp()>_configuration->profile.maxTemp){
//     strcpy(_safetyMsg1, "The max plastic Temp");
//     strcpy(_safetyMsg2, "has been exceeded");
//     shutDown(_safetyMsg1, _safetyMsg2);
//   }
//   //Check for nozzle overtemp
//   if (_nozzle->getTemp()>_configuration->physical.maxTemp){
//     strcpy(_safetyMsg1, "The max nozzle temp");
//     strcpy(_safetyMsg2, "has been exceeded.");
//     shutDown(_safetyMsg1, _safetyMsg2);
//   }
//  




//  //The following safety checks are state dependent
//  switch( _stateMachine->getState()){
//  case StateMachine::PREHEAT:
//    //check for exceeding allowed preheat time
//    if (_now > _stateMachine->getPreheatStartTime()+_configuration->profile.maxPreheatTime*1000L*60L*60L){
//    strcpy(_safetyMsg1, "The preheat time has");
//    strcpy(_safetyMsg2, "been exceeded.");
//    shutDown(_safetyMsg1, _safetyMsg2);
//    }
//    break;
//    
//  case StateMachine::SOAK:
//    break;
//    
//  case StateMachine::BEGIN_EXTRUDE:
//    //Check to see that if the auger will be used the temp is high enough
//    if ((_configuration->profile.augerRPM>0) && (_nozzle->getTemp()<_configuration->profile.minExtrudeTemp)){
//    strcpy(_safetyMsg1, "Insufficient temp");
//    strcpy(_safetyMsg2, "for extrusion.");
//    shutDown(_safetyMsg1, _safetyMsg2);
//    }
//    break;
//    
//  case StateMachine::LOAD_FILAMENT:
//    //Check to make sure load filament time has not been exceeded.
//    if (_now >  _stateMachine->getLoadFilamentStartTime()+_configuration->physical.loadFilamentTime*1000*60*60){
//    strcpy(_safetyMsg1, "Load Filament Time");
//    strcpy(_safetyMsg2, "has been exceeded.");
//    shutDown(_safetyMsg1, _safetyMsg2);
//    }
//    break;    
//    
//  case StateMachine::EXTRUDE:// Automatic or manual
//    
//    //Check to see that the spool isn't filled
//    strcpy(_safetyMsg1, "The spool is full.");
//    strcpy(_safetyMsg2, "");
//    shutDown(_safetyMsg1, _safetyMsg2);
//    
//    //Check to see that the Diameter hasn't been at the minimum for too long
//    strcpy(_safetyMsg1, "Filament can't be");
//    strcpy(_safetyMsg2, "detected at outfeed.");
//    shutDown(_safetyMsg1, _safetyMsg2);
//    break;   
//    }    
  }

void Safety::shutDown(char* msg1, char* msg2){}

