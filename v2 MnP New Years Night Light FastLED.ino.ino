#include <ezButton.h>
#include <FastLED.h> 
  #define NUM_LEDS 80
  #define DATA_PIN 6 // connection w
#define LED_TYPE    WS2811

ezButton button(7);
ezButton buttonCold(2);

CRGBArray<NUM_LEDS> leds;
CRGBSet partA(leds(0,80));


void setup() {

  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  buttonCold.setDebounceTime(50); // set debounce time to 50 milliseconds
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // 
   FastLED.show();

}


void loop() {

// fucking pot brightness
int val = analogRead(5); // read value from pot
int brightnessValue = map(val, 0, 1023, 0, 255); // map to 0-255 range



button.loop(); // MUST call the loop() function first
buttonCold.loop();
button.getState();
buttonCold.getState();
FastLED.setBrightness(brightnessValue);
  if(button.isPressed()) {
    Serial.println("The button is pressed");
    leds = CHSV( 22, 255, 255);  
  }

  if(button.isReleased()) {
    Serial.println("The button is depressed");
    leds = CRGB::Black;
  }

 if(buttonCold.isPressed()) {
    leds = CHSV( 128, 255, 255);  
    Serial.println("The button_c is pressed");
  }

  if(buttonCold.isReleased()) {
    leds = CRGB::Black;
    Serial.println("The button_c is depressed");
    }


FastLED.setBrightness(brightnessValue);
FastLED.show();

 

}
