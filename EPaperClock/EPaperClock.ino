#include <WiFi.h>                               // WiFi
#include <GxEPD2_BW.h>                          // e-paper
#include <Fonts/FreeSans9pt7b.h>                // e-paper
//#include <Fonts/FreeSansBold24pt7b.h>           // e-paper
#include "GxEPD2_display_selection_new_style.h" // e-paper
//#include "Monster_AG24pt7b.h"
#include "AARDV40pt7b.h"
#include "AARDV12pt7b.h"

#define TIME_FONT &AARDV40pt7b
#define DATE_FONT &AARDV12pt7b
#define INFO_FONT &FreeSans9pt7b

// 24x20 縦に７文字
const unsigned char weekKanji[] PROGMEM = {
0x00, 0x00, 0x00, 
0x07, 0xff, 0xe0, 
0x07, 0xff, 0xf0, 
0x07, 0xff, 0xf0, 
0x07, 0x80, 0x70, 
0x07, 0x00, 0x70, 
0x07, 0x00, 0x78, 
0x07, 0x00, 0x78, 
0x07, 0x00, 0xf8, 
0x07, 0xff, 0xf8, 
0x07, 0xff, 0xf8, 
0x0f, 0xe0, 0x78, 
0x0f, 0x00, 0x78, 
0x0f, 0x00, 0x78,
0x0f, 0x00, 0x78,
0x0f, 0x00, 0x78,
0x0f, 0x7f, 0xf8,
0x0f, 0xff, 0xf8,
0x0f, 0xff, 0xf8,
0x00, 0x00, 0x00,
0x00, 0x00, 0x00,
0x03, 0xff, 0xe0,
0x03, 0xff, 0xf0,
0x03, 0xff, 0xf0,
0x07, 0x80, 0x70,
0x07, 0x80, 0x70,
0x07, 0x80, 0xf8,
0x07, 0xff, 0xf8,
0x07, 0xff, 0xf8, 
0x07, 0xfe, 0xf8,
0x07, 0x00, 0x78,
0x07, 0x83, 0xf8,
0x07, 0xff, 0xf8,
0x07, 0xff, 0xf8,
0x0f, 0xe0, 0x78,
0x0f, 0x00, 0x78,
0x0f, 0x00, 0x78,
0x0f, 0x03, 0xf8,
0x0f, 0x03, 0xf0,
0x00, 0x00, 0x00,
0x00, 0x0f, 0x00,
0x00, 0x0f, 0x00, 
0x00, 0x0f, 0x00,
0x0e, 0x1e, 0x18,
0x1e, 0x1e, 0x3c,
0x1e, 0x3c, 0x7c,
0x1e, 0x3c, 0x78,
0x1e, 0x7c, 0xf8,
0x0e, 0x79, 0xf0,
0x0e, 0xfd, 0xe0,
0x00, 0xfe, 0x60,
0x01, 0xff, 0x00,
0x03, 0xff, 0xc0,
0x03, 0xc7, 0xe0, 
0x07, 0xc3, 0xf0,
0x0f, 0x81, 0xf8,
0x1f, 0x00, 0xfc,
0x1f, 0x00, 0x3c,
0x0e, 0x00, 0x18,
0x00, 0x00, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x10,
0x00, 0x1c, 0x38,
0x1f, 0x9e, 0x7c,
0x1f, 0xdf, 0xf8,
0x1f, 0xdf, 0xf0,
0x1b, 0xdf, 0xe0,
0x03, 0xdf, 0xc0,
0x07, 0x9f, 0xe0,
0x07, 0x9d, 0xf0,
0x0f, 0x1c, 0xf8,
0x1e, 0x1c, 0x7c,
0x1e, 0x1c, 0x3c,
0x0c, 0x1c, 0x1c,
0x00, 0xfc, 0x08,
0x00, 0xfc, 0x00,
0x00, 0x7c, 0x00, 
0x00, 0x00, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x07, 0xff, 0xfc,
0x1f, 0xff, 0xfc,
0x1f, 0xff, 0xfc,
0x1c, 0xff, 0x00,
0x00, 0xff, 0x80,
0x01, 0xff, 0xc0,
0x03, 0xff, 0xe0,
0x07, 0xbd, 0xf0, 
0x0f, 0xbc, 0xf8,
0x1f, 0x3c, 0x7c,
0x1e, 0x3c, 0x3c,
0x1c, 0x3c, 0x1c,
0x08, 0x3c, 0x08,
0x00, 0x3c, 0x00,
0x00, 0x3c, 0x00,
0x00, 0x3c, 0x00,
0x00, 0x00, 0x00, 
0x00, 0x3e, 0x00,
0x00, 0xff, 0x00,
0x01, 0xff, 0xc0,
0x03, 0xe3, 0xe0,
0x07, 0xc1, 0xf0,
0x0f, 0x80, 0xf8,
0x1f, 0xff, 0xfc,
0x1f, 0xff, 0xdc,
0x0c, 0x3c, 0x08,
0x00, 0x3e, 0x00,
0x0f, 0xff, 0xf8, 
0x0f, 0xff, 0xf8,
0x0f, 0x1c, 0xe0,
0x03, 0x9c, 0xe0,
0x07, 0x9c, 0xe0,
0x03, 0x9c, 0xe0,
0x1f, 0xff, 0xfc,
0x1f, 0xff, 0xfc,
0x1f, 0xff, 0xfc,
0x00, 0x00, 0x00,
0x00, 0x1e, 0x00,
0x00, 0x1e, 0x00,
0x00, 0x1e, 0x00,
0x00, 0x1e, 0x00,
0x00, 0x1e, 0x00, 
0x0f, 0xff, 0xf8,
0x0f, 0xff, 0xf8,
0x0f, 0xff, 0xf8,
0x00, 0x3c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x00, 0x1c, 0x00,
0x1f, 0xff, 0xfc,
0x1f, 0xff, 0xfc,
0x1f, 0xff, 0xfc,
0x1e, 0x00, 0x00,
0x00, 0x00, 0x00,};

// WiFi
const char *WIFI_SSID = "Buffalo-G-5CD0";
const char *WIFI_PASS = "r38hvs4nkhk7n";

// 現在時間
int currentYear = 9999;
int currentMon = 99;
int currentMDay = 99;
int currentWDay = 99;
int currentHour = 99;
int currentMin = 99;
int currentSec = 99;

// 前回時間
int lastYear = 8888;
int lastMon = 88;
int lastMDay = 88;
int lastWDay = 88;
int lastHour = 88;
int lastMin = 88;
int lastSec = 88;

// 時刻取得情報
char timeAdjustInfo[32];

void setup() {

  // e-paper
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  display.hibernate();

}


void connectWiFi(void) {

  if (WiFi.status() == WL_CONNECTED) return;

  drawStrCenter(0, 20, display.width(), "connecting...");

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    i += 1;
    if (i > 5) break;
  }
  if (WiFi.status() != WL_CONNECTED) {
    sprintf(timeAdjustInfo, "%s", "WiFi Connect Error");
  } else {
    sprintf(timeAdjustInfo, "%s", "WiFi Connect OK");
  }

}

void adjustCurrentTime(void) {

  connectWiFi();

  // NTPから時間取得
  configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");

  //sprintf(timeAdjustInfo, "last adj. %02d:%02d:%02d", currentHour, currentMin, currentSec);
  sprintf(timeAdjustInfo, "last adj. %02d:%02d", currentHour, currentMin);

}

void getCurrentTime(void) {

  // 一時間ごとに時間調整
  if (currentHour != lastHour) {
    adjustCurrentTime();
  }

  // ローカル時刻取得
  struct tm timeInfo;
  getLocalTime(&timeInfo);

  lastYear = currentYear;
  lastMon = currentMon;
  lastMDay = currentMDay;
  lastWDay = currentWDay;
  lastHour = currentHour;
  lastMin = currentMin;
  lastSec = currentSec;

  currentYear = timeInfo.tm_year + 1900;
  currentMon = timeInfo.tm_mon + 1;
  currentMDay = timeInfo.tm_mday;
  currentWDay = timeInfo.tm_wday;
  currentHour = timeInfo.tm_hour;
  currentMin = timeInfo.tm_min;
  currentSec = timeInfo.tm_sec;
}

void outputToScreen(void) {

  display.setRotation(3);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);

  // 時刻
  char timeStrHour1[2];
  char timeStrHour2[2];
  char timeStrMin1[2];
  char timeStrMin2[2];
  //char timeStrSec1[2];
  //char timeStrSec2[2];
  if (currentHour > 9) {
    sprintf(timeStrHour1, "%d", currentHour / 10);
  } else {
    sprintf(timeStrHour1, "%s", "");
  }
  sprintf(timeStrHour2, "%d", currentHour % 10);
  sprintf(timeStrMin1,  "%d", currentMin / 10);
  sprintf(timeStrMin2,  "%d", currentMin % 10);
  //sprintf(timeStrSec1,  "%d", currentSec / 10);
  //sprintf(timeStrSec2,  "%d", currentSec % 10);
  int numWidth   = 54;
  int colonWidth = 28;
  int top = 80;
  display.setFont(TIME_FONT);
  drawStrCenter(numWidth * 0 + colonWidth * 0, top, numWidth,   timeStrHour1);
  drawStrCenter(numWidth * 1 + colonWidth * 0, top, numWidth,   timeStrHour2);
  drawStrCenter(numWidth * 2 + colonWidth * 0, top, colonWidth, ":");
  drawStrCenter(numWidth * 2 + colonWidth * 1, top, numWidth,   timeStrMin1);
  drawStrCenter(numWidth * 3 + colonWidth * 1, top, numWidth,   timeStrMin2);
  //drawStrCenter(numWidth * 4 + colonWidth * 1, top, colonWidth, ":");
  //drawStrCenter(numWidth * 4 + colonWidth * 2, top, numWidth,   timeStrSec1);
  //drawStrCenter(numWidth * 5 + colonWidth * 2, top, numWidth,   timeStrSec2);

  // 年月日
  char dateStr[32];
  sprintf(dateStr, "%d/%d/%d", currentYear, currentMon, currentMDay);
  display.setFont(DATE_FONT);
  drawStrRight(0, 115, 200, dateStr);

  // 曜日
  if (currentWDay >= 0 && currentWDay <= 6) {
    display.drawBitmap(208, 96, weekKanji + currentWDay * (3 * 20), 24, 20, GxEPD_BLACK);
  }

  // 同期情報
  //display.setFont(INFO_FONT);
  //drawStrLeft(130, 115, timeAdjustInfo);

  // 00:00 の時は、スクリーン全体リフレッシュ
  display.display(!(currentHour == 0 && currentMin == 0)); 
}

void drawStrCenter(int x, int y, int areaWidth, char * str) {
  display.setCursor(x + (areaWidth - getStrWidth(str)) / 2, y);
  display.print(str);
}
void drawStrRight(int x, int y, int areaWidth, char * str) {
  display.setCursor(x + (areaWidth - getStrWidth(str)), y);
  display.print(str);
}
void drawStrLeft(int x, int y, char * str) {
  display.setCursor(x, y);
  display.print(str);
}
uint16_t getStrWidth(char * str) {
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(str, 0, 0, &tbx, &tby, &tbw, &tbh);
  return tbw;
}

// void outputText(char * text) {
//   display.setRotation(1);
//   display.setFont(&FreeSansBold18pt7b);
//   display.setTextColor(GxEPD_BLACK);
//   int16_t tbx, tby; uint16_t tbw, tbh;
//   display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);
//   // center the bounding box by transposition of the origin:
//   uint16_t x = ((display.width() - tbw) / 2) - tbx;
//   uint16_t y = ((display.height() - tbh) / 2) - tby;
//   display.setFullWindow();
//   // display.firstPage();
//   // do {
//   //   display.fillScreen(GxEPD_WHITE);
//   //   display.setCursor(x, y);
//   //   display.print(text);
//   // } while (display.nextPage());

//   display.fillScreen(GxEPD_WHITE);
//   display.setCursor(x, y);
//   display.print(text);
//   display.display(true); 

// }

void loop() {

  getCurrentTime();
  
  if (currentMin != lastMin) {
    outputToScreen();
  }

  // display.setRotation(3);
  // display.setTextColor(GxEPD_BLACK);
  // display.setFullWindow();
  // display.fillScreen(GxEPD_WHITE);
  // display.drawBitmap(200, 96, weekKanji + (currentSec % 7) * (3 * 20), 24, 20, GxEPD_BLACK);
  // display.display(true);

  delay(1000);

}
