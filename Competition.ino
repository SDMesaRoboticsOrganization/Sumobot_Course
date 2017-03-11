#include <QTRSensors.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <ZumoBuzzer.h>


///////////////////////////  VAR/PINs  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//Define PINs
const int SONAR = 5;
const int LED = 13;
const int BUTTON = 12;
const int SPEED = 300;
const int REVERSE_DURATION = 200;
const int TURN_DURATION = 300;
const int NUM_SENSORS = 6;
const int TIMEOUT = 2500;
const int EMITTER_PIN = QTR_NO_EMITTER_PIN;

//Declare class objects
QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2, A3, A4, A5}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
Pushbutton button(BUTTON);
ZumoMotors motors;
ZumoBuzzer buzzer;

//Global Variables
int targetDist = 30;
long pulse1, sensor1;
unsigned int sensorValues[NUM_SENSORS];

///////////////////////////  END VAR/PINs  \\\\\\\\\\\\\\\\\\\\\\\\\\\


///////////////////////////  FUNCTIONS  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//QTR Calibration
void calibrateSensors()
{
  delay(500);
  digitalWrite(LED, HIGH);
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();
  }
  digitalWrite(LED, LOW);
  delay(1000);
}

//5 second countdown
void waitForButtonAndCountDown()
{
  button.waitForButton();
  digitalWrite(LED, HIGH);
  for (int i = 0; i < 4; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  digitalWrite(LED, LOW);  
  delay(1000);
}

long read_sensor()
{
  pulse1 = pulseIn(SONAR, HIGH);
  return pulse1/147;//convert to inches
}

//Forward
void driveForward()
{
  motors.setSpeeds(SPEED, SPEED);
}

void ram()
{
  motors.setSpeeds(SPEED*2, SPEED*2);
}

//Reverse
void driveBackward()
{
  motors.setSpeeds(-SPEED, -SPEED);
  delay(REVERSE_DURATION);
}

//Stop
void stopMotors()
{
  motors.setSpeeds(0,0);
  delay(2);
}

//Right
void turnRight()
{
  motors.setSpeeds(SPEED, -SPEED);
  delay(TURN_DURATION);
}

//Left
void turnLeft()
{
  motors.setSpeeds(-SPEED, SPEED);
  delay(TURN_DURATION);
}

bool isBlack()
{
  return ((sensorValues[0] > 200 && sensorValues[1] > 200 && sensorValues[2] > 200 && sensorValues[3] > 200  && sensorValues[4] > 200 && sensorValues[5]));
}

bool opponent()
{
  return (sensor1 < targetDist);
}
//////////////////////////  END FUNCTIONS  \\\\\\\\\\\\\\\\\\\\\\\\


//////////////////////////  SETUP  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(SONAR, INPUT);
  calibrateSensors();
  waitForButtonAndCountDown();
}

//////////////////////////  END SETUP  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


//////////////////////////  LOOP  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void loop() 
{
  qtrrc.read(sensorValues);
  sensor1 = read_sensor();

  if(isBlack())
  {
    driveForward();
    if(opponent())
    {
      ram();
    }
  }
  else
  {
    driveBackward();
    turnRight();
  } 
}
//////////////////////////  END LOOP  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\

