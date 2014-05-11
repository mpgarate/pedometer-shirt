#include <Adafruit_NeoPixel.h>

const int pedometerPin = 9;
const int neoPin = 6;

// number of LEDs in the strip
const int ledCount = 10; 

// neopixel LED series
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, neoPin, NEO_GRB + NEO_KHZ800);

// total number of steps counted today
int steps = 0;

// desired step count
int stepGoal = 20;

void setup(){
  Serial.begin(9600);
  strip.begin();
  strip.show();
}


void loop(){
  
  updateStepCount();
  
  
  // if goal has been reached
  // celebrate and start over
  if (steps > stepGoal){
    playCelebration();
    steps = 0;
  }
  
  updateProgressBar();

}


// keep track of current time and time of last successful elapse
int ledCurrentMillis;
int ledPreviousMillis = 0;

boolean elapsedTimeForLed(int interval){
  ledCurrentMillis = millis();
  
  if (ledCurrentMillis - ledPreviousMillis > interval){
    ledPreviousMillis = ledCurrentMillis;
    return true;
  }
  else{
    return false;
  }
}


// analog value of pedometer sensor set each loop
int pedoVal;

// keep the previous pedoVal to detect changes
int lastPedoVal = 0;

// remember the time of the last counted step
int stepFoundTime = 0;

// keep track of time since last found step
int stepElapsedTime = 0;

void updateStepCount(){
  pedoVal = analogRead(pedometerPin);
    
  if (pedoVal != lastPedoVal){
    
    //Serial.println(pedoVal);
    stepElapsedTime = millis() - stepFoundTime;
    if (stepElapsedTime > 100){
      steps++;
    }
    
    stepFoundTime = millis();
    
    //Serial.println(elapsedTime);
    //Serial.println(steps);
  }
  
  lastPedoVal = pedoVal;
}


// arrays for led values, index is led index
int red[ledCount];
int green[ledCount];
int blue[ledCount];

void updateProgressBar(){
  
  float percentComplete = (float)steps / (float)stepGoal;
  float activeLeds = (float) ledCount * percentComplete;
  
  Serial.println(activeLeds);
  
  for(int i=ledCount;i>=0;i--){
    
    if (activeLeds > 0){
      activeLeds -= 1;
      
      red[i] = 0;
      green[i] = 0;
      blue[i] = 200;
    }
    else{
      red[i] = 140;
      green[i] = 80;
      blue[i] = 0;
    }
    
  }
  drawToStrip();
}


int frameLength = 50;
void playCelebration(){
  for(int i = i; i < ledCount; i++){
    
  }
}

void drawToStrip(){
  for(int i=0;i<ledCount;i++){
    strip.setPixelColor(i, strip.Color(red[i], green[i], blue[i]));
  }
  strip.show();
}
