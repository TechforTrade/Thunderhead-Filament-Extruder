/*
  StepperMotor.cpp - Library for controlling the 3 stepper motors
  in the extruder. The motors are driven using a fast PWM signal
  (Timer1, Timer2 and Timer4). PWM is used because angular velocity
  is more important than angular position the PWM signal works well
  and frees up the processor for other jobs.

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "definitions.h"
#include "Arduino.h"
#include "StepperMotor.h"
//#include "config.h"
#include "Configuration.h"

class Configuration;

StepperMotor::StepperMotor(Configuration* configuration, int pinSet) : _timer(pinSet)
{
  _pinSet = pinSet;
  _configuration = configuration;
  //Set Direction, Step and Enable pins to output
  switch (_pinSet){
    case 0://SET_8_14_6
      _ratio = (float)_configuration->physical.augerStepMode*(float)_configuration->physical.augerGearRatio;
      
#ifdef OLD_PINS      
      DDRJ |= B00000010; //Direction, Pin 14 to output
#else
      pinMode(5, OUTPUT);//Direction pin
#endif

      DDRH |= B00001000; // Step pin 6 to output
      DDRH |= B00100000;//Enable pin 8 to output

      //set Auger Stepper direction (pin 14)
      if (_configuration->physical.augerDirection){
#ifdef OLD_PINS
        PORTJ |= B00000010;// Direction is forward so set the pin HIGH
#else
        digitalWrite(5, HIGH);
#endif
      }else{
#ifdef OLD_PINS
        PORTJ &= B11111101; // Direction is Backward so set the pin LOW
#else
        digitalWrite(5, LOW);
#endif
      }

      break;

    case 1://SET_11_15_12
      _ratio = configuration->physical.outfeedStepMode;

      DDRJ |= B00000001; //Direction, pin 15 to output
      DDRB |= B01000000; //Enable, pin 12 to output
      DDRB |= B00100000; //Step, pin 11 to output

      //set outfeed Stepper direction (pin 15)
      if (configuration->physical.outfeedDirection){
        PORTJ |= B00000001;// Direction is forward so set the pin HIGH
      }else{
        PORTJ &= B11111110; // Direction is backward so set the pin LOW
      }

      break;

    case 2://SET_10_16_9
        _ratio = configuration->physical.spoolerStepMode;

      DDRH |= B00000010; //Direction, pin 16 to output
      DDRH |= B01000000; //Enable, pin 9 to output
      DDRB |= B00010000;//Step, pin 10 to output

      //set spool Stepper direction pin (pin 16)
      if (configuration->physical.spoolerDirection){
        PORTH = PORTH | B00000010;// Direction is backward so set the pin HIGH
      }else{
        PORTH = PORTH & B11111101; // Direction is forward so set the pin LOW
      }

      break;

    case 3://SET_46_48_5
//      _ratio = configuration->physical.starveFeederStepMode;
//
//      DDRL |= B00001000; //Direction, pin 46 to output
//      DDRL |= B00000010; //Enable, pin 48 to output
//      DDRE |= B00001000;//Step, pin 5 to output

      //set Starve Feeder Stepper direction pin (pin 46)
//      if (configuration->physical.starveFeederDirection){
//        PORTL = PORTL | B00001000;// Direction is backward so set the pin HIGH
//      }else{
//        PORTL = PORTL & B11110111; // Direction is forward so set the pin LOW
//      }
      break;
    }
    disable(); // Make sure that the steppers begin disabled
 }

float StepperMotor::getFrequency(){

	return _timer.getFrequency();
}

void StepperMotor::setRPM(double RPM){
  _rpm = RPM;
  float freq = RPM/60.0*200.0*(float)_ratio;
 _timer.setFrequency(freq);
}

float StepperMotor::getRPM(){return _rpm;}


 //The following should be done before Setting the Spool RPM

   //Make sure the spoolRPM is updated
//   calcSpoolRPM();

void StepperMotor::enable() {

  switch (_pinSet){
    case 0://SET_6_7_8
      //Auger Stepper pin 8
      //disable is backwards for the KL stepper driver being used. Set LOW
      if (_configuration->physical.augerEnable){
      PORTH |= B00100000;
      }else{
      PORTH &= B11011111;
      }
      break;

    case 1://SET_11_15_12
      //Outfeed Stepper pin 12
      //disable outfeed stepper by setting the enable pin HIGH
      if (_configuration->physical.outfeedEnable){
      PORTB |= B01000000;
      }else{
      PORTB &= B10111111;
      }
      break;

    case 2://SET_10_16_9
       //Spool Stepper pin 9
       //disable Spool stepper by setting the enable pin HIGH
      if (_configuration->physical.spoolerEnable){
//          digitalWrite(9, HIGH);
        PORTH |= B01000000;
      }else{
//          digitalWrite(9, LOW);
        PORTH &= B10111111;
      }
      break;

    case 3://SET_46_48_5
       //StarveFeeder Stepper pin 48
       //enable StarveFeeder stepper by setting the enable pin HIGH
//      if (_configuration->physical.starveFeederEnable){
//       PORTL |= B00000010;
//      }else{
//       PORTL &= B11111101;
//      }
       break;
     }
}

void StepperMotor::disable() {
  switch (_pinSet){
    case 0://SET_6_7_8
      //Auger Stepper pin 3
      if (!_configuration->physical.augerEnable){
        PORTH |= B00100000;
      }else{
        PORTH &= B11011111;
      }

      break;

    case 1://SET_11_15_12
      //Outfeed Stepper pin 12
      //disable outfeed stepper by setting the enable pin Low
      if (!_configuration->physical.outfeedEnable){
      PORTB |= B01000000;
      }else{
      PORTB &= B10111111;
      }
      break;

    case 2://SET_10_16_9
       //Spool Stepper pin 9
       //disable Spool stepper by setting the enable pin low
      if (!_configuration->physical.spoolerEnable){
         PORTH |= B01000000;
      }else{
       PORTH &= B10111111;
      }
      break;

    case 3://SET_46_48_5
       //StarveFeeder Stepper pin 48
       //disable StarveFeeder stepper by setting the enable pin low
//      if (!_configuration->physical.starveFeederEnable){
//       PORTL |= B00000010;
//      }else{
//       PORTL &= B11111101;
//      }

      break;
  }
  setRPM(0.0);// turn the PWM to the pin off for safety
}


void StepperMotor::setDirection(){

	  switch (_pinSet){
		  case 0://SET_8_7_6
		  //set Auger Stepper direction (pin 14)
		  if (_configuration->physical.augerDirection){
#ifdef OLD_PINS
			  PORTJ |= B00000010;// Direction is forward so set the pin HIGH
#else
        digitalWrite(5, HIGH);
#endif
			  }else{
#ifdef OLD_PINS  
			  PORTJ &= B11111101; // Direction is Backward so set the pin LOW
#else
        digitalWrite(5, LOW);
#endif
		  }

		  break;

		  case 1://SET_11_15_12

		  //set outfeed Stepper direction (pin 15)
		  if (_configuration->physical.outfeedDirection){
			  PORTJ |= B00000001;// Direction is forward so set the pin HIGH
			  }else{
			  PORTJ &= B11111110; // Direction is backward so set the pin LOW
		  }

		  break;

		  case 2://SET_10_16_9

		  //set spool Stepper direction pin (pin 16)
		  if (_configuration->physical.spoolerDirection){
			  PORTH = PORTH | B00000010;// Direction is backward so set the pin HIGH
			  }else{
			  PORTH = PORTH & B11111101; // Direction is forward so set the pin LOW
		  }

		  break;

		  case 3://SET_46_48_5
		  //      _ratio = configuration->physical.starveFeederStepMode;
		  //
		  //      DDRL |= B00001000; //Direction, pin 46 to output
		  //      DDRL |= B00000010; //Enable, pin 48 to output
		  //      DDRE |= B00001000;//Step, pin 5 to output

		  //set Starve Feeder Stepper direction pin (pin 46)
		  //      if (configuration->physical.starveFeederDirection){
		  //        PORTL = PORTL | B00001000;// Direction is backward so set the pin HIGH
		  //      }else{
		  //        PORTL = PORTL & B11110111; // Direction is forward so set the pin LOW
		  //      }
		  break;
	  }

}
