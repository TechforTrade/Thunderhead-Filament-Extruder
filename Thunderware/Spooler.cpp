/*
Spooler.cpp - Library for controlling the spooling mechanism. A stepper
motor turns the spool. Its speed is determined by the geometry
of the spool, the distance from the center of the spool to the surface
of the filament and the rate at which filament is being extruded.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.
*/

#include "Arduino.h"
#include <Wire.h>
#include "Spooler.h"

Spooler::Spooler(Configuration* configuration)
  :   _motor(configuration, configuration->physical.spoolerPinSet),
      _pid(&_rawADCInput,
           &_motorRPM,
           &_pidSetpoint,
           0.0005,
           0.0005,
           0.0,
           DIRECT)

{
  _wireAddress = 5;
  _interval = 500;
  _pidSetpoint = 512.0;
  _pid.SetSampleTime(_interval);
  _pid.SetMode(MANUAL);
  _pid.SetOutputLimits(0, 350);

}

void Spooler::setInitialRPM() { //This needs to be reworked
  c1 = (_configuration->physical.outfeedRollerRadius
        * _configuration->physical.spoolerDiskRadius
        * _configuration->physical.spoolerStepMode
        / (_configuration->physical.spoolerMotorRollerRadius
           * _configuration->physical.outfeedStepMode));
  c2 = (_configuration->profile.diaSetpoint / (PI * _configuration->physical.spoolerTraverseLength));
  c3 = (_configuration->physical.spoolerCoreRadius * _configuration->physical.spoolerCoreRadius);
  c4 = (PI * _configuration->physical.outfeedRollerRadius / ((double)_configuration->physical.outfeedStepMode * 100.0));

  _filamentSurfaceRaduis = pow(c2 * c2 * _outfeed->getMmExtruded() + c3, 0.5);
  _motorRPM = _configuration->physical.outfeedRollerRadius
              * _configuration->physical.spoolerDiskRadius
              / (_filamentSurfaceRaduis * _configuration->physical.spoolerMotorRollerRadius)
              * _outfeed->getRPM();

  setMode(MANUAL);
  setRPM(120);
  setMode(AUTOMATIC);

}

void Spooler::setRPM() // Call every 1000ms to update the speed of the spooler based on the PID output
{
  if (_startFlag && _rawADCInput >60){//Stick with aggressive tunings until there is tension on the filament.
    _pid.SetTunings(0.01,0.01,0.0);//Switch to lighter tunings now that there is tension on the filament.
    _startFlag = false;
//    Serial.println("Lowering Tunings");
  }
    
  _now = millis();
  if (_now >= _previousTime) {
    Wire.requestFrom(_wireAddress, 4);
    int i = 0;
    while (Wire.available()) {
      _rawADC._byte[i] = Wire.read();
      i++;
    }
    Wire.endTransmission();
    _rawADCInput = _rawADC._float;
    _pid.Compute();
    _motor.setRPM(_motorRPM);
    _previousTime = _now + _interval;
  }
}

void Spooler::setMode(int mode) {
  _pid.SetMode(mode);
}

float Spooler::getRPM() {
  return _motor.getRPM();
}

float Spooler::getRawADC() {
  Wire.requestFrom(_wireAddress, 4);
  int i = 0;
  while (Wire.available()) {
    _rawADC._byte[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  _rawADCInput = _rawADC._float;
  return _rawADCInput;
}



void Spooler::setRPM(float rpm)
{
  _motor.setRPM(rpm);
  _motorRPM = rpm;
}

//Instead of using the following, should I have a public pointer to _motor and then use someting like spooler.motor->enable()?
void Spooler::enable() {
  _motor.enable();
}
void Spooler::disable() {
  _motor.disable();
}

void Spooler::setDirection() {
  _motor.setDirection();
}

void Spooler::setTunings(double kp, double ki, double kd) {
  _pid.SetTunings(kp, ki, kd);
}

int Spooler::getMode() {
  return _pid.GetMode();
}

void Spooler::on() {
  setTunings(0.5, 0.01, 0.0);
  setMode(MANUAL);
  setRPM(120);
  setMode(AUTOMATIC);
  enable();
  _startFlag = true;
}

void Spooler::off() {
  setMode(MANUAL);
  setRPM(0);
  _startFlag = false;
}

