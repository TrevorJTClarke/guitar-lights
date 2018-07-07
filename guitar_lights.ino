#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

/**
 * NOTE:S

 Strip A - Near Bridge
    - 22 total [3,8,8,3]

 Strip B - Middle
    - 34 total [4,13,13,4]

 Strip C - Near Neck
    - 24 total [8,9,3,4]

  Effects Catalog
  - 1. White Twinkle (TODO)
  - 2. Yellow Fades (TODO)
  - 3. Yellow Flash (TODO)
  - 4. Blue Shock (Flash, fade twinkle) (TODO)
  - 5. Wave, material design color wipe, match strum (TODO)
  - 6. Radar (Red or Green) (TODO)

  Colors:
  - White: 255, 255, 255
  - Yellow: 255, 127, 0
  - Red: 255, 0, 0
  - Green: 0, 255, 0
  - Blue: 0, 0, 255

 */

// Gotta luv ugly code
const int stripApin = 3;
const int stripBpin = 4;
const int stripCpin = 5;
const int ledPin = 13;
const int typeBtn = 22;
int state = 0;
bool oldState = HIGH;

// Light Strip Segments
int Lights[][4] = {
  {3, 8, 8, 3},
  {4, 13, 13, 4},
  {8, 9, 3, 4}
};


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel stripA = Adafruit_NeoPixel(24, stripApin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB = Adafruit_NeoPixel(34, stripBpin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripC = Adafruit_NeoPixel(22, stripCpin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(typeBtn, INPUT_PULLUP);

  stripA.setBrightness(255);
  stripB.setBrightness(255);
  stripC.setBrightness(255);
  stripA.begin();
  stripB.begin();
  stripC.begin();
  // Initialize all pixels to 'off'
  stripA.show();
  stripB.show();
  stripC.show();

  // Init Flash
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

// Effect modes are based on button press
void loop() {
  bool newState = digitalRead(typeBtn);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(typeBtn);
    if (newState == LOW) {
      state++;
      if (state > 6) state=0;
    }
  }

  // Set the last button state to the old state.
  oldState = newState;
  executeLights(state);
}

// TODO: TEst!!!!
void clearAll() {
  stripA.clear();
  stripB.clear();
  stripC.clear();
}

// -------------------------------------------
// Effects
// -------------------------------------------

// White Twinkle
void whiteTwinkle(uint8_t wait) {
  // White
  uint32_t c = stripA.Color(255, 255, 255);

  for (int j=0; j<6; j++) {  //do 6 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < stripA.numPixels(); i=i+3) {
        stripA.setPixelColor(i+q, c);    //turn every third pixel on
      }
      for (uint16_t i=0; i < stripB.numPixels(); i=i+3) {
        stripB.setPixelColor(i+q, c);    //turn every third pixel on
      }
      for (uint16_t i=0; i < stripC.numPixels(); i=i+3) {
        stripC.setPixelColor(i+q, c);    //turn every third pixel on
      }
      stripA.show();
      stripB.show();
      stripC.show();

      delay(wait);

      for (uint16_t i=0; i < stripA.numPixels(); i=i+3) {
        stripA.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      for (uint16_t i=0; i < stripB.numPixels(); i=i+3) {
        stripB.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      for (uint16_t i=0; i < stripC.numPixels(); i=i+3) {
        stripC.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      stripA.show();
      stripB.show();
      stripC.show();
    }
  }
}

void loopStripA(uint16_t c1) {
  for (uint16_t i = 0; i < stripA.numPixels(); i++) {
    stripA.setPixelColor(i, c1);
  }

  stripA.show();
}

void loopStripB(uint16_t c1) {
  for (uint16_t i = 0; i < stripB.numPixels(); i++) {
    stripB.setPixelColor(i, c1);
  }

  stripB.show();
}

void loopStripC(uint16_t c1) {
  for (uint16_t i = 0; i < stripC.numPixels(); i++) {
    stripC.setPixelColor(i, c1);
  }

  stripC.show();
}

// void loopStripA(uint16_t c1, uint16_t c2, uint16_t wait) {
//   uint16_t a1 = Lights[2][0];
//   uint16_t a2 = Lights[2][1];
//   uint16_t a3 = Lights[2][2];
//   uint16_t a4 = Lights[2][3];
//
//   // A, Segment 3
//   for (uint16_t i = a2; i < a1 + a2 + a3; i++) {
//     stripA.setPixelColor(i, c1);
//   }
//   // A, Segment 4
//   for (uint16_t i = a3; i < a1 + a2 + a3 + a4; i++) {
//     stripA.setPixelColor(i, c1);
//   }
//   // A, Segment 1
//   for (uint8_t i = 0; i < a1; i++) {
//     stripA.setPixelColor(i, c2);
//   }
//   // A, Segment 2
//   for (uint8_t i = a1; i < a1 + a2; i++) {
//     stripA.setPixelColor(i, c2);
//   }
//
//   stripA.show();
// }
//
// void loopStripB(uint16_t c1, uint16_t c2, uint16_t wait) {
//   uint16_t b1 = Lights[1][0];
//   uint16_t b2 = Lights[1][1];
//   uint16_t b3 = Lights[1][2];
//   uint16_t b4 = Lights[1][3];
//
//   // A, Segment 1
//   for (uint8_t i = 0; i < b1; i++) {
//     stripB.setPixelColor(i, c1);
//   }
//   // A, Segment 4
//   for (uint16_t i = b3; i < b1 + b2 + b3 + b4; i++) {
//     stripB.setPixelColor(i, c1);
//   }
//   // A, Segment 2
//   for (uint8_t i = b1; i < b1 + b2; i++) {
//     stripB.setPixelColor(i, c2);
//   }
//   // B, Segment 3
//   for (uint16_t i = b2; i < b1 + b2 + b3; i++) {
//     stripB.setPixelColor(i, c2);
//   }
//
//   stripB.show();
// }
//
// void loopStripC(uint16_t a1, uint16_t a2, uint16_t wait) {
//   uint16_t c1 = Lights[0][0];
//   uint16_t c2 = Lights[0][1];
//   uint16_t c3 = Lights[0][2];
//   uint16_t c4 = Lights[0][3];
//
//   // A, Segment 2
//   for (uint8_t i = c1; i < c1 + c2; i++) {
//     stripC.setPixelColor(i, a1);
//   }
//   // A, Segment 3
//   for (uint16_t i = c1 + c2; i < c1 + c2 + c3; i++) {
//     stripC.setPixelColor(i, a1);
//   }
//   // A, Segment 1
//   for (uint8_t i = 0; i < c1; i++) {
//     stripC.setPixelColor(i, a2);
//   }
//   // A, Segment 4
//   for (uint16_t i = c1 + c2 + c3; i < c1 + c2 + c3 + c4; i++) {
//     stripC.setPixelColor(i, a2);
//   }
//
//   stripC.show();
// }

// Yellow Fades
void yellowFades(uint8_t wait) {
  // Yellow
  // 255, 127, 0

  // Fade the strip in order
  float in;
  // int b, c, d, e, f, g;
  int b, c, d;
  for (in = 4.712; in < 10.995; in = in + 0.001) {
    b = sin(in) * 40 + 40;
    c = sin(in - 1) * 127.5 + 127.5;
    d = sin(in - 2) * 127.5 + 127.5;
    // e = sin(in - 3) * 127.5 + 127.5;
    // f = sin(in - 4) * 127.5 + 127.5;
    // g = sin(in - 5) * 127.5 + 127.5;

    // uint16_t sa1 = stripA.Color(b, b/2, 0);
    // uint16_t sa2 = stripA.Color(c, c/2, 0);
    // uint16_t sb1 = stripA.Color(d, d/2, 0);
    // uint16_t sb2 = stripA.Color(e, e/2, 0);
    // uint16_t sc1 = stripA.Color(f, f/2, 0);
    // uint16_t sc2 = stripA.Color(g, g/2, 0);

    // loopStripA(sa1, sa2, wait);
    // loopStripB(sb1, sb2, wait);
    // loopStripC(sc1, sc2, wait);

    uint16_t sa1 = stripA.Color(b, b/2, 0);
    uint16_t sb1 = stripA.Color(c, c/2, 0);
    uint16_t sc1 = stripA.Color(d, d/2, 0);
    loopStripA(sa1);
    loopStripB(sb1);
    loopStripC(sc1);

    delayMicroseconds(wait);
  }
}

// -------------------------------------------
// Switcher
// -------------------------------------------

void executeLights(int s) {
  switch (s) {
    // case 2: whiteTwinkle(50);
    //   break;
    case 1: yellowFades(1);
      break;
    // case 6: rainbowCycle(50);
    //   break;
    default:
      clearAll();
      break;
  }
}
