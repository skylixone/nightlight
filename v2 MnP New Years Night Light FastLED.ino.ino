#include <ezButton.h>
#include <FastLED.h> 
#define NUM_LEDS 	80
#define DATA_PIN 	6 // connection w
#define LED_TYPE 	WS2811
#define POT_PIN 	5

ezButton button(7);
ezButton buttonCold(2);

CRGBArray<NUM_LEDS> leds;
CRGBSet partA(leds(0,80)); // might not be necessary

void setup() {
	button.setDebounceTime(50); // set debounce time to 50 milliseconds
	buttonCold.setDebounceTime(50); // set debounce time to 50 milliseconds
	Serial.begin(9600);

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // 
	FastLED.show();

}
void loop() {
	// fucking pot brightness 
	int val = analogRead(POT_PIN); 										// read value from pot
	int brightnessValue = map(val, 0, 1023, 0, 255); 	// map to 0-255 range

// call the loop() function first
	button.loop();                                    
	buttonCold.loop();

// check button states to restart with regard for switch on power loss
	button.getState();
	buttonCold.getState();

// not sure if the one here or the one at the end actually works
	FastLED.setBrightness(brightnessValue);

// switch left for warm
	if(button.isPressed()) {
		Serial.println("The button is pressed");
		leds = CHSV( 22, 255, 255);  
	}

	if(button.isReleased()) {
		Serial.println("The button is depressed");
		leds = CRGB::Black;
	}


// switch right for cold
 if(buttonCold.isPressed()) {
		leds = CHSV( 128, 255, 255);  
		Serial.println("The button_c is pressed");
	}

	if(buttonCold.isReleased()) {
		leds = CRGB::Black;
		Serial.println("The button_c is depressed");
		}

FastLED.setBrightness(brightnessValue);
FastLED.show(); // update leds
}
