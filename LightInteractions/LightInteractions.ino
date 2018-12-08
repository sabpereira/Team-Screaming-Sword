//int photocellValues[6];// = {0, 0, 0, 0, 0, 0};        // values read from the photocells
int roomLight = 0;
int lightThresholdOffset = 50;
int lightCounter = 0;
unsigned long flashCounter = 0;

const int ul = A0; // Upper left photocell
//Upper platform only has 3 mushrooms and 3 static plants, doesn't need a photocell
const int ur = A1; // Upper right photocell
const int l = A2; // Left photocell
const int ll = A3; // Lower left photocell
const int lo = A4; // Lower photocell
const int lr = A5; // Lower right photocell

const int fc1 = 12; //fairy circle digital pin - does not need to be a PWM pin
const int fc2 = 11; //second fairy circle digital pin - does not need to be a PWM pin

unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
int interval = 500; // time interval between blinks


void setup() {
  Serial.begin(9600);
  
  pinMode(fc1, OUTPUT);
  pinMode(fc2, OUTPUT);
  
  //Calibrate to room lighting
  // roomLight = (analogRead(ul)+analogRead(ur)+analogRead(l)+analogRead(ll)+analogRead(lo)+analogRead(lr))/6;
  roomLight = analogRead(ul);
}

void loop() {
  //photocellValues = {analogRead(ul), analogRead(ur), analogRead(l), analogRead(ll), analogRead(lo), analogRead(lr)};

  //Fairy circle: Lower left. Controlled by one photocell, involves two digital pins. 
  // If you get close to it, every other mushroom should flash. Each four mushrooms are connected in series
  // and controlled by one digital pin.

  currentMillis = millis();

  // if the fairy circle photocell is below a certain interval, start the flashing routine
  if (analogRead(ul) <= (roomLight - lightThresholdOffset/2)) {
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
  
}
