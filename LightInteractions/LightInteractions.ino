int photocellValues[] = {0, 0, 0, 0, 0, 0};        // values read from the photocells
int roomLight = 0;
int lightThresholdOffset = 50;
int lightCounter = 0;

const int ul = A0; // Upper left photocell
//Upper platform only has 3 mushrooms and 3 static plants, doesn't need a photocell
const int ur = A1; // Upper right photocell
const int l = A2; // Left photocell
const int ll = A3; // Lower left photocell
const int lo = A4; // Lower photocell
const int lr = A5; // Lower right photocell

const int 

void setup() {
  Serial.begin(9600);
  pinMode(ul, INPUT);
  pinMode(ur, INPUT);
  pinMode(l, INPUT);
  pinMode(ll, INPUT);
  pinMode(lo, INPUT);
  pinMode(lr, INPUT);
  roomLight = (analogRead(ul)+analogRead(ur)+analogRead(l)+analogRead(ll)+analogRead(lo)+analogRead(lr))/6;
}

void loop() {
  photocellValues[] = {analogRead(ul), analogRead(ur), analogRead(l), analogRead(ll), analogRead(lo), analogRead(lr)};
  
}
