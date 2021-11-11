//================================== SOURCE CODE ==================================
#include <WiFi.h>
#include <ESP32-RGB64x32MatrixPanel-I2S-DMA.h>
#include <Adafruit_GFX.h>
//#include "Fonts/Font5x7.h"




RGB64x32MatrixPanel_I2S_DMA dmd;


char ssid[] = "xxxxxxxx"; // Nama Wifi Anda
char pass[] = "xxxxxxxx"; // Password Wifi Anda
#define TZ (+7*60*60) //Timezone

void setup() {
  Serial.begin(115200);

  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  configTime(TZ, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp"); 

  //dmd.begin();
  dmd.begin();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    ESP.restart();

  time_t t;
  static time_t last_t;
  struct tm *tm;
  static const char* const wd[7] = {"Minggu","Senin","Selasa","Rabu","Kamis","Jum'at","Sabtu"};

  t = time(NULL);
  if (last_t == t) return;
  last_t = t;
  tm = localtime(&t);
  dmd.clearScreen();
  int jam,menit,detik;
  jam = ("%02d", tm->tm_hour);
  menit = ("%02d", tm->tm_min);
  detik = ("%02d", tm->tm_sec);
  dmd.setTextSize(2);    
  dmd.setTextWrap(false);
  dmd.setTextColor(dmd.color444(0,15,15));
  dmd.setCursor(0, 0);
  dmd.print(jam);
  dmd.setTextColor(dmd.color444(15,0,0));
  dmd.setCursor(20, 0);
  dmd.print(":");
  dmd.setTextColor(dmd.color444(0,15,15));
  dmd.setCursor(28, 0);
  dmd.print(menit);
  dmd.setTextColor(dmd.color444(0,15,15));
  dmd.setCursor(48, 0);
  dmd.setTextColor(dmd.color444(15,0,0));
  dmd.print(":");
  dmd.setTextColor(dmd.color444(0,15,15));
  dmd.setCursor(56, 0);
  dmd.print(detik);
  
  dmd.setTextSize(1);    
  dmd.setCursor(82, 0);
  dmd.setTextColor(dmd.color444(15,15,0));
  dmd.print("DOT MATRIX + ESP32");
  dmd.setCursor(87, 8);
  dmd.setTextColor(dmd.color444(0,15,0));
  dmd.print("www.dickybmz.com");

  dmd.setTextSize(2);    
  dmd.setCursor(18, 18);
  dmd.setTextColor(dmd.color444(15,4,15));
  dmd.print("P5");

  dmd.setCursor(54, 18);
  dmd.setTextColor(dmd.color444(15,0,0));
  dmd.print("R");

  dmd.setCursor(66, 18);
  dmd.setTextColor(dmd.color444(0,15,0));
  dmd.print("G");

  dmd.setCursor(78, 18);
  dmd.setTextColor(dmd.color444(0,0,15));
  dmd.print("B");

  dmd.setCursor(102, 18);
  dmd.setTextColor(dmd.color444(15,0,0));
  dmd.print("3");
  dmd.setCursor(114, 18);
  dmd.setTextColor(dmd.color444(15,10,4));
  dmd.print("2");
  dmd.setCursor(126, 18);
  dmd.setTextColor(dmd.color444(15,15,0));
  dmd.print("x");
  dmd.setCursor(136, 18);
  dmd.setTextColor(dmd.color444(0,15,0));
  dmd.print("1");
  dmd.setCursor(148, 18);
  dmd.setTextColor(dmd.color444(0,15,10));
  dmd.print("9");
  dmd.setCursor(160, 18);
  dmd.setTextColor(dmd.color444(0,15,15));
  dmd.print("2");
  dmd.showDMABuffer();   

}
