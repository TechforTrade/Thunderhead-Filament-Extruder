/*
StarveFeeder.cpp - Library for controlling the the StarveFeeder.
The StarveFeeder's only electronic component is a stepper motor.
By modifying the speed of the stepper, the rate of pellet feed
into the hopper can be changed.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.
*/

#include "Arduino.h"
#include "StarveFeeder.h"

StarveFeeder::StarveFeeder(Configuration* configuration)
{
	_mainConfig = configuration;
	strcpy(_mode, "OFF");
}

void StarveFeeder::loadConfig()
{
	//create byte array and load it with config data

	//load _mainConfig data into _config struct
	_config.gramsPerMin = _mainConfig->profile.gramsPerMin;
	_config.lumpMass = _mainConfig->physical.starveFeederLumpMass;
	_config.minFillTime = _mainConfig->physical.starveFeederMinFillTime;
	_config.maxFillTime = _mainConfig->physical.starveFeederMaxFillTime;
	_config.startupTime = _mainConfig->physical.starveFeederStartupTime;
	_config.debounceTime = _mainConfig->physical.starveFeederDebounceTime;
	_config.homePosition = _mainConfig->physical.starveFeederHomePosition;
	_config.dumpPosition = _mainConfig->physical.starveFeederDumpPosition;
	_config.stepDelay = _mainConfig->physical.starveFeederStepDelay;
	_config.homingStepDelay = _mainConfig->physical.starveFeederHomingStepDelay;
	_config.overRotation = _mainConfig->physical.starveFeederOverRotation;
	_config.dir = _mainConfig->physical.starveFeederDirection;
	_config.vibDutyCycle = _mainConfig->physical.starveFeederVibDutyCycle;
	_config.maxDutyCycle = _mainConfig->physical.starveFeederMaxDutyCycle;
	_config.startupDutyCycle = _mainConfig->physical.starveFeederStartupDutyCycle;

	Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
	Wire.write((byte) StarveFeeder::LOAD_CONFIG);
	byte* bytePtr;
	bytePtr = (byte*)&_config;
	for (int i = 0; i < 31; i++) {
		Wire.write(*bytePtr);
		bytePtr++;
	}
	Wire.endTransmission();    // stop transmitting
}

void StarveFeeder::home() {
	Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
	Wire.write((byte) StarveFeeder::HOME);
	Wire.endTransmission();    // stop transmitting
}

void StarveFeeder::dump() {
	Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
	Wire.write((byte) StarveFeeder::DUMP_BUCKET);
	Wire.endTransmission();    // stop transmitting
}

void StarveFeeder::feed() {
	if (!_feeding){
		Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
		Wire.write((byte) StarveFeeder::FEED_PLASTIC);
		Wire.endTransmission();    // stop transmitting
		_feeding = true;

		} else {
		off();
		_feeding = false;
	}
}

void StarveFeeder::setGPM(double gpm)
{
	_config.gramsPerMin = gpm;
	_mainConfig->profile.gramsPerMin = gpm;
	Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
	Wire.write((byte) StarveFeeder::SET_GPM);
	byte* bytePtr;
	bytePtr = (byte*)&_config.gramsPerMin;
	for (int i = 0; i < 4; i++) {
		Wire.write(*bytePtr);
		bytePtr++;
	}
	Wire.endTransmission();    // stop transmitting

}

//The following is used for calibration
void StarveFeeder::setCycles(int cycles)
{
	strcpy(_mode, "ON");
	Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
	Wire.write((byte) StarveFeeder::SET_CYCLES);
	byte* bytePtr;
	bytePtr = (byte*)&cycles;
	for (int i = 0; i < 2; i++) {
		Wire.write(*bytePtr);
		bytePtr++;
	}
	Wire.endTransmission();    // stop transmitting

}

void StarveFeeder::setTime(unsigned long timeToRun)
{
	strcpy(_mode, "ON");
	Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
	Wire.write((byte) StarveFeeder::SET_TIME);
	byte* bytePtr;
	bytePtr = (byte*)&timeToRun;
	for (int i = 0; i < 2; i++) {
		Wire.write(*bytePtr);
		bytePtr++;
	}
	Wire.endTransmission();    // stop transmitting
}
void StarveFeeder::on() {
	loadConfig();// load configurations to make sure that any recent changes haven't been missed.
	strcpy(_mode, "ON");
	Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
	Wire.write((byte) StarveFeeder::ON);
	Wire.endTransmission();    // stop transmitting
}

void StarveFeeder::off() {
	//Call and response to make sure that the starve feeder actually got the message.

	boolean starveFeederState = true;
	while(starveFeederState){
		Wire.beginTransmission(_mainConfig->physical.starveFeederSlaveAddress); // transmit to slave
		Wire.write((byte) StarveFeeder::OFF);
		Wire.endTransmission();    // stop transmitting

		delay(50);

		Wire.requestFrom(_mainConfig->physical.starveFeederSlaveAddress, 1);    // request 6 bytes from slave device #2
		while(Wire.available()){
			starveFeederState = Wire.read(); // receive a byte
		}
	}
	strcpy(_mode, "OFF");
}

void StarveFeeder::getMode(char* strPtr) {
	strcpy(strPtr, _mode);
}

void StarveFeeder::changeMode() {
	//a little wonkey but it works
	//Check the seond letter in the mode to see if the starve feeder is on or off
	//then set it for the opposite.
	if (_mode[1] == 'F') {
		strcpy(_mode, "ON");
		on();
		} else {
		strcpy(_mode, "OFF");
		off();
	}
}
