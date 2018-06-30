#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Gotta luv ugly code
#define stripApin 3
#define stripBpin 4
#define stripCpin 5

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel stripA = Adafruit_NeoPixel(60, stripApin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB = Adafruit_NeoPixel(60, stripBpin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripC = Adafruit_NeoPixel(60, stripCpin, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  stripA.begin();
  stripB.begin();
  stripB.begin();
  // Initialize all pixels to 'off'
  stripA.show();
  stripB.show();
  stripB.show();
}

// TODO: Setup button logic
// TODO: Setup other modes based on button
void loop() {
  colorWipe(stripA.Color(255, 0, 0), 50); // Red
  colorWipe(stripA.Color(0, 255, 0), 50); // Green
  colorWipe(stripA.Color(0, 0, 255), 50); // Blue

  theaterChase(stripA.Color(127, 127, 127), 50); // White
  theaterChase(stripB.Color(127, 127, 127), 50); // White
  theaterChase(stripC.Color(127, 127, 127), 50); // White
  theaterChase(stripA.Color(127, 0, 0), 50); // Red
  theaterChase(stripB.Color(127, 0, 0), 50); // Red
  theaterChase(stripC.Color(127, 0, 0), 50); // Red
  theaterChase(stripA.Color(0, 0, 127), 50); // Blue
  theaterChase(stripB.Color(0, 0, 127), 50); // Blue
  theaterChase(stripC.Color(0, 0, 127), 50); // Blue

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<stripA.numPixels(); i++) {
    stripA.setPixelColor(i, c);
    stripA.show();
    delay(wait);
  }
  for(uint16_t i=0; i<stripB.numPixels(); i++) {
    stripB.setPixelColor(i, c);
    stripB.show();
    delay(wait);
  }
  for(uint16_t i=0; i<stripC.numPixels(); i++) {
    stripC.setPixelColor(i, c);
    stripC.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < stripA.numPixels(); i=i+3) {
        stripA.setPixelColor(i+q, c);    //turn every third pixel on
      }
      stripA.show();
      for (uint16_t i=0; i < stripB.numPixels(); i=i+3) {
        stripB.setPixelColor(i+q, c);    //turn every third pixel on
      }
      stripB.show();
      for (uint16_t i=0; i < stripC.numPixels(); i=i+3) {
        stripC.setPixelColor(i+q, c);    //turn every third pixel on
      }
      stripC.show();

      delay(wait);

      for (uint16_t i=0; i < stripA.numPixels(); i=i+3) {
        stripA.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      for (uint16_t i=0; i < stripB.numPixels(); i=i+3) {
        stripB.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      for (uint16_t i=0; i < stripB.numPixels(); i=i+3) {
        stripB.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
