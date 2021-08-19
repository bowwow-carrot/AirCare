#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif
#define PIN        6
#define NUMPIXELS 16
#define DELAYVAL 500

#define green ledOn(0,255,0)
#define red 255,0,0
#define orange 255,128,0
#define yellow 255,255,0

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();

}

void loop() {
  int pm;
  neoPixel(50);
  delay(5000);

}


void neoPixel(int pm){
  pixels.clear();
  green;
  if (pm < 10){
    green;
  }
  else if (pm < 40){
    ledOn(yellow);
  }
  else if (pm < 60){
    ledOn(orange);
  }
  else{
    ledOn(red);
  }
}

void ledOn(int r, int g, int b){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r,g,b));
    pixels.show();   
    delay(DELAYVAL); 
  }
}
