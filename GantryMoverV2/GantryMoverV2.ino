
#include <FlexyStepper.h>



int photocellValue1 = 0; // value read from the photocell
int photocellValue2 = 0;
int photocellValue3 = 0; // value read from the photocell
int photocellValue4 = 0;

int roomLight = 0;
int lightThresholdOffset = 50;
int lightCounter = 0;
int lightCounter2 = 0;

int motor1Go;
int motor2Go;
int motor3Go;
int motor4Go;

int stepsToTop = 200 * 10;

int loopCounter = 0;


//
// pin assignments
//

const int photocellPin1 = A0;
const int photocellPin2 = A1;
const int photocellPin3 = A2;
const int photocellPin4 = A3;

const int MOTOR_1_STEP_PIN = 2;
const int MOTOR_1_DIRECTION_PIN = 3;
const int MOTOR_2_STEP_PIN = 4;
const int MOTOR_2_DIRECTION_PIN = 5;
const int MOTOR_3_STEP_PIN = 6;
const int MOTOR_3_DIRECTION_PIN = 7;
const int MOTOR_4_STEP_PIN = 8;
const int MOTOR_4_DIRECTION_PIN = 9;

//
// create two stepper motor objects, one for each motor
//
FlexyStepper stepper1;
FlexyStepper stepper2;
FlexyStepper stepper3;
FlexyStepper stepper4;


void setup() {

  Serial.begin(9600);
  //Calibrate to room lighting
  roomLight = analogRead(photocellPin1);


  //
  // connect and configure the stepper motors to their IO pins
  //
  stepper1.connectToPins(MOTOR_1_STEP_PIN, MOTOR_1_DIRECTION_PIN);
  stepper2.connectToPins(MOTOR_2_STEP_PIN, MOTOR_2_DIRECTION_PIN);
  stepper3.connectToPins(MOTOR_3_STEP_PIN, MOTOR_3_DIRECTION_PIN);
  stepper4.connectToPins(MOTOR_4_STEP_PIN, MOTOR_4_DIRECTION_PIN);


  //
  // setup the speed, acceleration and number of steps to move for the motors
  //

  stepper1.setSpeedInStepsPerSecond(75);
  stepper1.setAccelerationInStepsPerSecondPerSecond(50);
  stepper2.setSpeedInStepsPerSecond(150); // this is the fancy stepper
  stepper2.setAccelerationInStepsPerSecondPerSecond(50);
  stepper3.setSpeedInStepsPerSecond(75);
  stepper3.setAccelerationInStepsPerSecondPerSecond(50);
  stepper4.setSpeedInStepsPerSecond(75);
  stepper4.setAccelerationInStepsPerSecondPerSecond(50);

}

void loop() {
  if ( loopCounter == 1) {
    photocellValue1 = analogRead(photocellPin1);
    if (photocellValue1 > roomLight + lightThresholdOffset) {
      stepper1.setSpeedInStepsPerSecond(75);
      stepper1.setTargetPositionInSteps(stepsToTop);
      motor1Go = true;
      Serial.print("+");
    }
    else if (photocellValue1 < roomLight - lightThresholdOffset) {
      stepper1.setSpeedInStepsPerSecond(75);
      stepper1.setTargetPositionInSteps(0);
      motor1Go = true;
      Serial.print("-");

    }
    else {
      stepper1.setSpeedInStepsPerSecond(0);
      motor1Go = false;
      Serial.print("0");

    }
  }
  if ( loopCounter == 2) {
    photocellValue2 = analogRead(photocellPin2);
    if (photocellValue2 > roomLight + lightThresholdOffset) {
      stepper2.setSpeedInStepsPerSecond(150);
      stepper2.setTargetPositionInSteps(-stepsToTop);
      motor2Go = true;
    }
    else if (photocellValue2 < roomLight - lightThresholdOffset) {
      stepper2.setSpeedInStepsPerSecond(150);
      stepper2.setTargetPositionInSteps(0);
      motor2Go = true;
    }
    else {
      stepper2.setSpeedInStepsPerSecond(0);
      motor2Go = false;
    }
  }
  if ( loopCounter == 3) {
    photocellValue3 = analogRead(photocellPin3);
    if (photocellValue3 > roomLight + lightThresholdOffset) {
      stepper3.setSpeedInStepsPerSecond(150);
      stepper3.setTargetPositionInSteps(stepsToTop);
      motor3Go = true;
    }
    else if (photocellValue3 < roomLight - lightThresholdOffset) {
      stepper3.setSpeedInStepsPerSecond(150);
      stepper3.setTargetPositionInSteps(0);
      motor3Go = true;
    }
    else {
      stepper3.setSpeedInStepsPerSecond(0);
      motor3Go = false;

    }
  }
  if ( loopCounter == 4) {
    photocellValue4 = analogRead(photocellPin4);
    if (photocellValue4 > roomLight + lightThresholdOffset) {
      stepper4.setSpeedInStepsPerSecond(150);
      stepper4.setTargetPositionInSteps(stepsToTop);
      motor4Go = true;
    }
    else if (photocellValue4 < roomLight - lightThresholdOffset) {
      stepper4.setSpeedInStepsPerSecond(150);
      stepper4.setTargetPositionInSteps(0);
      motor4Go = true;
    }
    else {
      stepper4.setSpeedInStepsPerSecond(0);
      motor4Go = false;
      Serial.print("0");

    }
  }  

  // start processing movement
  if (motor1Go) {
    stepper1.processMovement();
  }
  if (motor2Go) {
    stepper2.processMovement();
  }
  if (motor3Go) {
    stepper3.processMovement();
  }
  if (motor4Go) {
    stepper4.processMovement();
  }

  loopCounter++;
  if (loopCounter == 300) {
    loopCounter = 0;
  }




}
















//if (photocellValue1 < (roomLight + lightThresholdOffset)) {
//  lightCounter = 0;
//
//  if (photocellValue1 <= (roomLight - lightThresholdOffset)) {
//    stepperX.setTargetPositionInSteps(0);
//    stepperY.setTargetPositionInSteps(0);
//    while (!stepperX.motionComplete()) {
//      stepperX.processMovement();
//      stepperY.processMovement();
//    }
//  }
//}
//








