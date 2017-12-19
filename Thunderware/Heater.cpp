/*
Heater.cpp - Library for controlling the heaters.
The heater library can control heaters using PWM (time base set to 0) or
by using a relay in which case the Time base is set to a larger value (maybe 2000).

Created by Matthew P. Rogge, Nov 24, 2015.
Released into the public domain.

*/

#include "Arduino.h"
#include "Heater.h"

Heater::Heater(Configuration::HeatingZone* zone)
: _thermistor(zone->thermistorPin, //This is the thermistor pin. Should this be set in physical configuration?
zone->thermistorRNom,
zone->thermistorTNom,
zone->thermistorNumSamples,
zone->thermistorBCoefficient,
zone->thermistorSeriesResistor),
_pid( &_thermistor.temp,
&_dutyCycle,
&zone->setTemp,
zone->Kp,
zone->Ki,
zone->Kd,
DIRECT)
{
	_timeBase = &zone->timeBase;
	_temp = &_thermistor.temp;
	_pid.SetSampleTime(*_timeBase);
	_pid.SetTunings(zone->Kp,
	zone->Ki,
	zone->Kd);

	_pid.SetOutputLimits(zone->minDutyCycle,
	zone->maxDutyCycle);
	_pid.SetMode(MANUAL);
	_dutyCycle = 0;
	_heaterPin = &zone->heaterPin;
	_activeCooling = &zone->activeCooling;
	if (_activeCooling){
		_coolerPin = &zone->coolerPin;
		pinMode(*_coolerPin, OUTPUT);
	}
	_heaterPin = &zone->heaterPin;
	pinMode(zone->heaterPin, OUTPUT);
	_PWM = &zone->PWM;
	_maxDutyCycle = &zone->maxDutyCycle;
	_minDutyCycle = &zone->minDutyCycle;
}



void Heater::activate()
{

	//Get the time
	_now = millis();
	_thermistor.sampleTemp();//Always sample temp so that the PID gets a good input

	//If one timebase has passed start over. Get the new PID setting and turn the relay on.
	if (_now >= (*_timeBase + _startTime)){
		_startTime = _now;
		_temp = &_thermistor.temp;
		_pid.Compute();

		if (!*_PWM){//IE, PWM isn't being used so use the time base as the duty cycle period.
			// Determine the length of time that the relay should be on

			_durration = ((*_timeBase*_dutyCycle)/100L);
						
			if (_dutyCycle>1.0){ // Only turn on if duty cycle is greater than 1
				digitalWrite(*_heaterPin , HIGH);//Turn the heater on.
			}
			
			} else {//Using PWM, so just set the PWM on the heater pin
			if(*_activeCooling){
				if (_dutyCycle >= 1){
					analogWrite(*_heaterPin, _dutyCycle);
					digitalWrite(*_coolerPin, LOW);
				} else if (_dutyCycle <= -1){
					if (_boostNeeded){
						analogWrite(*_coolerPin,50);
						_boostNeeded = false;
						delay(100);
					}
					analogWrite(*_heaterPin, 0);
					analogWrite(*_coolerPin, -_dutyCycle+10); //The extra 10 is because 10 is the minimum duty cycle that runs the fan.
				} else if (_dutyCycle < 1 && _dutyCycle > -1){
					analogWrite(*_heaterPin, 0);
					digitalWrite(*_coolerPin, LOW);
					_boostNeeded = true;
				}
			} else {
					analogWrite(*_heaterPin, _dutyCycle);

			}
		}
	}

	//If the relay should now be off, turn it off
	if (!*_PWM && digitalRead(*_heaterPin) &&_now >= _startTime + _durration){
		digitalWrite(*_heaterPin, LOW);//Turn the heater off
	}
}

// sampleTemp is used for states where the heater should be inactive.
void Heater::sampleTemp()
{
	_thermistor.sampleTemp();//Always sample temp so that the PID gets a good input
}

void Heater::setDutyCycle(float dutyCycle)
{
	if (_pid.GetMode() == AUTOMATIC){// if in Automatic switch to manual
		_pid.SetMode(MANUAL);
	}
	//Validate the duty cycle
	if (dutyCycle<*_minDutyCycle){dutyCycle = *_minDutyCycle;}
	if (dutyCycle>*_maxDutyCycle){dutyCycle = *_maxDutyCycle;}
	
	_dutyCycle = dutyCycle;
}

double Heater::getDutyCycle(){return _dutyCycle;}


void Heater::off()
{
	_pid.SetMode(MANUAL);
	_dutyCycle = 0.0;
	digitalWrite(*_heaterPin, LOW);//turn the relay off
	if (_activeCooling){
		digitalWrite(*_coolerPin, LOW);
	}
}

void Heater::setMode(int mode)
{
	_pid.SetMode(mode);
}


float Heater::getTemp(){return _thermistor.temp;}
