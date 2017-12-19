/*
  Timer.cpp - Library for setting up timers 1, 2 and 4
  which are used for generating the step signal for the 
  steppers.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "FastPWM.h"


FastPWM::FastPWM(int pinSet)
{
 _pinSet = pinSet;
 switch (_pinSet){
   case 0://SET_6_14_8
     _timerNumber = 4;
     break;
   case 1://SET_11_15_12
     _timerNumber = 1;
     break;
   case 2://SET_10_16_9
     _timerNumber = 2;
     break;
   case 3://Set 46_48_5
     _timerNumber = 3;
 }
 
 }

//setFrequency(float frequency) sets the PWM to the designated frequency
//and activates it. 
void FastPWM::setFrequency(float frequency)
{
  //Store frequency in private variable
  _frequency = frequency;
  
  //Define Modes
  byte outModeA = 1; //Fast PWM toggles pin OC1A
  byte outModeB = 0 ;//Normal pin operation on OC1B
  byte captureMode = 0 ;//I think that this is used for interrupts

//For all timers 1,2 and 4 the functions should be setup to start and stop the PWM. 
//There should also be a setup That just gets fast PWM ready but doesn't set freq or turn on.
int prescaler;

  if (_timerNumber == 2){ //Timer 2 is an 8 bit timer so gets a different setup than the others
    byte mode = 7;//Fast PWM

    int prescalers[] = {1,8,32,64,128,256,1024};
    
      //Select Prescaler assumes using 16bit fast PWM
	
    for (int i=0; i<7;i++){
      if (16000000/(2*frequency* *(prescalers+i))< 255){
        prescaler = *(prescalers+i);
        break;
      }
    }
		
      
    byte clockMode = 0 ; // 0 means no clocking - the counter is frozen.
    switch (prescaler)
    {
      case 1: clockMode = 1 ; break ;
      case 8: clockMode = 2 ; break ;
      case 32: clockMode = 3 ; break ;
      case 64: clockMode = 4 ; break ;
      case 128: clockMode = 5 ; break ;
      case 256: clockMode = 6 ; break ;
      case 1024: clockMode = 7 ; break ;
    }
  
    TCCR2A = (outModeA << 6) | (outModeB << 4) | (mode & 3) ;
    TCCR2B = (captureMode << 6) | ((mode & B00000100) << 1) | clockMode;
    OCR2A = (byte)(16000000.0/(2*frequency * prescaler));//OCR2A because we are working with pin OC2As (pin 10)
    
  } else { //Timer 1, 3 or 4
  
  byte mode = 15 ;//Fast PWM

  int prescalers[] = {1,8,64,256,1024};
  
    //Select Prescaler assumes using 16bit fast PWM
  for (int i=0; i<5;i++){
    if (16000000/(2*frequency* *(prescalers+i))< 65535){
      prescaler = *(prescalers+i);
      break;
    }
  }
  
  byte clockMode = 0 ; // 0 means no clocking - the counter is frozen.
  switch (prescaler)
  {
    case 1: clockMode = 1 ; break ;
    case 8: clockMode = 2 ; break ;
    case 64: clockMode = 3 ; break ;
    case 256: clockMode = 4 ; break ;
    case 1024: clockMode = 5 ; break ;
    default:
      if (prescaler < 0)
        clockMode = 7 ; // external clock
  }
  
  switch(_timerNumber){
    case 1:
      TCCR1A = (outModeA << 6) | (outModeB << 4) | (mode & 3) ;
      TCCR1B = (captureMode << 6) | ((mode & 0xC) << 1) | clockMode ;
      OCR1A = (short)(16000000.0/(2*frequency * prescaler));//OCR1A because signal will be on pin OC1A (pin 11)
      break;
    
    case 3:
      TCCR3A = (outModeA << 6) | (outModeB << 4) | (mode & 3) ;
      TCCR3B = (captureMode << 6) | ((mode & 0xC) << 1) | clockMode ;
      OCR3A = (short)(16000000.0/(2*frequency * prescaler));//OCR3A because signal will be on pin 5 PE3
      break;

    case 4:
      //Notes
      //WGM40 and WGM41 are on TCCR4A bits 0 and 1 so mask other two: (mode & 3)
      //WGM41 and WGM42 are on TCCR4B bits 3 and 4 so mask the other two and shift to the left one: ((mode & 0xC) << 1)
      //the clockMode (prescaler setting) takes up the last 3 bits of TCCR4B
      //Capture mode is first 2 bits of TCCR4B so shift 6;
      //The format is the same for the other timers.
      TCCR4A = (outModeA << 6) | (outModeB << 4) | (mode & 3);
      TCCR4B = (captureMode << 6) | ((mode & 0xC) << 1) | clockMode;
      OCR4A = (short)(16000000.0/(2*frequency * prescaler));//OCR4A because signal will be on pin 6 PH3 
      break;
    }
  }
}

float FastPWM::getFrequency() 
{
  return _frequency;
}

void FastPWM::off()
{
  switch (_timerNumber){
    // for all timers, bits 6 and 7 designate the Compare Output Mode 
    // 00 designates normal operation with OCnA disconnected
    case 1: TCCR1A = TCCR1A & B00111111; break; 
    case 2: TCCR2A = TCCR2A & B00111111; break;
    case 3: TCCR3A = TCCR3A & B00111111; break;
    case 4: TCCR4A = TCCR4A & B00111111; break;
  } 
}
