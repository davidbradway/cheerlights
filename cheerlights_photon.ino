// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
#include <MQTT.h>

#define PIXEL_COUNT 689
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

const long channelID = 1417;
String subscribeTopic = "channels/" + String(channelID) + "/subscribe/fields/field1";
String MQTTAPIKey = "XXXXXXXXXXXXXXXX";

void callback(char* topic, byte* payload, unsigned int length);

MQTT client("mqtt.thingspeak.com", 1883, callback);

// This function processes the messages relayed by the MQTT broker
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1]; // Leave an extra space to null terminate the string.
    memcpy(p, payload, length);
    p[length] = NULL;  // Terminate the string.

    if (!strncmp(p, "red", 3)){
        colorWipe(strip.Color(255, 0, 0), 50);
    }
    else if (!strncmp(p, "green", 5)){
        colorWipe(strip.Color(0, 255, 0), 50);
    }
    else if (!strncmp(p, "blue", 4)){
        colorWipe(strip.Color(0, 0, 255), 50);
    }
    else if(!strncmp(p, "yellow", 6)){
        colorWipe(strip.Color(255, 255, 0), 50);
    }
    else if(!strncmp(p, "orange", 6)){
        colorWipe(strip.Color(255, 165, 0), 50);
    }
    else if(!strncmp(p, "magenta", 7)){
        colorWipe(strip.Color(255, 0, 255), 50);
    }
    else if(!strncmp(p, "cyan", 4)){
        colorWipe(strip.Color(0, 255, 255), 50);
      }
    else if(!strncmp(p, "white", 5)){
        colorWipe(strip.Color(255, 255, 255), 50);
    }
    else if(!strncmp(p, "oldlace", 7)){
        colorWipe(strip.Color(253, 245, 230), 50);
    }
    else if(!strncmp(p, "purple", 6)){
        colorWipe(strip.Color(128, 0, 128), 50);
    }
    else if(!strncmp(p, "pink", 4)){
        colorWipe(strip.Color(255, 192, 203), 50);
    }
    else{
        colorWipe(strip.Color(255, 255, 255), 50);
    }     
}

void setup() {
    strip.begin();
    strip.show();
  
    // Connect to the server
    subscribeMQTT();
}

void loop() {
    if (client.isConnected()){
        client.loop();
    }
    else{
        subscribeMQTT();
    }

    int timeHour=Time.hour();
    if ( ( timeHour > 23 ) or ( timeHour < 7 ) ){
        Particle.publish( "Sleep" );
        System.sleep( SLEEP_MODE_DEEP , 7200 );
    }
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    theaterChase(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    theaterChase(strip.Color(0, 255, 0), 50); // Green
}

void subscribeMQTT(){
  if (!client.isConnected()) {
    client.connect( " PhotonSubscribeXX" , "Username" , MQTTAPIKey , NULL , MQTT::QOS0 , 0 , NULL , true );
    Particle.publish( "Connect" );
    delay( 1000 );
    if ( client.isConnected()){     
        client.subscribe( subscribeTopic );
        Particle.publish( "Subscribe" );
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
        for (int q=0; q < 30; q++) {
            for (int i=0; i < strip.numPixels(); i=i+30) {
                strip.setPixelColor(i+q, c);    //turn every thirtieth pixel on
            }
            strip.show();
            delay(wait);

            for (int i=0; i < strip.numPixels(); i=i+30) {
                strip.setPixelColor(i+q, 0);        //turn every thirtieth pixel off
            }
        }
    }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}
