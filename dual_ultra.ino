/**
*  Pin designations for trigger, echo and LED.
* Note Two separate ultrasonic sensors and two separate LEDs.
*
* Trigger receives a pulse of power from arduino 
* That pulse sends 'triggers' an ultrasonic 
* sound wave from the sensor.
*
* Echo receives the sound wave back from the object 
* it bounces off of.
*
*/
#define trigPin1 13
#define echoPin1 12
#define led1 11 // Note pin 11 should be connected to the Ground pin of the LED
/**
* Pin definitions for ultrasonic sensor 2
* and LED 2
*/
#define trigPin2 4
#define echoPin2 3
#define led2 2

/**
* Global variable definitions.
*/
long distance, duration, leftSensor, rightSensor;

/**
* Establish Trigger pin as output and 
* Echo as input.
*
* Also begin a serial data stream.
*/
void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(led1, OUTPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led2, OUTPUT);
}

void loop() 
{
  // Calling SonarSensor reads values into duration and distance.
  SonarSensor(trigPin1, echoPin1);
  leftSensor = distance;

  // If an obstruction is detected within range, 
  // the LED will turn on.
  if (leftSensor < 30) 
  {  
    digitalWrite(led1, LOW); 

   // If an obstruction is not detected the LED
   // turns off.
  } else
  {
    digitalWrite(led1, HIGH);
  }

  SonarSensor(trigPin2, echoPin2);
  rightSensor = distance;

  if (rightSensor < 30)
  {
    digitalWrite(led2, LOW);
    
  } else
  {
    digitalWrite(led2, HIGH);
  }

  delay(5);
} 
/**
* SonarSensor 
* Can be used with any sensor attached to the Arduino
*
* Parameters: trigger and echo pins for the ultrasonic
* sensor we want to work with.
*
* *Note we could make this method return distance*
*/
void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
}

