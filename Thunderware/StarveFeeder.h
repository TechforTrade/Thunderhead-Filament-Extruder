/*
  StarveFeeder.h - Library for controlling the the StarveFeeder.
          The StarveFeeder's only electronic component is a stepper motor.
          By modifying the speed of the stepper, the rate of pellet feed
          into the hopper can be changed.

 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef StarveFeeder_h
#define StarveFeeder_h

#include "Arduino.h"
#include <Wire.h>
#include "Configuration.h"

class Configuration;

class StarveFeeder
{
  public:

    StarveFeeder(Configuration* configuration);
	void home();
	void dump();
	void feed();
    void setGPM(double gpm);
    void setCycles(int cycles);
    void setTime(unsigned long timeToRun);
    void loadConfig();
    void off();
    void on();
    void getMode(char* strPtr);
    void changeMode();
    boolean getState();

    char _mode[4];


    Configuration* _mainConfig;
    struct Config {
      float gramsPerMin;
      float lumpMass;
      int minFillTime;
      int maxFillTime;
      int startupTime;
      int debounceTime;
      int homePosition;
      int dumpPosition;
      int stepDelay;
      int homingStepDelay;
      int overRotation;
      boolean dir;
      int vibDutyCycle;
      int maxDutyCycle;
      int startupDutyCycle;
    } _config;
	boolean _feeding = false;

  private:

    enum Command {
      ON,
      OFF,
      HOME,
	  DUMP_BUCKET,
	  FEED_PLASTIC,
      SET_GPM,
      SET_CYCLES,
      LOAD_CONFIG,
	  SET_TIME
    };



};

#endif

