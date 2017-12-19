#ifndef Preheat_h
#define Preheat_h

#include "Safety.h"
#include "TestReporting.h"

static unsigned long preheatStartTime;

void beginPreheat() {
  configuration.physical.zone1.setTemp = configuration.profile.zone1InitialSetTemp;
  configuration.physical.zone2.setTemp = configuration.profile.zone2InitialSetTemp;
  configuration.physical.zone3.setTemp = configuration.profile.zone3InitialSetTemp;
  configuration.physical.zone4.setTemp = configuration.profile.zone4InitialSetTemp;
  configuration.physical.zone5.setTemp = configuration.profile.zone5InitialSetTemp;
  
 
//  setZone1Temp();
//  setZone2Temp();
//  setZone3Temp();
//  setZone4Temp();
//  setZone5Temp();

  preheatStartTime = millis();
  //start from full power state
  zone1.setDutyCycle(90);
  zone2.setDutyCycle(90);
  zone3.setDutyCycle(255);
  zone4.setDutyCycle(255);
  zone5.setDutyCycle(255);

  //Then set heater PIDs to automatic
  zone1.setMode(AUTOMATIC);
  zone2.setMode(AUTOMATIC);
  zone3.setMode(AUTOMATIC);
  zone4.setMode(AUTOMATIC);
  zone5.setMode(AUTOMATIC);

  currentState = PREHEAT;
}

void preheat() {

  buzzer.activate();
  zone1.activate();
  zone2.activate();
  zone3.activate();
  zone4.activate();
  zone5.activate();

  if (zone1.getTemp() > configuration.profile.zone1InitialSetTemp - 3 &&
      zone2.getTemp() > configuration.profile.zone2InitialSetTemp - 3 &&
      zone3.getTemp() > configuration.profile.zone3InitialSetTemp - 3 &&
      zone4.getTemp() > configuration.profile.zone4InitialSetTemp - 3 &&
      zone5.getTemp() > configuration.profile.zone5InitialSetTemp - 3) {
    buzzer.setMsg(Buzzer::PREHEAT_FINISHED);
    currentState = BEGIN_SOAK;
    activeMenu = &soakMenu;
    activeMenu->reset();
    activeMenu->display();
  }

}



static unsigned long soakStartTime;
static unsigned long soakEndTime;

void beginSoak() {
//  Serial.println("Begin Soak");
  soakStartTime = millis();
  soakEndTime = soakStartTime + configuration.profile.soakTime * 60L * 1000L;
  currentState = SOAK;
}



//Soak state function
void soak() {
  static unsigned long now;
  static boolean msgSet = false;//indicates that the end soak buzzer message has been set

  now = millis();

  buzzer.activate();
  zone1.activate();
  zone2.activate();
  zone3.activate();
  zone4.activate();
  zone5.activate();

  //  safety.check();

  if (now >= soakEndTime - 5000 && !msgSet) {
    buzzer.setMsg(Buzzer::SOAK_FINISHED);
    msgSet = true;
  }

  if (now >= soakEndTime) {
    msgSet = false;//reset msgSet flag
//    Serial.println("");
//    Serial.println(F("Finished Soaking"));
//    Serial.println("");
    currentState = BEGIN_EXTRUDE;//Changed from begin load filament for testing purposes
    activeMenu = &extrudeMenu;

    activeMenu->reset();
    activeMenu->display();
  }
}




#endif // Preheat_h

