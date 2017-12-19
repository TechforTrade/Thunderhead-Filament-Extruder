//Thermistor

// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Thermistor.h"



Thermistor::Thermistor(int tPin, long rNominal, int tTempNominal, int numSamples, int bCoefficient, int seriesResistor)
{
	_tPin = tPin; //The analog pin connected to the thermistor
	_rNominal = rNominal;//The nominal resistance of the thermistor
	_tTempNominal = tTempNominal;//The nominal temperature of the thermistor
	_numSamples = numSamples;//The number of samples to average
	_bCoefficient = bCoefficient; //The beta coefficient of the thermistor
	_seriesResistor = seriesResistor; //The value of the series resistor
	_vApplied = 5;
	_adcRange = 1024;
	_measureTime = millis();



}


void Thermistor:: sampleTemp() {

	_now = millis();
	if (_now > _measureTime) {

		_sampleSum +=  analogRead(_tPin);

		if (_sampleCounter == _numSamples - 1) {

			//get Average measurement
			float average = (float)_sampleSum / (float)_numSamples;
			avgADC = average;
			//Reset _sampleSum and _sampeleCounter
			_sampleCounter = 0;
			_sampleSum = 0.0;
			
			_avgTemp = lookUpTemp();
			temp = _avgTemp;

			// The following is for use without lookup table.
			//      // convert the value to resistance
			//      average = 1023.0 / average - 1.0;
			//      average = _seriesResistor / average;
			//
			//      //    _avgTemp;
			//      _avgTemp = average / (float)_rNominal; // (R/Ro)
			//      _avgTemp = log(_avgTemp); // ln(R/Ro)
			//      _avgTemp /= (float)_bCoefficient; // 1/B * ln(R/Ro)
			//      _avgTemp += 1.0 / ((float)_tTempNominal + 273.15); // + (1/To)
			//      _avgTemp = 1.0 / _avgTemp; // Invert
			//      _avgTemp -= 273.15; // convert to C
			//      temp = _avgTemp; //update public variable;
			} else {
			_sampleCounter++;
		}
		_measureTime = _now + 20;

	}
}

int Thermistor::getADC() {
	return avgADC;
}

float Thermistor::getTemp() {
	return _avgTemp;
}

float Thermistor::lookUpTemp() {
	if ((avgADC == 1023) || (avgADC == 0.0)) {
		//The thermistor is disconnected
		return -1;
	}
	int x1;
	int y1;
	int x2;
	int y2;

	
	if ((avgADC < pgm_read_word_near(&lookUpTable[0][0])) && (avgADC >= pgm_read_word_near(&lookUpTable[29][0]))) {
		// loop one less than length of lookUpTable
		for (int i = 1; i < 29; i++) {
			if (avgADC == pgm_read_word_near(&lookUpTable[i][0])) {
				return pgm_read_word_near(&lookUpTable[i][1]);
			}
			if (avgADC > pgm_read_word_near(&lookUpTable[i][0])) {
				x1 = pgm_read_word_near(&lookUpTable[i-1][0]);
				y1 = pgm_read_word_near(&lookUpTable[i-1][1]);
				x2 = pgm_read_word_near(&lookUpTable[i][0]);
				y2 = pgm_read_word_near(&lookUpTable[i][1]);
				break;
			}
		}
		} else if (avgADC > pgm_read_word_near(&lookUpTable[0][0])) {
		x1 = pgm_read_word_near(&lookUpTable[0][0]);
		y1 = pgm_read_word_near(&lookUpTable[0][1]);
		x2 = pgm_read_word_near(&lookUpTable[1][0]);
		y2 = pgm_read_word_near(&lookUpTable[1][1]);

		} else if (avgADC < pgm_read_word_near(&lookUpTable[29][0])) {
		x1 = pgm_read_word_near(&lookUpTable[28][0]);
		y1 = pgm_read_word_near(&lookUpTable[28][1]);
		x2 = pgm_read_word_near(&lookUpTable[29][0]);
		y2 = pgm_read_word_near(&lookUpTable[29][1]);

		} else if (avgADC == pgm_read_word_near(&lookUpTable[0][0])) {
		return pgm_read_word_near(&lookUpTable[0][1]);
	}

	float temp = (float)(y2 - y1) / (float)(x2 - x1) * (avgADC - (float)x1) + (float)y1;
	return temp;
}
