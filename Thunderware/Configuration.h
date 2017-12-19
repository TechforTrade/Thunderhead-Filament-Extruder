/*
  Configuration.h - Library for saving, loading,
 and deleting the various configurations both
 for the active profile and the physical setup
 of the extruder.

 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */


#ifndef Configuration_h
#define Configuration_h

#include "Arduino.h"

class Configuration
{
  public:
    struct Profile {
      //General
      int profileNumber;
      char name[20];
      double diaSetpoint;//mm
      float density; //g/cm3
      float tolerance;//mm

      //Starve Feeder
      float gramsPerMin;


      //Auger
      float augerRPM;

      //Outfeed
      double outfeedRPM;


      double soakTime;

      //heating Zones
      double zone1InitialSetTemp;
      double zone2InitialSetTemp;
      double zone3InitialSetTemp;
      double zone4InitialSetTemp;
      double zone5InitialSetTemp;

      double zone1SetTemp;
      double zone2SetTemp;
      double zone3SetTemp;
      double zone4SetTemp;
      double zone5SetTemp;

      //Safety parameters
      double minExtrudeTemp;
      double maxTemp; //The maximum temp allowed for any heating zone
      unsigned long maxPreheatTime;
    } profile, tempProfile;

    //Heating zone
    struct HeatingZone {
      int timeBase;//Time base in milliseconds if zero standard PWM will be used
      double maxDutyCycle;//The max dutyCycle for the barrel
      double minDutyCycle;//The min dutyCycle for the barrel
      double Kp, Ki, Kd;
      long thermistorRNom;
      int thermistorTNom;
      int thermistorNumSamples;
      int thermistorBCoefficient;
      int thermistorSeriesResistor;
      int thermistorPin;
      int heaterPin;
      int coolerPin;
      double setTemp;
      boolean PWM;
      boolean activeCooling;
    };
	
	//A struct the same as diameter sensor register.
	typedef struct DiaSensorRegMap_S {
		double diameter; //byte 0
		double rpm;//byte 4 //disable stepper if RPM = 0
		double diaSetpoint; //byte 8
		byte mode; //byte 12
		int sampleTime; //byte 13
		double kp;//byte 15
		double ki; //byte 19
		double kd; //byte 23
		double outputMin; //byte 27
		double outputMax; //byte 31
		boolean laserOn;//byte 35
		char version[8]; //byte 36
	};
	
	//A union with byte array for easily reading/writing data
	//using the wire library
	typedef union DiaSensorRegMap_u {
		DiaSensorRegMap_S s;
		byte b[sizeof(DiaSensorRegMap_S)];
	};

    /*The physicalConfig struct holds information describing *
     *the physical setup of the extruder.                    */

    struct PhysicalConfig {
      //variables that help with storage
      boolean configStored;
      boolean loadAutomatically;

      //StarveFeeder
      int starveFeederSlaveAddress;
      float starveFeederLumpMass;
      int starveFeederHomePosition;
      int starveFeederDumpPosition;
      int starveFeederStepDelay;
      int starveFeederHomingStepDelay;
      int starveFeederOverRotation;
      boolean starveFeederDirection;
      int starveFeederVibDutyCycle;
      int starveFeederStartupDutyCycle;
      int starveFeederMaxDutyCycle;
      int starveFeederMinDutyCycle;
      int starveFeederMinFillTime;
      int starveFeederMaxFillTime;
      int starveFeederStartupTime;
      int starveFeederDebounceTime;


      //Auger
      int augerPinSet;
      int augerStepMode;
      boolean augerDirection;
      boolean augerEnable;
      float augerGearRatio;

      //Outfeed
      int outfeedPinSet;
      int outfeedStepMode;
      boolean outfeedDirection;
      boolean outfeedEnable;
      float outfeedRollerRadius;
      double outfeedMaxRPM;
      double outfeedMinRPM;


      //Spooler
      int spoolerPinSet;
      int spoolerStepMode;
      boolean spoolerDirection;
      boolean spoolerEnable;
      float spoolerDiskRadius;
      float spoolerCoreRadius;
      float spoolerTraverseLength;
      float spoolerMotorRollerRadius;

      //Heating Zones
      HeatingZone zone1;
      HeatingZone zone2;
      HeatingZone zone3;
      HeatingZone zone4;
      HeatingZone zone5;

      //Diameter Sensor
      DiaSensorRegMap_u diaSensorRegMap;//The register map which is a union of a byte array and a struct
      DiaSensorRegMap_u qcDiaSensorRegMap;//The register map which is a union of a byte array and a struct

      //Parameters for the different states
      double maxTemp;
      unsigned long loadFilamentTime; //The number of minutes allowed for loading the filament.

    } physical;

    char profileNames[10][20];
    char name0[20];
    void loadProfileName(char* namePtr, int profile);//Used for menus.
    void loadProfileNames();
    Configuration();//constructor
    void saveConfig();
    void deleteConfig();
    void loadConfig();//returns true if successfull
    void loadDefaultConfig();
    void saveProfile();//Saves profile in designated position.
    boolean loadProfile(int profileNum);
    void loadDefaultProfile();
    void deleteProfile(int profileNum);

    //returns a pointer to the name of the indicated profile
    char *getName(int profileNum);


  private:
    int calculateOffset(int profileNum);//determines the address of a profile
    int numProfiles;//The number of allowed profiles
};

#endif


