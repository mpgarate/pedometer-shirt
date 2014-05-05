const int pedometerPin = A5;

void setup(){
  Serial.begin(9600);
}
int pedoVal;
int lastPedoVal = 0;
int steps = 0;
int foundTime = 0;
int elapsedTime = 0;

void loop(){
  pedoVal = analogRead(pedometerPin);
    
  if (pedoVal != lastPedoVal){
    elapsedTime = millis() - foundTime;
    if (elapsedTime > 100){
      steps++;
    }
    
    foundTime = millis();
    
    //Serial.println(elapsedTime);
    Serial.println(steps);
  }
  
  
  
  lastPedoVal = pedoVal;
}
