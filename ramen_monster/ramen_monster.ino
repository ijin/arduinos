#include <Adafruit_NeoPixel.h>
#include <math.h>
//#include "ResetButton.h"

#define PIN            6
#define NUMPIXELS      180
#define BATCH          9
#define SWITCH_PIN     10
#define BREATHE        1


// sda -> green -> A4
// scl -> blue -> A5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delay_cnt = 120; //3000/256 = 12
int mySwitch;

void setup() 
{
  strip.begin();
  strip.show();
  pinMode (SWITCH_PIN, INPUT_PULLUP);

  //SetupResetButton();
  Serial.begin(9600);
  delay(10);
  Serial.println();/*
  Serial.print("Reset.sketchMode = "); Serial.println(gResetSafeMemory.sketchMode);
  Serial.print("Reset.pushButton = "); Serial.println(gResetSafeMemory.pushButton);
  Serial.print("Reset.resetCount = "); Serial.println(gResetSafeMemory.resetCount);
  Serial.print("Reset.uptimePrev = "); Serial.println(gResetSafeMemory.uptimePrev);
  */
}

void loop() {
  //breathe();
  //rainbow(20);
  rainbowCycle(1);
  //fade();
  /*
  mySwitch = gResetSafeMemory.resetCount % 2;
  Serial.println(mySwitch);
  if (mySwitch == BREATHE) {
    Serial.println("breathe");
    breathe();
  } else {
    Serial.println("nine");
    nine();
  }*/
}

void fade() {
  fade_in();
  Serial.println("waiting...\n");
  delay(1000);
  fade_out();
  Serial.println("waiting...\n");
  delay(1000);
}


void breathe() {
  brighten();
  Serial.println("waiting...\n");
  delay(1000);
  darken();
  Serial.println("waiting...\n");
  delay(1000);
}

void nine() {
  for (int i = 0; i <= ceil(NUMPIXELS/BATCH); i++) {
    //if (digitalRead(SWITCH_PIN) == BREATHE) return;
    //if ((gResetSafeMemory.resetCount % 2) == BREATHE) return;
    int pixelStart = (i*BATCH);
    int pixelEnd = pixelStart + BATCH - 1;
    String s = String(); 
    Serial.println(s+"setting pixel from " + pixelStart + " to " + pixelEnd);
    for (int j = pixelStart; j <= pixelEnd; j++) {
      //Serial.println(j);
      strip.setBrightness(255);
      strip.setPixelColor(j, strip.Color(255, 255, 255));
    }
    strip.show();
    delay(1000);
    color(255, 255, 255, 0);
    strip.show();
    delay(250);
  }
}


void fade_in() {
  for (int i = 0; i <= 12; i++) {
    //color(0, 203, 152, 16); // turquoise
    // to color(191, 255, 0, i); // light green
    int r = i*16;
    int g = ceil(152+i*8.6);
    int b = ceil(16-i*1.3);
    color(r, g, b, 16);
    strip.show();
    delay(delay_cnt);
  }
}
void fade_out() {
  for (int i = 0; i <= 12; i++) {
    //color(191, 255, 0, i); // light green
    //to color(0, 203, 152, 16); // turquoise
    int r = 191-i*16;
    int g = ceil(255-i*9);
    int b = ceil(i*1.3);
    color(r, g, b, 16);
    
    strip.show();
    delay(delay_cnt);
  }
}



// 0 to 255
void brighten() {
  for (int i = 4; i <= 16; i++) {
    //if (digitalRead(SWITCH_PIN) != BREATHE) return;
    //if ((gResetSafeMemory.resetCount %2) != BREATHE) return;
    //color(255, 255, 255, i);
    //color(127, 0, 255, i); // white purple
    //color(191, 255, 0, i); // light green
    //color(0, 203, 152, i); // turquoise
    color(0, 203, 101, i); // turquoise green
    strip.show();
    //Serial.println(i);
    delay(delay_cnt);
  }
}

// 255 to 0
void darken() {
  for (int i = 16; i >= 4; i--) {
    //if (digitalRead(SWITCH_PIN) != BREATHE) return;
    //if ((gResetSafeMemory.resetCount %2) != BREATHE) return;
    //color(255, 255, 255, i);
    //color(127, 0, 255, i); // white purple
   // color(191, 255, 0, i); // light green
    //color(0, 203, 152, i); // turquoise
    color(0, 203, 101, i); // turquoise green
    strip.show();
    //Serial.println(i);
    delay(delay_cnt);
  }
}

void white() {
  strip.Color(255, 255, 255);
}

void color(int cred, int cgreen, int cblue, int brightness) {
  strip.setBrightness(brightness);
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(cred, cgreen, cblue));
  }
}

//-----------------------
void rainbow(uint8_t wait) {
  uint16_t i, j;
  strip.setBrightness(16);
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  strip.setBrightness(16);
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
