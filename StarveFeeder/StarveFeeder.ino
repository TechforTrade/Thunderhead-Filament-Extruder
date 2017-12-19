#include <Wire.h>
int starveFeederSlaveAddress = 2;
boolean active = false;

//Flags for indicating a change sent by the master arduino
boolean homeFlag;
boolean setGPMFlag;
boolean loadConfigFlag;
boolean fastFill = false;
boolean runForSetTime = false;

enum Mode {
  GRAMS_PER_MIN,
  CYCLES,
};

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

//configuration data that is sent by master arduino
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

//General Variables
char key;
int cycles;
Mode mode;

//Time related variables
unsigned long now;//milliseconds
unsigned long dumpTime; //The time at which the plastic is to be dumped from the bucket in milliseconds
unsigned long dumpInterval; //The interval of time between dumps of plastic in milliseconds
unsigned long startTime;
unsigned long startFill;
unsigned long endStartupTime;
unsigned long fillTime;
unsigned long timeToRun;//Used when controller sends a specific amount of time in milliseconds that the starve feeder is to run
unsigned long endRunTime;//Time in milliseconds when the starve feeder is to be shutdown

//Vibrator related Variables
int minDutyCycle = 0;

//Pins
int sensorPin = 2;//The slot sensor pin
int vibPin = 3; //The  vibrator's PWM pin
int enablePin = 4; // the stepper enable pin
int stepPin = 5; //The stepper step pin
int dirPin = 6;//The stepper direction pin

//make state machine
//Setup Finite State Machine
void standby();
void homeBalance();
void prepFillBucket();
void startupVibrator();
void fillBucket();
void beginWait();
void wait();
void dump();
void feed();
void turnOff();

//Names of States
enum states {
  STANDBY,
  HOME_BALANCE,
  PREP_FILL_BUCKET,
  STARTUP_VIBRATOR,
  FILL_BUCKET,
  BEGIN_WAIT,
  WAIT,
  DUMP,
  FEED,
  TURN_OFF
};

states currentState;


//Pointers to State functios
void (*state_table[])() = {
  standby,
  homeBalance,
  prepFillBucket,
  startupVibrator,
  fillBucket,
  beginWait,
  wait,
  dump,
  feed,
  turnOff
};



//Setup
void setup() {
  Serial.begin(115200);
  Wire.begin(starveFeederSlaveAddress);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(sensorPin, INPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(vibPin, OUTPUT);

  digitalWrite(enablePin, HIGH);
  //Set initial state
  _config.homingStepDelay = 2000;
  _config.homePosition = 100;
  _config.dumpPosition = 1600;
  _config.stepDelay = 75;
  _config.gramsPerMin = 4.0;
  _config.lumpMass = 1.0;
  _config.minFillTime = 1000;
  _config.maxFillTime = 10000;
  _config.startupTime = 120;
  _config.debounceTime = 80;
  _config.overRotation = 90;
  _config.vibDutyCycle = 85;
  _config.maxDutyCycle = 160;
  _config.startupDutyCycle = 120;
  _config.dir = 1;

  currentState = STANDBY;
}

void loop() {
  if (Serial.available() > 0) {
    key = (char)Serial.read();
    switch (key) {
      case '1':
        {
          Serial.println("Homing balance");
          digitalWrite(dirPin, !_config.dir);
          currentState = HOME_BALANCE;
        }
        break;
      case '2':
        {
          startTime = millis();
          mode = GRAMS_PER_MIN;
          setGPMFlag = true;
          currentState = PREP_FILL_BUCKET;
        }
        break;
      case '3':
        {
          digitalWrite(enablePin, HIGH);
          analogWrite(vibPin, 0);
          cycles = 0;
          currentState = STANDBY;
        }
        break;
      case '4':
        {
          mode = CYCLES;
          currentState = DUMP;
        }
        break;
      case '5':
        {
          currentState = FEED;
        }
        break;
      case '6':
        {
          cycles = 10;
          mode = CYCLES;
          currentState = PREP_FILL_BUCKET;
        }
        break;
    }
  }

  if (setGPMFlag) {
    dumpInterval = _config.lumpMass / _config.gramsPerMin * 60L * 1000L;
    Serial.println(dumpInterval);
    Serial.print("Mode: ");
    Serial.println(mode);
    setGPMFlag = false;
    dumpTime = millis()+dumpInterval;
  }

  if (loadConfigFlag) {
    dumpInterval = _config.lumpMass / _config.gramsPerMin * 60L * 1000L;
    loadConfigFlag = false;
  }
  
  if (runForSetTime && millis()>=endRunTime){
    turnOff();
  }

  state_table[currentState]();
}

void standby() {
}

void homeBalance() {
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, _config.dir);
  for (int i = 0; i < _config.homePosition; i++) {
    PORTD |= B00100000;
    delayMicroseconds(_config.homingStepDelay);
    PORTD &= B11011111;
    delayMicroseconds(_config.homingStepDelay);
  }
  digitalWrite(enablePin, HIGH);
  currentState = STANDBY;
}


void prepFillBucket() {
  //disable stepper
  digitalWrite(enablePin, HIGH);

  //get time and turn jiggler on
  startFill = millis();
  endStartupTime = startFill + _config.startupTime;

  analogWrite(vibPin, _config.startupDutyCycle);
  currentState = STARTUP_VIBRATOR;

}

void startupVibrator() {
  //check to see if bucket is already full
  //Sometimes lots flows out initially
  if (digitalRead(sensorPin)) {

    // record time taken to fill bucket
    fillTime = millis() - startFill;

    //check to see if the bucket was caused by the bucket bouncing
    //if so reset the start time.
    //Is this necessary if the startup time is sufficient?
    if (fillTime < _config.debounceTime) {
      currentState = FILL_BUCKET;
      startFill = millis();
      return;
    }

    //Turn off vibrator
    analogWrite(vibPin, 0);
    //Switch states to BEGIN_WAIT
    currentState = BEGIN_WAIT;
  }

  if (millis() >= endStartupTime) {
    if (fastFill) { // fill bucket without slowing down
      fastFill = false;
      currentState = FILL_BUCKET;
    } else {
      //switch to normal dutycycle now that the vibrator is on
      analogWrite(vibPin, _config.vibDutyCycle);
      currentState = FILL_BUCKET;
    }
  }
}


void fillBucket() {
  //hangout while the bucket is filling.
  //IE - Do nothing
  
  //if we have passed the dumpInterval and it still isn't full
  //Juice it!
  //This will help to keep from getting too far behind
  if (millis() - startFill>dumpInterval){
      analogWrite(vibPin, _config.startupDutyCycle);
  }
  
  //When the sensor pin goes high the bucket is full
  //Capture the time for filling, and switch to BEGIN_WAIT
  if (digitalRead(sensorPin)) {

    // record time taken to fill bucket
    fillTime = millis() - startFill;

    //check to see if the bucket was caused by the bucket bouncing
    //if so reset the start time.
    //Is this necessary if the startup time is sufficient?
    if (fillTime < _config.debounceTime) {
      currentState = FILL_BUCKET;
      startFill = millis();
      return;
    }

    //Turn off vibrator
    analogWrite(vibPin, 0);
    //Switch states to BEGIN_WAIT
    currentState = BEGIN_WAIT;
  }
}

//Remove this state if not needed
void beginWait() {
    if (millis() > dumpTime) {
      fastFill = true;
    }
    currentState = WAIT;
}


void wait() {
  //If the mode is CYCLES switch to the DUMP state automatically
  if (mode == CYCLES) {
    cycles--;
    currentState = DUMP;
    return;
  }

  //wait until the dumpTime and then switch state to dump.
  if (mode == GRAMS_PER_MIN && millis() >= dumpTime) {
    //advance dumpTime
    dumpTime += dumpInterval;


    //Change state
    currentState = DUMP;
  }
}

void dump() {
  //enable Stepper
  digitalWrite(enablePin, LOW);
  //determine next dump time if in automatic mode
  
  //go to dump location
  digitalWrite(dirPin, _config.dir);
  for (int i = 0; i < _config.dumpPosition; i++) {
    PORTD |= B00100000;
    delayMicroseconds(_config.stepDelay);
    PORTD &= B11011111;
    delayMicroseconds(_config.stepDelay);
  }

  //return to home
  digitalWrite(dirPin, !_config.dir);
  for (int i = 0; i < _config.dumpPosition; i++) {
    PORTD |= B00100000;
    delayMicroseconds(_config.stepDelay);
    PORTD &= B11011111;
    delayMicroseconds(_config.stepDelay);
  }
  for (int i = 0; i < _config.overRotation; i++) {
    PORTD |= B00100000;
    delayMicroseconds(_config.stepDelay);
    PORTD &= B11011111;
    delayMicroseconds(_config.stepDelay);
  }
  delay(150);
  digitalWrite(dirPin, _config.dir);
  for (int i = 0; i < _config.overRotation; i++) {
    PORTD |= B00100000;
    delayMicroseconds(_config.stepDelay);
    PORTD &= B11011111;
    delayMicroseconds(_config.stepDelay);
  }
  delay(150);
  digitalWrite(enablePin, HIGH);
  if (mode == CYCLES && cycles == 0) {
    currentState = STANDBY;
  } else {
    //Change state to fill bucket
    currentState = PREP_FILL_BUCKET;
  }
}

void feed() {
  analogWrite(vibPin, _config.startupDutyCycle);
  currentState = STANDBY;
}

void turnOff() {
  analogWrite(vibPin, 0);
  digitalWrite(enablePin, HIGH);
  cycles = 0;
  active = false;
  runForSetTime = false;
  currentState = STANDBY;
}

void turnOn(){
      mode = GRAMS_PER_MIN;
      active = true;
      dumpInterval = _config.lumpMass * 60.0 * 1000.0 / _config.gramsPerMin;
      dumpTime = millis() + dumpInterval;
      currentState = PREP_FILL_BUCKET;
}

void receiveEvent(int bytesRecieved)
{
  byte* bytePtr;
  byte action = Wire.read();


  switch (action) {
    case ON://turn starve feeder on;
      turnOn();
      break;

    case OFF: //turn starve feeder off
      currentState = TURN_OFF;
      break;

    case HOME: //Home the starveFeeder
      currentState = HOME_BALANCE;
      break;

    case DUMP_BUCKET: //Dump
      mode = CYCLES;
      cycles = 0;
      currentState = DUMP;
      break;

    case FEED_PLASTIC: //Feed
      active = true;
      currentState = FEED;
      break;

    case SET_GPM: // set gramsPerMin
      bytePtr = (byte*)&_config.gramsPerMin;
      for (int i = 0; i < 4; i++) {
        *bytePtr = Wire.read();
        bytePtr++;
      }
      setGPMFlag = true;
      break;

    case SET_CYCLES: //set cycles to run
      bytePtr = (byte*)&cycles;
      for (int i = 0; i < 2; i++) {
        *bytePtr = Wire.read();
        bytePtr++;
      }
      active = true;
      mode = CYCLES;
      currentState = PREP_FILL_BUCKET;
      break;

    case LOAD_CONFIG://load the configuration of the starve feeder
      //load the incomming bytes to  _config
      bytePtr = (byte*)&_config;
      while (0 < Wire.available()) {
        *bytePtr = Wire.read();
        bytePtr++;
      }
      loadConfigFlag = true;
      break;
      
    case SET_TIME://Sets an amount of milliseconds for the starve feeder to run. Used for calibration
      bytePtr = (byte*)&timeToRun;
      while (0 < Wire.available()) {
        *bytePtr = Wire.read();
        bytePtr++;
      }
      endRunTime = timeToRun+millis();
      mode = GRAMS_PER_MIN;
      setGPMFlag = true;      
      currentState = PREP_FILL_BUCKET;
      runForSetTime = true;
  }

  //Make sure the buffer is left empty
  while (0 < Wire.available()) {
    *bytePtr = Wire.read();
    bytePtr++;
  }
}

void requestEvent()
{
  Wire.write(active);
}

