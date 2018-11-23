#include <FastLED.h>

#define LED_PIN     1
#define NUM_LEDS    50
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define BUT1 PB0
#define BUT2 PB2
#define LED PB1


int but1State = 0;
int but2State = 0;
int staticLights = 0;
int randomLights = 0;

CRGB leds[NUM_LEDS];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = PartyColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
  but1State = digitalRead(BUT1);
  but2State = digitalRead(BUT2);

  static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    if( but1State == LOW) {   
    randomLights = 1;
    }
    
    else if( but2State == LOW) {     
      randomLights = 0;
      staticLights = staticLights + 1;
      if (staticLights > 3) {staticLights = 0;}
      
    }

    if (randomLights = 1){
      FillLEDsFromPaletteColors( startIndex);
    }
    else if(randomLights = 0){
      switch (staticLights){
        case 0: 
          currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND;
          break;
        case 1:
          currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;
          break;
        case 2:
          currentPalette = CloudColors_p;           currentBlending = LINEARBLEND;
          break;
        case 3:
          currentPalette = PartyColors_p;           currentBlending = LINEARBLEND;
          break;
        
      }
    }
    
  
    FastLED.show();
    delay(100);// / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 16;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand ) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
   //    if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
       //if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
       //if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
       //if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
       //if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
       //if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
   //    if( secondHand == 30)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
   //    if( secondHand == 40)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
       //if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
       //if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
    
      
    
}
