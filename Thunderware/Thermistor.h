/*

 */
    

#ifndef Thermistor_h
#define Thermistor_h

#include <inttypes.h>
#include <avr/pgmspace.h>
const int lookUpTable[30][2] PROGMEM= {
      {1013, 22},
      {1011, 25},
      {1009, 30},
      {1001, 40},
      {994, 50},
      {978, 60},
      {962, 70},
      {941, 80},
      {913, 90},
      {879, 100},
      {840, 110},
      {790, 120},
      {740, 130},
      {682, 140},
      {625, 150},
      {579, 160},
      {513, 170},
      {458, 180},
      {395, 190},
      {338, 200},
      {300, 210},
      {265, 220},
      {235, 230},
      {200, 240},
      {172, 250},
      {150, 260},
      {130, 270},
      {114, 280},
      {99, 290},
      {83, 300}
    };
    
class Thermistor
{

  public:
    Thermistor(int tPin, long rNominal, int tTempNominal, int numSamples, int bCoefficient, int seriesResistor);
    void sampleTemp();
    float getTemp();
    double temp;
    int getADC();
    float lookUpTemp();

  protected:
    unsigned int displayInt;

    int avgADC;
    int _tPin;
    int _numSamples;
    long _rNominal;
    long _sampleSum;
    int _tTempNominal;
    int _sampleCounter;
    int _bCoefficient;
    int _seriesResistor;
    float _vApplied;
    float _avgTemp;
    int _adcRange;
    unsigned long _now;
    unsigned long _measureTime;


};

#endif