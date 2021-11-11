 
/**
 * Author:    UseMyTools.Net
 * Created:   2021.01.20
 *
 * (c) Copyright by UseMyTools.Net.
 *  MIT license
 *
 **/

#include <Adafruit_GFX.h>
/*
 * Adafruit_GFX Core graphics library
 * Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
 * for Adafruit Industries.
 *  BSD license, all text above must be included in any redistribution.
*/

/*
 * code snippet from Time_Message_ESP8266_Matrix-P4
 * https://arduino-projects-free.blogspot.com/2020/08/time-message-esp8266-matrix-p4-weather.html
 *
 */


#include <RGBmatrixPanel.h> // Hardware-specific library
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/TomThumb.h>
#include <kongtext4pt7b.h>

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr


#define CLK 11   // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define triggerGYRO 13




// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
//RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true, 64);



uint16_t myRED = matrix.Color333(7,0,0);
uint16_t myGREEN = matrix.Color333(0,7,0);
uint16_t myBLUE = matrix.Color333(0,0,7);
uint16_t myWHITE = matrix.Color333(7, 7,7);
//uint16_t myYELLOW = matrix.Color333(7,7,0);
//uint16_t myCYAN = matrix.Color333(0,7,7);
//uint16_t myMAGENTA = matrix.Color333(7,0,7);
//uint16_t myShadow = matrix.Color333(4,0,7);
//uint16_t myROSE = matrix.Color333(7,0,4);
//uint16_t myBLACK = matrix.Color333(0,0,0);
//uint16_t myCOLORS[9] = {myRED, myGREEN, myWHITE, myMAGENTA, myBLUE, myYELLOW, myCYAN, myShadow, myROSE};


const char str[] PROGMEM = "LATITUDE:6.8909  ";
const char str1[] PROGMEM = "LONGITUDE:104.8909";
const char str2[] PROGMEM = "HEADING : 180.4";
//int    textX   = matrix.width(),

boolean parsing=false, parsingGPS=false, parsing_gyro=false;
String s_heading;
float f_heading=0;
String dataku;
int textX1 = 14;
int textMin1 = sizeof(str1) * -6;
int    textX   = 14,

       //textMin = sizeof(str) * -12,
       textMin = sizeof(str) * -6,
        
       hue     = 0;
int8_t ball[3][4] = {
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 }
};
static const uint16_t PROGMEM ballcolor[3] = {
  0x0080, // Green=1
  0x0002, // Blue=1
  0x1000  // Red=1
};

  void setup() {
  pinMode(triggerGYRO, OUTPUT);
  digitalWrite(triggerGYRO, LOW);
  Serial.begin(4800); //opens serial port, sets data rate to 115200 bps
  Serial1.begin(4800);
 // Serial2.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(1);

}

void hdt(){
  
  matrix.setCursor(28,12);
  matrix.setTextColor(myWHITE);
  matrix.setFont();
  matrix.print(f_heading);
}

void lat_long(){

  matrix.setCursor(18,1);
  matrix.setTextColor(myWHITE);
  matrix.setFont();
  matrix.print(f_heading);




  
}

String WaitForInputGyro(){
  while(!Serial1.available()){}
  return Serial1.readStringUntil('\n');
}
 

void loop() {

    
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    digitalWrite(triggerGYRO, LOW);
    delay(250);
    digitalWrite(triggerGYRO, HIGH);
    s_heading = WaitForInputGyro();
    f_heading = s_heading.toFloat();
    /* Nilai Heading */
    matrix.setCursor(4,12);
    matrix.setFont();
    matrix.setTextColor(myWHITE);
    matrix.print("HDG:");
    hdt();
    /* Nilai Latitude */
    matrix.setCursor(1,1);
    matrix.setTextColor(myWHITE);
    matrix.setFont();
    matrix.print("LT:");
    lat_long();
    /* Nilai Longitude */
    matrix.setCursor(1,22);
    matrix.setTextColor(myWHITE);
    matrix.setFont();
    matrix.print("LG:");   
    matrix.setCursor(18,22);
    matrix.setTextColor(myWHITE);
    matrix.setFont();
    matrix.print(f_heading);     
    matrix.swapBuffers(false);

  

}
