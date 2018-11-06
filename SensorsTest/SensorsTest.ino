/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int photocellPin = A0;  // Analog input pins that the potentiometers are attached to
const int irPin = A1;
const int potPin = A2;
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int sensorValue1 = 0;
int sensorValue2 = 0;
int outputValue = 0;        // value output to the PWM (analog out)

int roomLight = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  roomLight = analogRead(photocellPin);
}

void loop() {

Serial.println(roomLight);
  
  // read the analog in value:
  sensorValue = analogRead(photocellPin);
  sensorValue1 = analogRead(irPin);
  sensorValue2 = analogRead(potPin);
  // map it to the range of the analog out:

  if (sensorValue < 100)
  {
    outputValue = 0;
  }

  else if (sensorValue < 375)
  {
    outputValue = map(sensorValue, 0, 1023, 100, 200);
  }

  else
  {
    outputValue = 255;
  }

  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("Light = ");
  Serial.print(sensorValue);
  Serial.print("  Distance = ");
  Serial.print(sensorValue1);
  Serial.print("  Pot = ");
  Serial.println(sensorValue2);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(30);
}
