/*

Vixen Lights 3.x - Arduino Generic Serial for Addressable Pixels

Using this code is pretty straight forward, simply hookup your one wire (WS2811 or WS2812) data line to pin 6 of your Arduino
and upload this code.  Make sure you have properly installed the FastLED library from http://fastled.io Once you are done, simply
power your Pixel strips from an external power supply.  Next configure a Generic Serial Controller inside of Vixen Lights 3.x and 
add 3 x pixels for the number of channels.  Configure the Generic Serial Controller to use 115200, 8, none, and 1.  Then create
your element and add "Multiple Items (1 x number of pixels).  Finally select your pixel elements and set them as RGB pixels before
patching them to the controler outputs.  You should now be ready to begin testing.

For a complete tutorial check out blog.huntgang.com

Created   November 8th, 2014
By        Richard Sloan - www.themindfactory.com
And       David Hunt - blog.huntgang.com
Version   1.4

*/


// You must download and install the library from http://fastled.io/ 
#include <FastLED.h>

// Sets the maximum number of LEDs that this code will handle to avoid running out of memory
#define NUM_LEDS 50

// Sets the pin which is used to connect to the LED pixel strip
#define DATA_PIN 3

CRGB leds[NUM_LEDS];


void setup() {
  // Define the speed of the serial port
  Serial.begin(115200);
  // Let the FastLED library know how many pixels we will be addressing
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  pinMode(13,OUTPUT);
}

// Set some counter / temporary storage variables
int cnt = 0;
int state = 0; // 0 - waiting head,
               // 1 - waiting red
               // 2 - waiting green
               // 3 - waiting blue
               // 4 - waiting tail
int newState = 0;
unsigned int num_leds;
unsigned int r, g, b;

void loop() {
  if(Serial.available()){
    int data = Serial.read();
    switch(state){
    case 0: if (data == '<'){
        digitalWrite(13,HIGH);
        newState = 1;
        cnt = 0;
      } else {
        newState = 0;
      }
      break;
    case 1: leds[cnt].g = data;
      newState = 2;
      break;
    case 2: leds[cnt].r = data;
      newState = 3;
      break;
    case 3: leds[cnt].b = data;
      cnt++;
      if(cnt==NUM_LEDS){
        newState = 0;
        digitalWrite(13,LOW);
        FastLED.show();
      } else {
        newState = 1;
      }
      break;
    case 4:  if (data == '>'){
        digitalWrite(13,LOW);
        
      }
      newState = 0;
      break;
    }
    state = newState;
  }
}
