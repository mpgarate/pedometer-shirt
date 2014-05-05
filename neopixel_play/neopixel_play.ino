#include <Adafruit_NeoPixel.h>

#define PIN 6


const int ledCount = 3;

int red[ledCount];
int green[ledCount];
int blue[ledCount];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  strip.begin();
  strip.show();
}

void loop(){
  for(int i=0;i<ledCount;i++){
    red[i] = random(127);
    green[i] = random(127);
    blue[i] = random(127);
  }
  
  drawToStrip();
  delay(100);
}

void drawToStrip(){
  for(int i=0;i<ledCount;i++){
    strip.setPixelColor(i, strip.Color(red[i], green[i], blue[i]));
  }
  strip.show();
}
