//Maintain this file using an excel spread sheet so that it is easier to keep all of the linkages correct.

#ifndef MenuData_h
#define MenuData_h



//MenuItem Text strings
const char rootStr[] PROGMEM = "Main Menu";
const char selectProfileStr[] PROGMEM = "Select Profile";
const char calibrateStr[] PROGMEM = "Calibrate";
const char auxiliaryStr[] PROGMEM = "Auxiliary";
const char profile0Str[] PROGMEM = "1)";
const char profile1Str[] PROGMEM = "2)";
const char profile2Str[] PROGMEM = "3)";
const char profile3Str[] PROGMEM = "4)";
const char profile4Str[] PROGMEM = "5)";
const char profile5Str[] PROGMEM = "6)";
const char profile6Str[] PROGMEM = "7)";
const char profile7Str[] PROGMEM = "8)";
const char profile8Str[] PROGMEM = "9)";
const char profile9Str[] PROGMEM = "10)";
const char defaultProfileStr[] PROGMEM = "Default Profile";
const char extrudeStr[] PROGMEM = "Extrude";
const char saveProfileStr[] PROGMEM = "Save Profile";
const char profileNameStr[] PROGMEM = "Name";
const char diaSetpointStr[] PROGMEM = "Dia Setpoint";
const char densityStr[] PROGMEM = "Density";
const char toleranceStr[] PROGMEM = "Tolerance";
const char gramsPerMinStr[] PROGMEM = "Grams/Min";
const char augerRPMStr[] PROGMEM = "Auger RPM";
const char outfeedRPMStr[] PROGMEM = "Outfeed RPM";
const char soakTimeStr[] PROGMEM = "Soak Time";
const char zone1InitialSetTempStr[] PROGMEM = "Z1 Init Temp";
const char zone2InitialSetTempStr[] PROGMEM = "Z2 Init Temp";
const char zone3InitialSetTempStr[] PROGMEM = "Z3 Init Temp";
const char zone4InitialSetTempStr[] PROGMEM = "Z4 Init Temp";
const char zone5InitialSetTempStr[] PROGMEM = "Z5 Init Temp";
const char zone1SetTempStr[] PROGMEM = "Zone 1 Set Temp";
const char zone2SetTempStr[] PROGMEM = "Zone 2 Set Temp";
const char zone3SetTempStr[] PROGMEM = "Zone 3 Set Temp";
const char zone4SetTempStr[] PROGMEM = "Zone 4 Set Temp";
const char zone5SetTempStr[] PROGMEM = "Zone 5 Set Temp";
const char saveConfigStr[] PROGMEM = "Save Configuration";
const char starveFeederConfigStr[] PROGMEM = "StarveFeeder";
const char augerConfigStr[] PROGMEM = "Auger";
const char heaterConfigStr[] PROGMEM = "Heater Config";
const char outfeedConfigStr[] PROGMEM = "Outfeed";
const char spoolerConfigStr[] PROGMEM = "Spooler";
const char homeStarveFeederStr[] PROGMEM = "Home";
const char dumpStr[] PROGMEM = "Dump";
const char feedStr[] PROGMEM = "Feed Plastic";
const char sendCyclesStr[] PROGMEM = "Send Cycles";
const char cyclesToSendToStarveFeederStr[] PROGMEM = "Cycles to send";
const char sendTimeStr[] PROGMEM = "Send Time";
const char timeToSendToStarveFeederStr[] PROGMEM = "Time to send";
const char stopStr[] PROGMEM = "Stop";
const char starveFeederSlaveAddressStr[] PROGMEM = "Slave Address";
const char starveFeederLumpMassStr[] PROGMEM = "Lump Mass";
const char starveFeederHomePositionStr[] PROGMEM = "Home Position";
const char starveFeederDumpPositionStr[] PROGMEM = "Dump Position";
const char starveFeederStepDelayStr[] PROGMEM = "Step Delay";
const char starveFeederHomingStepDelayStr[] PROGMEM = "Homing Delay";
const char starveFeederOverRotationStr[] PROGMEM = "Over Rotation";
const char starveFeederDirectionStr[] PROGMEM = "Direction";
const char starveFeederVibDutyCycleStr[] PROGMEM = "DutyCycle";
const char starveFeederStartupDutyCycleStr[] PROGMEM = "Startup DutyCycle";
const char starveFeederMaxDutyCycleStr[] PROGMEM = "MaxDutyCycle";
const char starveFeederMinFillTimeStr[] PROGMEM = "MinFillTime";
const char starveFeederMaxFillTimeStr[] PROGMEM = "MaxFillTime";
const char starveFeederStartupTimeStr[] PROGMEM = "Startup Time";
const char starveFeederDebounceTimeStr[] PROGMEM = "Debounce Time";
const char testAugerStr[] PROGMEM = "Test Auger";
const char augerPinSetStr[] PROGMEM = "Pin Set";
const char augerStepModeStr[] PROGMEM = "Step Mode";
const char augerDirectionStr[] PROGMEM = "Direction";
const char augerEnableStr[] PROGMEM = "Enable";
const char augerGearRatioStr[] PROGMEM = "Gear Ratio";
const char heaterStateStr[] PROGMEM = "Activate Heaters";
const char zone1TempStr[] PROGMEM = "Zone 1 Temp";
const char zone2TempStr[] PROGMEM = "Zone 2 Temp";
const char zone3TempStr[] PROGMEM = "Zone 3 Temp";
const char zone4TempStr[] PROGMEM = "Zone 4 Temp";
const char zone5TempStr[] PROGMEM = "Zone 5 Temp";
const char zone1TimeBaseStr[] PROGMEM = "Z1 Time base";
const char zone1MaxDutyCycleStr[] PROGMEM = "Z1 Max DC";
const char zone1MinDutyCycleStr[] PROGMEM = "Z1 Min DC";
const char zone1KpStr[] PROGMEM = "Z1 Kp";
const char zone1KiStr[] PROGMEM = "Z1 Ki";
const char zone1KdStr[] PROGMEM = "Z1 Kd";
const char zone2TimeBaseStr[] PROGMEM = "Z2 Time base";
const char zone2MaxDutyCycleStr[] PROGMEM = "Z2 Max DC";
const char zone2MinDutyCycleStr[] PROGMEM = "Z2 Min DC";
const char zone2KpStr[] PROGMEM = "Z2 Kp";
const char zone2KiStr[] PROGMEM = "Z2 Ki";
const char zone2KdStr[] PROGMEM = "Z2 Kd";
const char zone3MaxDutyCycleStr[] PROGMEM = "Z3 Max DC";
const char zone3MinDutyCycleStr[] PROGMEM = "Z3 Min DC";
const char zone3KpStr[] PROGMEM = "Z3 Kp";
const char zone3KiStr[] PROGMEM = "Z3 Ki";
const char zone3KdStr[] PROGMEM = "Z3 Kd";
const char zone4MaxDutyCycleStr[] PROGMEM = "Z4 Max DC";
const char zone4MinDutyCycleStr[] PROGMEM = "Z4 Min DC";
const char zone4KpStr[] PROGMEM = "Z4 Kp";
const char zone4KiStr[] PROGMEM = "Z4 Ki";
const char zone4KdStr[] PROGMEM = "Z4 Kd";
const char zone5MaxDutyCycleStr[] PROGMEM = "Z5 Max DC";
const char zone5MinDutyCycleStr[] PROGMEM = "Z5 Min DC";
const char zone5KpStr[] PROGMEM = "Z5 Kp";
const char zone5KiStr[] PROGMEM = "Z5 Ki";
const char zone5KdStr[] PROGMEM = "Z5 Kd";
const char RPMStr[] PROGMEM = "RPM";
const char testSpoolerStr[] PROGMEM = "Test Spooler";
const char spoolerPinSetStr[] PROGMEM = "Pin Set";
const char spoolerStepModeStr[] PROGMEM = "Step Mode";
const char spoolerDirectionStr[] PROGMEM = "Direction";
const char spoolerEnableStr[] PROGMEM = "Enable";
const char spoolerDiskRadiusStr[] PROGMEM = "Disk Radius";
const char spoolerCoreRadiusStr[] PROGMEM = "Core Radius";
const char spoolerTraverseLengthStr[] PROGMEM = "Traverse Len";
const char spoolerMotorRollerRadiusStr[] PROGMEM = "Roller Radius";
const char measureFilametStr[] PROGMEM = "Measure Filament";
const char resetEEPROMStr[] PROGMEM = "Reset EEPROM";

const char preheatRootStr[] PROGMEM = "Preheating. . .";
const char skipPreheatStr[] PROGMEM = "Skip Preheat";
const char soakRootStr[] PROGMEM = "Soaking. . .";
const char soakTimeRemainingStr[] PROGMEM = "Time Remaining";
const char increaseSoakTimeStr[] PROGMEM = "Increase Soak Time";
const char decreaseSoakTimeStr[] PROGMEM = "Decrease Soak Time";
const char skipSoakStr[] PROGMEM = "Skip Soak";
const char loadFilamentRootStr[] PROGMEM = "Load Filament. . .";
const char loadFilamentRemainingTimeStr[] PROGMEM = "Time Remaining";
const char filamentLoadedStr[] PROGMEM = "Filament Loaded";
const char loadFilamentAddTimeStr[] PROGMEM = "Add Time";
const char starveFeederModeStr[] PROGMEM = "Starve Feeder";
const char extrudeRootStr[] PROGMEM = "Extruding. . .";
const char setExtrudeTempsStr[] PROGMEM = "Set Extude Temps";
const char outfeedModeStr[] PROGMEM = "OF Mode";
const char outfeedKpStr[] PROGMEM = "OF Kp";
const char outfeedKiStr[] PROGMEM = "OF Ki";
const char outfeedKdStr[] PROGMEM = "OF Kd";
const char outfeedMinRPMStr[] PROGMEM = "OF Min RPM";
const char outfeedMaxRPMStr[] PROGMEM = "OF Max RPM";
const char outfeedSampleTimeStr[] PROGMEM = "OF Sample Time";
const char filamentDiameterStr[] PROGMEM = "Ini Dia";
const char filamentDiameterFinalStr[] PROGMEM = "Final Dia";

//Variables for holding Menu values
double zone1Temp;
double zone2Temp;
double zone3Temp;
double zone4Temp;
double zone5Temp;
char heaterState[] = "Off";
char outfeedState[] = "Off";
char outfeedMode[] = "MAN";
char outfeedReduceSpeed[] = "Off";
float outfeedRPM =  0.0;
char spoolerState[] = "Off";
char loadFilamentTimeRemaining[6];
char starveFeederMode[] = "Off";
char soakTimeRemaining[6];
int gramsExtruded;
float diameter = 1.75;
int cyclesToSendToStarveFeeder = 10;
int timeToSendToStarveFeeder = 4;
char feedMode[4] = "Off";//starve feeder feeding plastic or not
unsigned long extrudeStartTime;

//Menu Action methods
void activateHeaters();
void testAuger();
void testOutfeed();
void testSpooler();
void toggleHeaterState();
void toggleOutfeedState();
void changeOutfeedMode();
void changeOutfeedSetpoint();
void toggleSpoolerState();
void setZone1Temp();
void setZone2Temp();
void setZone3Temp();
void setZone4Temp();
void setZone5Temp();
/*void homeStarveFeederStr();*/
void sendTimeToStarveFeeder();
void sendCyclesToStarveFeeder();
void stopStarveFeeder();
void loadStarveFeederConfig();
//void sendOneRevToOutfeed();
void measureFilament();
//void calibrateCalipers();
//void reduceOutfeedSpeed();

//forward declarations (didn't seem to be needed before)
void loadProfile0();
void loadProfile1();
void loadProfile2();
void loadProfile3();
void loadProfile4();
void loadProfile5();
void loadProfile6();
void loadProfile7();
void loadProfile8();
void loadProfile9();
void loadDefaultProfile();
void actionExtrude();
void saveCurrentProfile();
void saveConfig();
void homeStarveFeeder();
void dump();
void feed();
void resetEEPROM();
void exitPreheat();
void skipPreheat();
void exitSoak();
void increaseSoakTime();
void decreaseSoakTime();
void skipSoak();
void exitLoadFilament();
void filamentLoaded();
void loadFilamentAddTime();
void starveFeederChangeMode();
void setGramsPerMin();
void setTempsToExtrudeVals();
void setAugerRPM();
void setOutfeedRPM();
void setOutfeedTunings();
void exitExtrude();

const Menu::MenuItem mainItems[] PROGMEM =
{
{rootStr, -1, 1, NULL, 0, Menu::TITLE, NULL},
{selectProfileStr, 0, 4, NULL, 0, Menu::TITLE, NULL},
{calibrateStr, 0, 35, NULL, 0, Menu::TITLE, NULL},
{auxiliaryStr, 0, 119, NULL, 0, Menu::TITLE, NULL},
{profile0Str, 1, 15, &configuration.profileNames[0], 0, Menu::TITLE_STRING, &loadProfile0},
{profile1Str, 1, 15, &configuration.profileNames[1], 0, Menu::TITLE_STRING, &loadProfile1},
{profile2Str, 1, 15, &configuration.profileNames[2], 0, Menu::TITLE_STRING, &loadProfile2},
{profile3Str, 1, 15, &configuration.profileNames[3], 0, Menu::TITLE_STRING, &loadProfile3},
{profile4Str, 1, 15, &configuration.profileNames[4], 0, Menu::TITLE_STRING, &loadProfile4},
{profile5Str, 1, 15, &configuration.profileNames[5], 0, Menu::TITLE_STRING, &loadProfile5},
{profile6Str, 1, 15, &configuration.profileNames[6], 0, Menu::TITLE_STRING, &loadProfile6},
{profile7Str, 1, 15, &configuration.profileNames[7], 0, Menu::TITLE_STRING, &loadProfile7},
{profile8Str, 1, 15, &configuration.profileNames[8], 0, Menu::TITLE_STRING, &loadProfile8},
{profile9Str, 1, 15, &configuration.profileNames[9], 0, Menu::TITLE_STRING, &loadProfile9},
{defaultProfileStr, 1, 15, NULL, 0, Menu::TITLE, &loadDefaultProfile},
{extrudeStr, 4, -1, NULL, 0, Menu::TITLE, &actionExtrude},
{saveProfileStr, 4, -1, NULL, 0, Menu::TITLE, &saveCurrentProfile},
{profileNameStr, 4, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetpointStr, 4, -1, &configuration.profile.diaSetpoint, 2, Menu::DOUBLE, NULL},
{densityStr, 4, -1, &configuration.profile.density, 2, Menu::DOUBLE, NULL},
{toleranceStr, 4, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMinStr, 4, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
{augerRPMStr, 4, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPMStr, 4, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{soakTimeStr, 4, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
{zone1InitialSetTempStr, 4, -1, &configuration.profile.zone1InitialSetTemp, 0, Menu::DOUBLE, NULL},
{zone2InitialSetTempStr, 4, -1, &configuration.profile.zone2InitialSetTemp, 0, Menu::DOUBLE, NULL},
{zone3InitialSetTempStr, 4, -1, &configuration.profile.zone3InitialSetTemp, 0, Menu::DOUBLE, NULL},
{zone4InitialSetTempStr, 4, -1, &configuration.profile.zone4InitialSetTemp, 0, Menu::DOUBLE, NULL},
{zone5InitialSetTempStr, 4, -1, &configuration.profile.zone5InitialSetTemp, 0, Menu::DOUBLE, NULL},
{zone1SetTempStr, 4, -1, &configuration.profile.zone1SetTemp, 0, Menu::DOUBLE, NULL},
{zone2SetTempStr, 4, -1, &configuration.profile.zone2SetTemp, 0, Menu::DOUBLE, NULL},
{zone3SetTempStr, 4, -1, &configuration.profile.zone3SetTemp, 0, Menu::DOUBLE, NULL},
{zone4SetTempStr, 4, -1, &configuration.profile.zone4SetTemp, 0, Menu::DOUBLE, NULL},
{zone5SetTempStr, 4, -1, &configuration.profile.zone5SetTemp, 0, Menu::DOUBLE, NULL},
{saveConfigStr, 2, -1, NULL, 0, Menu::ACTION, &saveConfig},
{starveFeederConfigStr, 2, 41, NULL, 0, Menu::TITLE, NULL},
{augerConfigStr, 2, 65, NULL, 0, Menu::TITLE, NULL},
{heaterConfigStr, 2, 71, NULL, 0, Menu::TITLE, NULL},
{outfeedConfigStr, 2, 109, NULL, 0, Menu::TITLE, NULL},
{spoolerConfigStr, 2, 110, NULL, 0, Menu::TITLE, NULL},
{homeStarveFeederStr, 36, -1, NULL, 0, Menu::ACTION, &homeStarveFeeder},
{dumpStr, 36, -1, NULL, 0, Menu::ACTION, &dump},
{feedStr, 36, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
{sendCyclesStr, 36, -1, NULL, 0, Menu::ACTION, &sendCyclesToStarveFeeder},
{cyclesToSendToStarveFeederStr, 36, -1, &cyclesToSendToStarveFeeder, 0, Menu::INT, NULL},
{sendTimeStr, 36, -1, NULL, 0, Menu::ACTION, &sendTimeToStarveFeeder},
{timeToSendToStarveFeederStr, 36, -1, &timeToSendToStarveFeeder, 0, Menu::INT, NULL},
{gramsPerMinStr, 36, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
{stopStr, 36, -1, NULL, 0, Menu::ACTION, &stopStarveFeeder},
{starveFeederSlaveAddressStr, 36, -1, &configuration.physical.starveFeederSlaveAddress, 0, Menu::INT, NULL},
{starveFeederLumpMassStr, 36, -1, &configuration.physical.starveFeederLumpMass, 2, Menu::FLOAT, NULL},
{starveFeederHomePositionStr, 36, -1, &configuration.physical.starveFeederHomePosition, 0, Menu::INT, NULL},
{starveFeederDumpPositionStr, 36, -1, &configuration.physical.starveFeederDumpPosition, 0, Menu::INT, NULL},
{starveFeederStepDelayStr, 36, -1, &configuration.physical.starveFeederStepDelay, 0, Menu::INT, NULL},
{starveFeederHomingStepDelayStr, 36, -1, &configuration.physical.starveFeederHomingStepDelay, 0, Menu::INT, NULL},
{starveFeederOverRotationStr, 36, -1, &configuration.physical.starveFeederOverRotation, 0, Menu::INT, NULL},
{starveFeederDirectionStr, 36, -1, &configuration.physical.starveFeederDirection, 0, Menu::BOOLEAN, NULL},
{starveFeederVibDutyCycleStr, 36, -1, &configuration.physical.starveFeederVibDutyCycle, 0, Menu::INT, NULL},
{starveFeederStartupDutyCycleStr, 36, -1, &configuration.physical.starveFeederStartupDutyCycle, 0, Menu::INT, NULL},
{starveFeederMaxDutyCycleStr, 36, -1, &configuration.physical.starveFeederMaxDutyCycle, 0, Menu::INT, NULL},
{starveFeederMinFillTimeStr, 36, -1, &configuration.physical.starveFeederMinFillTime, 0, Menu::INT, NULL},
{starveFeederMaxFillTimeStr, 36, -1, &configuration.physical.starveFeederMaxFillTime, 0, Menu::INT, NULL},
{starveFeederStartupTimeStr, 36, -1, &configuration.physical.starveFeederStartupTime, 0, Menu::INT, NULL},
{starveFeederDebounceTimeStr, 36, -1, &configuration.physical.starveFeederDebounceTime, 0, Menu::INT, NULL},
{testAugerStr, 37, -1, NULL, 0, Menu::ACTION, &testAuger},
{augerPinSetStr, 37, -1, &configuration.physical.augerPinSet, 0, Menu::INT, NULL},
{augerStepModeStr, 37, -1, &configuration.physical.augerStepMode, 0, Menu::INT, NULL},
{augerDirectionStr, 37, -1, &configuration.physical.augerDirection, 0, Menu::BOOLEAN, NULL},
{augerEnableStr, 37, -1, &configuration.physical.augerEnable, 0, Menu::BOOLEAN, NULL},
{augerGearRatioStr, 37, -1, &configuration.physical.augerGearRatio, 2, Menu::FLOAT, NULL},
{heaterStateStr, 38, -1, &heaterState, 0, Menu::STRING_LOCKED, &toggleHeaterState},
{zone1TempStr, 38, -1, &zone1Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone2TempStr, 38, -1, &zone2Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone3TempStr, 38, -1, &zone3Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone4TempStr, 38, -1, &zone4Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone5TempStr, 38, -1, &zone5Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone1SetTempStr, 38, -1, &configuration.physical.zone1.setTemp, 0, Menu::DOUBLE, NULL},
{zone2SetTempStr, 38, -1, &configuration.physical.zone2.setTemp, 0, Menu::DOUBLE, NULL},
{zone3SetTempStr, 38, -1, &configuration.physical.zone3.setTemp, 0, Menu::DOUBLE, NULL},
{zone4SetTempStr, 38, -1, &configuration.physical.zone4.setTemp, 0, Menu::DOUBLE, NULL},
{zone5SetTempStr, 38, -1, &configuration.physical.zone5.setTemp, 0, Menu::DOUBLE, NULL},
{zone1TimeBaseStr, 38, -1, &configuration.physical.zone1.timeBase, 0, Menu::INT, NULL},
{zone1MaxDutyCycleStr, 38, -1, &configuration.physical.zone1.maxDutyCycle, 0, Menu::DOUBLE, NULL},
{zone1MinDutyCycleStr, 38, -1, &configuration.physical.zone1.minDutyCycle, 0, Menu::DOUBLE, NULL},
{zone1KpStr, 38, -1, &configuration.physical.zone1.Kp, 2, Menu::DOUBLE, NULL},
{zone1KiStr, 38, -1, &configuration.physical.zone1.Ki, 2, Menu::DOUBLE, NULL},
{zone1KdStr, 38, -1, &configuration.physical.zone1.Kd, 2, Menu::DOUBLE, NULL},
{zone2TimeBaseStr, 38, -1, &configuration.physical.zone2.timeBase, 0, Menu::INT, NULL},
{zone2MaxDutyCycleStr, 38, -1, &configuration.physical.zone2.maxDutyCycle, 0, Menu::DOUBLE, NULL},
{zone2MinDutyCycleStr, 38, -1, &configuration.physical.zone2.minDutyCycle, 0, Menu::DOUBLE, NULL},
{zone2KpStr, 38, -1, &configuration.physical.zone2.Kp, 2, Menu::DOUBLE, NULL},
{zone2KiStr, 38, -1, &configuration.physical.zone2.Ki, 2, Menu::DOUBLE, NULL},
{zone2KdStr, 38, -1, &configuration.physical.zone2.Kd, 2, Menu::DOUBLE, NULL},
{zone3MaxDutyCycleStr, 38, -1, &configuration.physical.zone3.maxDutyCycle, 0, Menu::DOUBLE, NULL},
{zone3MinDutyCycleStr, 38, -1, &configuration.physical.zone3.minDutyCycle, 0, Menu::DOUBLE, NULL},
{zone3KpStr, 38, -1, &configuration.physical.zone3.Kp, 2, Menu::DOUBLE, NULL},
{zone3KiStr, 38, -1, &configuration.physical.zone3.Ki, 2, Menu::DOUBLE, NULL},
{zone3KdStr, 38, -1, &configuration.physical.zone3.Kd, 2, Menu::DOUBLE, NULL},
{zone4MaxDutyCycleStr, 38, -1, &configuration.physical.zone4.maxDutyCycle, 0, Menu::DOUBLE, NULL},
{zone4MinDutyCycleStr, 38, -1, &configuration.physical.zone4.minDutyCycle, 0, Menu::DOUBLE, NULL},
{zone4KpStr, 38, -1, &configuration.physical.zone4.Kp, 2, Menu::DOUBLE, NULL},
{zone4KiStr, 38, -1, &configuration.physical.zone4.Ki, 2, Menu::DOUBLE, NULL},
{zone4KdStr, 38, -1, &configuration.physical.zone4.Kd, 2, Menu::DOUBLE, NULL},
{zone5MaxDutyCycleStr, 38, -1, &configuration.physical.zone5.maxDutyCycle, 0, Menu::DOUBLE, NULL},
{zone5MinDutyCycleStr, 38, -1, &configuration.physical.zone5.minDutyCycle, 0, Menu::DOUBLE, NULL},
{zone5KpStr, 38, -1, &configuration.physical.zone5.Kp, 2, Menu::DOUBLE, NULL},
{zone5KiStr, 38, -1, &configuration.physical.zone5.Ki, 2, Menu::DOUBLE, NULL},
{zone5KdStr, 38, -1, &configuration.physical.zone5.Kd, 2, Menu::DOUBLE, NULL},
{RPMStr, 39, -1, &outfeedRPM, 0, Menu::FLOAT, NULL},
{testSpoolerStr, 40, -1, NULL, 0, Menu::ACTION, &testSpooler},
{spoolerPinSetStr, 40, -1, &configuration.physical.spoolerPinSet, 0, Menu::INT, NULL},
{spoolerStepModeStr, 40, -1, &configuration.physical.spoolerStepMode, 0, Menu::INT, NULL},
{spoolerDirectionStr, 40, -1, &configuration.physical.spoolerDirection, 0, Menu::BOOLEAN, NULL},
{spoolerEnableStr, 40, -1, &configuration.physical.spoolerEnable, 0, Menu::BOOLEAN, NULL},
{spoolerDiskRadiusStr, 40, -1, &configuration.physical.spoolerDiskRadius, 2, Menu::FLOAT, NULL},
{spoolerCoreRadiusStr, 40, -1, &configuration.physical.spoolerCoreRadius, 2, Menu::FLOAT, NULL},
{spoolerTraverseLengthStr, 40, -1, &configuration.physical.spoolerTraverseLength, 2, Menu::FLOAT, NULL},
{spoolerMotorRollerRadiusStr, 40, -1, &configuration.physical.spoolerMotorRollerRadius, 2, Menu::FLOAT, NULL},
{feedStr, 3, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
{measureFilametStr, 3, -1, NULL, -1, Menu::ACTION, &measureFilament},
{resetEEPROMStr, 3, -1, NULL, 0, Menu::ACTION, &resetEEPROM}
};

const Menu::MenuItem preheatItems[] PROGMEM =
{
{preheatRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitPreheat},
{zone1TempStr, 0, -1, &zone1Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone2TempStr, 0, -1, &zone2Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone3TempStr, 0, -1, &zone3Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone4TempStr, 0, -1, &zone4Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone5TempStr, 0, -1, &zone5Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone1InitialSetTempStr, 0, -1, &configuration.profile.zone1InitialSetTemp, 0, Menu::DOUBLE, &setZone1Temp},
{zone2InitialSetTempStr, 0, -1, &configuration.profile.zone2InitialSetTemp, 0, Menu::DOUBLE, &setZone2Temp},
{zone3InitialSetTempStr, 0, -1, &configuration.profile.zone3InitialSetTemp, 0, Menu::DOUBLE, &setZone3Temp},
{zone4InitialSetTempStr, 0, -1, &configuration.profile.zone4InitialSetTemp, 0, Menu::DOUBLE, &setZone4Temp},
{zone5InitialSetTempStr, 0, -1, &configuration.profile.zone5InitialSetTemp, 0, Menu::DOUBLE, &setZone5Temp},
{skipPreheatStr, 0, -1, NULL, 0, Menu::ACTION, &skipPreheat},
{profileNameStr, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetpointStr, 0, -1, &configuration.profile.diaSetpoint, 2, Menu::DOUBLE, NULL},
{toleranceStr, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPMStr, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{soakTimeStr, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL}
};

const Menu::MenuItem soakItems[] PROGMEM =
{
{soakRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitSoak},
{soakTimeRemainingStr, 0, -1, &soakTimeRemaining, 0, Menu::STRING_LOCKED, NULL},
{zone1TempStr, 0, -1, &zone1Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone2TempStr, 0, -1, &zone2Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone3TempStr, 0, -1, &zone3Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone4TempStr, 0, -1, &zone4Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone5TempStr, 0, -1, &zone5Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone1InitialSetTempStr, 0, -1, &configuration.profile.zone1InitialSetTemp, 0, Menu::DOUBLE, &setZone1Temp},
{zone2InitialSetTempStr, 0, -1, &configuration.profile.zone2InitialSetTemp, 0, Menu::DOUBLE, &setZone2Temp},
{zone3InitialSetTempStr, 0, -1, &configuration.profile.zone3InitialSetTemp, 0, Menu::DOUBLE, &setZone3Temp},
{zone4InitialSetTempStr, 0, -1, &configuration.profile.zone4InitialSetTemp, 0, Menu::DOUBLE, &setZone4Temp},
{zone5InitialSetTempStr, 0, -1, &configuration.profile.zone5InitialSetTemp, 0, Menu::DOUBLE, &setZone5Temp},
{increaseSoakTimeStr, 0, -1, NULL, 0, Menu::ACTION, &increaseSoakTime},
{decreaseSoakTimeStr, 0, -1, NULL, 0, Menu::ACTION, &decreaseSoakTime},
{skipSoakStr, 0, -1, NULL, 0, Menu::ACTION, &skipSoak},
{homeStarveFeederStr, 0, -1, NULL, 0, Menu::ACTION, &homeStarveFeeder},
{dumpStr, 0, -1, NULL, 0, Menu::ACTION, &dump},
{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
{profileNameStr, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetpointStr, 0, -1, &configuration.profile.diaSetpoint, 2, Menu::DOUBLE, NULL},
{toleranceStr, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPMStr, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{soakTimeStr, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL}
};

const Menu::MenuItem loadFilamentItems[] PROGMEM =
{
{loadFilamentRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitLoadFilament},
{loadFilamentRemainingTimeStr, 0, -1, &loadFilamentTimeRemaining, 0, Menu::STRING_LOCKED, NULL},
{filamentLoadedStr, 0, -1, NULL, 0, Menu::ACTION, &filamentLoaded},
{loadFilamentAddTimeStr, 0, -1, NULL, 0, Menu::ACTION, &loadFilamentAddTime},
{starveFeederModeStr, 0, -1, &starveFeederMode, 0, Menu::STRING_LOCKED, &starveFeederChangeMode},
{zone1TempStr, 0, -1, &zone1Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone2TempStr, 0, -1, &zone2Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone3TempStr, 0, -1, &zone3Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone4TempStr, 0, -1, &zone4Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone5TempStr, 0, -1, &zone5Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone1SetTempStr, 0, -1, &configuration.profile.zone1SetTemp, 0, Menu::DOUBLE, &setZone1Temp},
{zone2SetTempStr, 0, -1, &configuration.profile.zone2SetTemp, 0, Menu::DOUBLE, &setZone2Temp},
{zone3SetTempStr, 0, -1, &configuration.profile.zone3SetTemp, 0, Menu::DOUBLE, &setZone3Temp},
{zone4SetTempStr, 0, -1, &configuration.profile.zone4SetTemp, 0, Menu::DOUBLE, &setZone4Temp},
{zone5SetTempStr, 0, -1, &configuration.profile.zone5SetTemp, 0, Menu::DOUBLE, &setZone5Temp},
{profileNameStr, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetpointStr, 0, -1, &configuration.profile.diaSetpoint, 2, Menu::DOUBLE, NULL},
{toleranceStr, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, &setGramsPerMin},
{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, &setAugerRPM},
{outfeedRPMStr, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, &setOutfeedRPM},
{soakTimeStr, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL}
};

const Menu::MenuItem extrudeItems[] PROGMEM =
{
{extrudeRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitExtrude},
{zone1TempStr, 0, -1, &zone1Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone2TempStr, 0, -1, &zone2Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone3TempStr, 0, -1, &zone3Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone4TempStr, 0, -1, &zone4Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{zone5TempStr, 0, -1, &zone5Temp, 1, Menu::DOUBLE_LOCKED, NULL},
{setExtrudeTempsStr, 0, -1, NULL, 0, Menu::ACTION, &setTempsToExtrudeVals},
{zone1SetTempStr, 0, -1, &configuration.profile.zone1SetTemp, 0, Menu::DOUBLE, &setZone1Temp},
{zone2SetTempStr, 0, -1, &configuration.profile.zone2SetTemp, 0, Menu::DOUBLE, &setZone2Temp},
{zone3SetTempStr, 0, -1, &configuration.profile.zone3SetTemp, 0, Menu::DOUBLE, &setZone3Temp},
{zone4SetTempStr, 0, -1, &configuration.profile.zone4SetTemp, 0, Menu::DOUBLE, &setZone4Temp},
{zone5SetTempStr, 0, -1, &configuration.profile.zone5SetTemp, 0, Menu::DOUBLE, &setZone5Temp},
{starveFeederModeStr, 0, -1, &starveFeederMode, 0, Menu::STRING_LOCKED, &starveFeederChangeMode},
{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, &setGramsPerMin},
{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, &setAugerRPM},
{outfeedRPMStr, 0, -1, &configuration.physical.diaSensorRegMap.s.rpm, 1, Menu::DOUBLE, &setOutfeedRPM},
{outfeedModeStr, 0, -1, outfeedMode, 0, Menu::STRING_LOCKED, &changeOutfeedMode},
{diaSetpointStr, 0, -1, &configuration.physical.diaSensorRegMap.s.diaSetpoint, 2, Menu::DOUBLE, &changeOutfeedSetpoint},
{outfeedKpStr, 0, -1, &configuration.physical.diaSensorRegMap.s.kp, 2, Menu::DOUBLE, &setOutfeedTunings},
{outfeedKiStr, 0, -1, &configuration.physical.diaSensorRegMap.s.ki, 2, Menu::DOUBLE, &setOutfeedTunings},
{outfeedKdStr, 0, -1, &configuration.physical.diaSensorRegMap.s.kd, 2, Menu::DOUBLE, &setOutfeedTunings},
{outfeedMinRPMStr, 0, -1, &configuration.physical.diaSensorRegMap.s.outputMin, 2, Menu::DOUBLE, &setOutfeedTunings},
{outfeedMaxRPMStr, 0, -1, &configuration.physical.diaSensorRegMap.s.outputMax, 2, Menu::DOUBLE, &setOutfeedTunings},
{outfeedSampleTimeStr, 0, -1, &configuration.physical.diaSensorRegMap.s.sampleTime, 0, Menu::INT, &setOutfeedTunings},
{filamentDiameterStr, 0, -1, &configuration.physical.diaSensorRegMap.s.diameter, 3, Menu::DOUBLE_LOCKED, NULL},
{filamentDiameterFinalStr, 0, -1, &configuration.physical.qcDiaSensorRegMap.s.diameter, 3, Menu::DOUBLE_LOCKED, NULL}
};

#endif
