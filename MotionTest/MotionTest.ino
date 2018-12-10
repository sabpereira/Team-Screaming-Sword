
#include <FlexyStepper.h>


int stepIncrementsUp = -200 * 4;
int stepIncrementsDown = 200 * 4;


const int MOTOR_X_STEP_PIN = 7;
const int MOTOR_X_DIRECTION_PIN = 8;

//
// create a stepper motor objects, one for each motor
//
FlexyStepper stepperX;


void setup() {

  Serial.begin(9600);
  //
  // connect and configure the stepper motors to their IO pins
  //
  stepperX.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIRECTION_PIN);

}

void loop() {
  //
  // setup the speed, acceleration and number of steps to move for the motors
  //

  stepperX.setSpeedInStepsPerSecond(75);
  stepperX.setAccelerationInStepsPerSecondPerSecond(50);


  //  if (photocellValue >= (roomLight + lightThresholdOffset)) {
  //    Serial.println("It's Bright");
  //    lightCounter += 1;
  //    Serial.println(lightCounter);
  //    delay(1000);


//    stepperX.setTargetPositionRelativeInSteps(stepIncrementsUp);
//    while (!stepperX.motionComplete()) {
//      stepperX.processMovement();
//    }
//    delay(500);
    stepperX.setTargetPositionInSteps(stepIncrementsDown);
    while (!stepperX.motionComplete()) {
      stepperX.processMovement();
      Serial.println(stepperX.getCurrentPositionInSteps());
    }
    delay(500);
    
    stepperX.setTargetPositionInSteps(0);
    while (!stepperX.motionComplete()) {
      stepperX.processMovement();
      Serial.println(stepperX.getCurrentPositionInSteps());
//      if (stepperX.getCurrentPositionInSteps() <= 1)
//      {
//        stepperX.setTargetPositionToStop();
//        break;
//      }
    }
    delay(500);
    


}




//    if (millis() >= 5000)
//    {
//      stepperX.setTargetPositionToStop();
//      break;
//    }



