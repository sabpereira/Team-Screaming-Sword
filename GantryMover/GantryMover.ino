
#include <FlexyStepper.h>



int photocellValue = 0; // value read from the photocell
int photocellValue2 = 0;
int roomLight = 0;
int lightThresholdOffset = 50;
int lightCounter = 0;
int lightCounter2 = 0;



int stepIncrementsUp = -200 * 10;
int stepIncrementsDown = -200 * 10;


//
// pin assignments
//
const int photocellPin = A0;
const int photocellPin2 = A1;
const int MOTOR_X_STEP_PIN = 7;
const int MOTOR_X_DIRECTION_PIN = 8;
const int MOTOR_Y_STEP_PIN = 12;
const int MOTOR_Y_DIRECTION_PIN = 13;


//
// create two stepper motor objects, one for each motor
//
FlexyStepper stepperX;
FlexyStepper stepperY;


void setup() {

  Serial.begin(9600);
  //Calibrate to room lighting
  roomLight = analogRead(photocellPin);


  //
  // connect and configure the stepper motors to their IO pins
  //
  stepperX.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIRECTION_PIN);
  stepperY.connectToPins(MOTOR_Y_STEP_PIN, MOTOR_Y_DIRECTION_PIN);

}

void loop() {
  //
  // setup the speed, acceleration and number of steps to move for the motors
  //

  photocellValue = analogRead(photocellPin);
  photocellValue2 = analogRead(photocellPin2);
  Serial.print("Photocell sensor = ");
  Serial.println(photocellValue);


  stepperX.setSpeedInStepsPerSecond(75);
  stepperX.setAccelerationInStepsPerSecondPerSecond(50);
  stepperY.setSpeedInStepsPerSecond(75);
  stepperY.setAccelerationInStepsPerSecondPerSecond(50);



  if (photocellValue >= (roomLight + lightThresholdOffset)) {
    Serial.println("It's Bright");
    lightCounter += 1;
    Serial.println(lightCounter);
    delay(1000);
  }
  if (photocellValue2 >= (roomLight + lightThresholdOffset)) {
    Serial.println("It's Bright");
    lightCounter2 += 1;
    Serial.println(lightCounter2);
    delay(1000);
  }
  if (lightCounter >= 3) {
    stepperX.setTargetPositionInSteps(stepIncrementsUp);
    while (!stepperX.motionComplete()) {
      // Note: The code added to this loop must execute VERY fast.
      // Perhaps no longer than 0.05 milliseconds.

      stepperX.processMovement();  // process motor steps

      //In case we implement time dependent rising
      //if (millis() >= 5000)
      //{
      //  stepper.setTargetPositionToStop();
      //}

    }

  }
  if (lightCounter2 >= 3) {
    stepperY.setTargetPositionInSteps(stepIncrementsUp);
    while (!stepperY.motionComplete()) {
      // Note: The code added to this loop must execute VERY fast.
      // Perhaps no longer than 0.05 milliseconds.

      stepperY.processMovement();// process motor steps

      //In case we implement time dependent rising
      //if (millis() >= 5000)
      //{
      //  stepper.setTargetPositionToStop();
      //}

    }
  }


if (photocellValue < (roomLight + lightThresholdOffset)) {
  lightCounter = 0;

  if (photocellValue <= (roomLight - lightThresholdOffset)) {
    stepperX.setTargetPositionInSteps(-stepIncrementsDown);
    stepperY.setTargetPositionInSteps(-stepIncrementsDown);
    while (!stepperX.motionComplete()) {
      stepperX.processMovement();
      stepperY.processMovement();
    }
  }
}




}





