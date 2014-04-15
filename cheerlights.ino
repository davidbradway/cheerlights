#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS 8
#define NUM_COLORS 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);  //change the first digit to add more lights
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

struct RGB{
  byte r;
  byte g;
  byte b;
  String name;
};

//Colors RGB (red, green, blue) values and name
const RGB color[NUM_COLORS] = {
  {255,   0,   0, "red"},
  {  0, 255,   0, "green"},
  {  0,   0, 255, "blue"},
  {102,  51, 204, "purple"},
  {  0, 255, 255, "cyan"},
  {255,   0, 255, "magenta"},
  {255, 255,   0, "yellow"},
  {255, 153,   0, "orange"},
  {255, 255, 255, "white"},
  {255, 244, 229, "warmwhite"},
  {  0,   0,   0, "black"},
  {  0,   0,   0, "off"}};
                    
void setup() {
  //initialize all pixels to off
  strip.begin();
  strip.show();
  
  // Setup Serial
  Serial.begin(9600);
  delay(100);
  Serial.flush();
  delay(100);
  
  // Set initial state
  char start[32] = "magenta";
  checkColors(start, 50);
}

void loop() {
  // Clear every time through the loop
  char stringIn[32] = "";

  // Listen to serial commands
  if(Serial.available() > 0) {
    delay(100);
    
    char charIn = 0;
    byte i = 0;
    while(Serial.available()) {
      charIn = Serial.read();
      stringIn[i] = charIn;
      i += 1;
    }
    
    // Echo Received Commands on the Serial Monitor
    Serial.println("CheerLight Command Received: " + String(stringIn));
    delay(200);
    checkColors(stringIn, 50);
  }
} // End loop

void checkColors(char string[], uint8_t waitms) {
  for (int i=0; i<NUM_COLORS; i++){
    if (color[i].name.equalsIgnoreCase(String(string))) { 
      // Currently it echos the color back to serial for debugging
      Serial.println(color[i].name);
      delay(200);
      // Send matching commands LED
      colorWipe(strip.Color(color[i].r,color[i].g,color[i].b), waitms);
      return;
    }
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
