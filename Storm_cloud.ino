#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//define the pin connect with led
#define led 6

//define the number of led
#define NUMPIXELS 30

//define the pin of heatsensor
#define sensor 3

//define the pin of dfplayer
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, led, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  
  pinMode(sensor, INPUT);
  pinMode(13, OUTPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(15);
  myDFPlayer.enableLoop();
  
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int SensorState = digitalRead(sensor);
  if(SensorState == 1){
    light_storm();
    digitalWrite(13, HIGH);
    myDFPlayer.play(1);
    delay(6000);
  }
  else{
    digitalWrite(13, LOW);
    myDFPlayer.pause();
    
  }
  delay(200);
}


void light_led(int r, int g, int b){
  for(int i = 0; i < NUMPIXELS; i++){

    //contral the color of led by rgb value from 0,0,0 to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r,g,b));

    pixels.show();

    //delay the display
    //delay(100);
  }
}

void light_storm(){
  light_led(255, 255, 255);
  delay(50);
  light_led(0, 0, 0);
  delay(100);
  light_led(255, 255, 255);
  delay(50);
  light_led(0, 0, 0);
}

