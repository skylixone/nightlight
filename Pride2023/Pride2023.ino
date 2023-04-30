// gay night light for gay homosexuals 2023 (now with encoder support!)
#include <FastLED.h>
#include <EncoderButton.h>

#define DATA_PIN 6
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 160
#define BRIGHTNESS 5
#define REFRESH_RATE

CRGB leds[NUM_LEDS];
EncoderButton eb1(12, 11, 13); // can be wrong tho, try juggling em around, the pin numbers order is:: clockwise, ccw, encoder button

int brightnessValue = eb1.position(); // self-sexplanatory
uint8_t brightnessDisplayed = ease8InOutQuad(brightnessValue);

// function for encoder click 
void onEb1Clicked(EncoderButton& eb) {
  Serial.print("eb1 clickCount: ");
  Serial.println(eb.clickCount());
}

// function for encoder rotation 
void onEb1Encoder(EncoderButton& eb1) {
  Serial.print("eb1 incremented by: ");
  Serial.println(eb1.increment());
  Serial.print("eb1 position is: ");
  Serial.println(eb1.position());
}

void setup() {
  delay(1000);  // 1 second delay for sanity

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
  .setCorrection(TypicalLEDStrip)
  .setDither(BRIGHTNESS < 255);

  //encoder events functions fuckery
  eb1.setClickHandler(onEb1Clicked);
  eb1.setEncoderHandler(onEb1Encoder);
}


void loop() {
  eb1.update(); // gotta read the encoder first
  pride(); // run in the forest, have fun, be gay
  FastLED.setMaxRefreshRate(24, true); // sum of that cinematic goodness, 60 and 120 are fun too. Uncomment the 
                                       // blur function if you want to go sub-16 fps for funk
  FastLED.show();
}


// This function draws rainbows with an ever-changing,
// widely-varying set of parameters, proudly stolen from much smarter ppl
void pride() {
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88(87, 220, 250);
  uint8_t brightdepth = beatsin88(341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;  //gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis;
  sLastMillis = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88(400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16 += brightnessthetainc16;
    uint16_t b16 = sin16(brightnesstheta16) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    CRGB newcolor = CHSV(hue8, sat8, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS - 1) - pixelnumber;

    nblend(leds[pixelnumber], newcolor, 64);
  }
}
