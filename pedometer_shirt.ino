#include <Adafruit_NeoPixel.h>

const int pedometerPin = A5;
const int neoPin = 6;

// number of LEDs in the strip
const int ledCount = 10; 

// neopixel LED series
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, neoPin, NEO_GRB + NEO_KHZ800);


void setup(){
  Serial.begin(9600);
  strip.begin();
  strip.show();
}


void loop(){
  
  updateStepCount();
  
  if (elapsedTimeForLed(100)){
    randomizeLeds();
  }
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


// total number of steps counted today
int steps = 0;

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
    stepElapsedTime = millis() - stepFoundTime;
    if (stepElapsedTime > 100){
      steps++;
    }
    
    stepFoundTime = millis();
    
    //Serial.println(elapsedTime);
    Serial.println(steps);
  }
  
  lastPedoVal = pedoVal;
}


// arrays for led values, index is led index
int red[ledCount];
int green[ledCount];
int blue[ledCount];

void randomizeLeds(){
  for(int i=0;i<ledCount;i++){
    red[i] = random(127);
    green[i] = random(127);
    blue[i] = random(127);
  }
  
  drawToStrip();
}

void drawToStrip(){
  for(int i=0;i<ledCount;i++){
    strip.setPixelColor(i, strip.Color(red[i], green[i], blue[i]));
  }
  strip.show();
}
