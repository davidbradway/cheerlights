#define NUM_COLORS 12

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
  // Set initial state
  char start[32] = "magenta";
  checkColors(start);
}

void loop() {
  // Clear every time through the loop
  char stringIn[32] = "";

    checkColors(stringIn);
} // End loop

void checkColors(char string[]) {
  uint8_t waitms = 50;
  for (int i=0; i<NUM_COLORS; i++){
    if (color[i].name.equalsIgnoreCase(String(string))) { 
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
