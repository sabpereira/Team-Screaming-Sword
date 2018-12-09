//int photocellValues[6];// = {0, 0, 0, 0, 0, 0};        // values read from the photocells
int roomLight_ul = 0;
int roomLight_ur = 0;
int roomLight_l = 0; 
int roomLight_ll = 0;
int roomLight_lo = 0;
int roomLight_lr = 0;
int lightThresholdOffset = 50;
unsigned long flashCounter = 0;
int lightReading = 0;
int outputValue = 0;

const int ul = A0; // Upper left photocell
//Upper platform only has 3 mushrooms and 3 static plants, doesn't need a photocell
const int ur = A1; // Upper right photocell
const int l = A2; // Left photocell
const int ll = A3; // Lower left photocell
const int lo = A4; // Lower photocell
const int lr = A5; // Lower right photocell

//int photocells[] = {ul, ur, l, ll, lo, lr};

//right now there's only one "photocell"/potentiometer
int photocells[] = {ul, ul, ul, ul, ul, ul};


const int fc1 = 13; //fairy circle digital pin - does not need to be a PWM pin
const int fc2 = 12; //second fairy circle digital pin - does not need to be a PWM pin
const int dimLED = 11; //dimming LED - needs to be a PWM pin

int roomLights[] = {roomLight_ul, roomLight_ur, roomLight_l, roomLight_ll, roomLight_lo, roomLight_lr};
int dimLEDS[] = {11, 10, 9, 6, 5, 3}; //all the PWM pins

unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
int interval = 500; // time interval between blinks


void setup() {
  Serial.begin(9600);
  
  pinMode(fc1, OUTPUT);
  pinMode(fc2, OUTPUT);
  
  //Calibrate to room lighting
  // roomLight = (analogRead(ul)+analogRead(ur)+analogRead(l)+analogRead(ll)+analogRead(lo)+analogRead(lr))/6;
  roomLight_ul = analogRead(ul);
  roomLight_ur = analogRead(ur);
  roomLight_l = analogRead(l);
  roomLight_ll = analogRead(ll);
  roomLight_lo = analogRead(lo);
  roomLight_lr = analogRead(lr);
}

void loop() {
  //photocellValues = {analogRead(ul), analogRead(ur), analogRead(l), analogRead(ll), analogRead(lo), analogRead(lr)};

  //Fairy circle: Lower left. Controlled by one photocell, involves two digital pins. 
  // If you get close to it, every other mushroom should flash. Each four mushrooms are connected in series
  // and controlled by one digital pin.

  currentMillis = millis();

  // if the fairy circle photocell is below a certain interval, start the flashing routine
  if (analogRead(ul) <= (roomLight_ul - lightThresholdOffset/2)) {
    if ((currentMillis - previousMillis) > interval) {
    
      //save the last time you blinked the LED
      previousMillis = currentMillis;
      flashCounter++; //increment counter

      //switches which LEDs are on
      if (flashCounter % 2 == 1) {
        digitalWrite(fc1, HIGH);
        digitalWrite(fc2, LOW);
      }
      if (flashCounter % 2 == 0){
        digitalWrite(fc1, LOW);
        digitalWrite(fc2, HIGH);
      }
    
    }
  }
  else {
    digitalWrite(fc1, LOW);
    digitalWrite(fc2, LOW);
  }
  // There are 6 PWM pins and there are 6 photocells. This code connects the light reading to how dim we want
  // the mushroom to be. Important that LEDs are connected in the same order as the photocells are arranged 
  // in this list: ul, ur, l, ll, lo, lr
  for (int i = 0; i<6; i++){
    lightReading = analogRead(photocells[i]);
    outputValue = map(lightReading, 0, 1023, 0, 255);
    analogWrite(dimLEDS[i], outputValue);
    delay(2);
  }
  
  
}
