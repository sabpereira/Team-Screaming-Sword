int steps=9;
int dir =8;
int stepTime=50;



void setup() {
  
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);
}


void loop() {
  digitalWrite(dir, HIGH);
  digitalWrite(steps, HIGH);   
  delay(stepTime);                      
  digitalWrite(steps, LOW);    
  delay(stepTime);                       
}
