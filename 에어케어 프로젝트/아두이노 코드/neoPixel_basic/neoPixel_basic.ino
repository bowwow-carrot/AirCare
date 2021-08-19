#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif
#define PIN       14
#define NUMPIXELS 30
#define DELAYVAL 500

void ledOn(int r, int g, int b);
#define green       ledOn(0,255,0)
#define red         ledOn(255,0,0)
#define orange      ledOn(255,128,0)
#define yellow      ledOn(255,255,0)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();

}

void loop() {
  int pm;
  neoPixel(70);
  delay(5000);
}


void neoPixel(int pm){
  pixels.clear();
  green;
  if (pm < 10){
    green;
  }
  else if (pm < 40){
    yellow;
  }
  else if (pm < 60){
    orange;
  }
  else{
    red;
  }
}

void ledOn(int r, int g, int b){
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r,g,b));
    pixels.show();   
    delay(DELAYVAL); 
  }
}
