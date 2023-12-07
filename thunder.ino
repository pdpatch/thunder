/*
   d. bodnar - 9-09-2022
   Lightning & thunder for CHP castle
   T O'Neill  03-12-2023
   Changed to use nano
   Could not find DFPlayer library that was used so I used the one from 
   DF Robot. https://github.com/DFRobot/DFRobotDFPlayerMini 
   Had to make TrueRandom and DFRobotDFPlayerMini work with IDE
   Uses ws2811 led strip.

*/
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <TrueRandom.h>   ///https://github.com/sirleech/TrueRandom
// How many internal neopixels do we have? some boards have more than one!
int Pixels = 21;
int NUMPIXELS    =    Pixels;
Adafruit_NeoPixel pixels(NUMPIXELS, 8, NEO_RGB + NEO_KHZ800);
int x = 0;
int howMany = 0;
#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini myDFPlayer;
const int buttonPin1 = 5;  
const int buttonPin2= 6;    // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int buusyPin1 = 20;// buusyPin1 = 20 sound player busy pin
int bsy = 0;
int LEDstripLight1 =23; // WAS 12  pin light string conected to
int sensorPin = 4;    // Audio level samples
int sensorValue = 0;  // variable to store the value coming from the sensor
int buttn = 0;
int whichMP3 = 1;

//***************************************SETUP*************************************
void setup () {
  Serial.begin (9600);
SoftwareSerial softSerial(14, 15); // RX, TX
 softSerial.begin(115200);
 while (!Serial) {
 // Open serial communications and wait for port to open:
    ; // wait for serial port to connect. Needed for native USB port only
  }
#if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
#endif
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(80); // not so bright -- 50 is much brighter
  pixels.updateLength(21); // number of leds in string

  pinMode(buttonPin1, INPUT);
  pinMode(LEDstripLight1, OUTPUT);
  pinMode(buusyPin1, INPUT);
  pinMode(buttonPin2, INPUT);

}

//.......................................LOOP................................................
void loop () {
  Serial.print("The id of mp3 to play is  ");
  whichMP3 = TrueRandom.random(1, 6); // place the number of mp3's as second number
  Serial.println(whichMP3);

  //Serial.println("");
  Serial.println("Waiting for Button Push to start.");
  do {
    buttn = digitalRead(buttonPin1); // pins closest to power pins
  } while (buttn == 0);
  Serial.println("Button Hit");
  myDFPlayer.play(whichMP3);
  delay(100); // add changeable delay based on volume
  do {
    sensorValue = analogRead(sensorPin);
    //    Serial.print(sensorValue);
    //    Serial.print(" ");
    //    if (sensorValue >= 750) {
    ////      Serial.println("large number! ");
    //      digitalWrite(LEDstripLight1, HIGH);
    //    }
    //    if (sensorValue <= 666) {
    //      digitalWrite(LEDstripLight1, LOW);
    //    }
    bsy = digitalRead(buusyPin1);
    //   map(value, fromLow, fromHigh, toLow, toHigh)
    howMany =  map(sensorValue, 555, 800, 0, NUMPIXELS);
    // howMany = sensorValue / 8;
    pixels.updateLength(howMany);
    onPixels();
    delay(30); // was 50
    //    Serial.print(howMany); Serial.println(" Hello!");
    pixels.updateLength(NUMPIXELS);
    offPixels();
  } while (bsy == 0); // zero when sound active

}

//...................................... END LOOP ........................................

void onPixels() {
  //    pixels.updateLength();
  //  pixels.fill(0xFFFFFF); //white
  //    pixels.fill(0x0000FF);// blue
  // pixels.fill(0xFF0000);//red
  if (random(10) <= 3 ) {
    pixels.fill(0xFFFFFF);
  }
  else
    pixels.fill(0x0000FF);
  pixels.show();
}

void offPixels() {
  pixels.updateLength(NUMPIXELS);
  //    pixels.updateLength(NUMPIXELS);

  pixels.fill(0x000000);  // set color to OFF
  pixels.show();

}