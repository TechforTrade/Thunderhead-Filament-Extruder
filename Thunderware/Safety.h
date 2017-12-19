/*
  Safety.h - Library for the safety functions of the
  filament extruder.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef Safety_h
#define Safety_h

#include "Arduino.h"
#include "Configuration.h"

class Configuration;


class Safety
{
public:

  Safety(Configuration* configuration);//constructor
  void check();
  void enable();
  void disable(); 
  void shutDown(char* msg1, char* msg2);

private:

  Configuration*  _configuration;
  boolean         _enabled;
  char        _safetyMsg1[21];
  char        _safetyMsg2[21];
  unsigned long   _now;
};

#endif

//
//
//#ifndef Safety_h
//#define Safety_h
//
//char safetyMsg[20];
//
//boolean heaterError(){
//  if (barrel.getTemp() > maxExtruderTemp){
//    barrel.off();
//    nozzle.off();
//    auger.disable();
//    outfeed.disable();
//    spooler.disable();
//    strcpy(safetyMsg, "Barrel over temp.");
//    Serial.println(barrel.getTemp());
//    currentState = SAFETY_SHUTDOWN;
//    return true;
//  }
//  return false;
//}
//
//void safetyShutdown(){
//  lcd.clear();
//  lcd.write("Safety Shutdown");
//  Serial.println("Safety Shutdown");
//  lcd.setCursor(0,1);
//  lcd.write(safetyMsg);
//  lcd.setCursor(0,3);
//  lcd.write("Press any key exit");
//  Serial.println("Press any key to exit.");
//  //        safetyErrorSound();
//  while(1){
//    kpd.getKey();
//
//    if (Serial.available() > 0) {
//      key = (char)Serial.read();
//    }
//
//    if (key){ 
//      break;
//    }
//  }
//  currentState = SELECT_PROFILE;
//
//}
//#endif // Safety_h

