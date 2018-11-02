/*
  Code Title:

  Code Description:

*/

// SENSOR INITIALIZATION
const int analogInPin = A0;     // Analog input pin that the potentiometer is attached to
const int button = 2;          //Digital pin for button
const int mushroomLight1 = 9;   // Analog output pin that the LED is attached to for mushrooms
const int mushroomLight2 = 10;


int sensorValue = 0;        // value read from the photocell
int outputValue = 0;        // value output to the PWM (analog out) LEDs
int lightThreshold = 375;
int counter = 1;          //Used for mode changes, 1 is main mode

int buttonState = 0;      //Initialize variables for the button's state and to detect changes
int lastButtonState = 0;


// MOTOR INITIALIZATION
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

int motorSpeed = 25;        // What speed we want the motors to go with light


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  // Initialize Motor Stuff
  AFMS.begin();

  myMotor1->setSpeed(00);
  myMotor2->setSpeed(00);
  myMotor3->setSpeed(00);
  myMotor4->setSpeed(00);

}

void loop() {

  // read the photocell sensor value:
  sensorValue = analogRead(analogInPin);

  //Updates buttonState to current state of button
  buttonState = digitalRead(button);

  Serial.print("sensor = ");
  Serial.println(sensorValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);

  //  // print the results to the Serial Monitor:
  //  Serial.print("sensor = ");
  //  Serial.print(sensorValue);
  //  Serial.print("\n");
  //
  //  // wait 50 milliseconds before the next loop for the analog-to-digital
  //  // converter to settle after the last reading:
  //  delay(50);


  //MAIN MODE
  if (counter == 1)
  {

    if (sensorValue > lightThreshold) {
      myMotor1->setSpeed(motorSpeed);  myMotor2->setSpeed(motorSpeed);  myMotor3->setSpeed(motorSpeed);  myMotor4->setSpeed(motorSpeed+20);
      myMotor1->run(FORWARD);
      myMotor2->run(FORWARD);
      myMotor3->run(FORWARD);
      myMotor4->run(FORWARD);

      //Turn Mushroom LEDs on related to light sensor values
      outputValue = map(sensorValue, lightThreshold, 1023, 0, 200);
      analogWrite(mushroomLight1, outputValue);
      analogWrite(mushroomLight2, outputValue);
    }
    else {

      myMotor1->setSpeed(00);
      myMotor2->setSpeed(00);
      myMotor3->setSpeed(00);
      myMotor4->setSpeed(00);
      myMotor1->run(FORWARD);
      myMotor2->run(FORWARD);
      myMotor3->run(FORWARD);
      myMotor4->run(FORWARD);
      outputValue = 0;
      analogWrite(mushroomLight1, outputValue);
      analogWrite(mushroomLight2, outputValue);
    }

    if (buttonState != lastButtonState)
    {
      if (buttonState == HIGH)
      {
        counter = 2;
      }
      delay(30);
    }
    lastButtonState = buttonState;
  }


  //STOP MODE
  if (counter == 2)
  {

    myMotor1->setSpeed(00);
    myMotor2->setSpeed(00);
    myMotor3->setSpeed(00);
    myMotor4->setSpeed(00);
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(FORWARD);

    if (buttonState != lastButtonState)    {
      if (buttonState == HIGH)      {
        counter = 3;
      }
      delay(30);
    }
    lastButtonState = buttonState;
  }


  //REVERSE MODE
  if (counter == 3)
  {
    myMotor1->setSpeed(motorSpeed);  myMotor2->setSpeed(motorSpeed);  myMotor3->setSpeed(motorSpeed);  myMotor4->setSpeed(motorSpeed);
    myMotor1->run(BACKWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(BACKWARD);

    if (buttonState != lastButtonState)    {
    if (buttonState == HIGH)      {
        counter = 4;
      }
      delay(30);
    }
    lastButtonState = buttonState;
  }

  //STOP MODE again
  if (counter == 4)
  {

    myMotor1->setSpeed(00);
    myMotor2->setSpeed(00);
    myMotor3->setSpeed(00);
    myMotor4->setSpeed(00);
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(FORWARD);

    if (buttonState != lastButtonState)    {
      if (buttonState == HIGH)      {
        counter = 1;
      }
      delay(30);
    }
    lastButtonState = buttonState;
  }


}

