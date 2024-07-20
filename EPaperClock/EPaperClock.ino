#include <WiFi.h>                               // WiFi
#include <GxEPD2_BW.h>                          // e-paper
#include <Fonts/FreeSans9pt7b.h>                // e-paper
#include "GxEPD2_display_selection_new_style.h" // e-paper
#include "AARDV40pt7b.h"
#include "AARDV12pt7b.h"

#define TIME_FONT &AARDV40pt7b
#define DATE_FONT &AARDV12pt7b
#define INFO_FONT &FreeSans9pt7b

// 曜日漢字ビットマップ
#include "WeekKanjiBitmap.h"

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

//bool firstFlg = true;

void setup() {

  // e-paper
  delay(100);
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse

  display.setRotation(3);

  // 全背景を白く描画
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);

}

void loop() {

  getCurrentTime();
  
  if (currentMin != lastMin) {
    outputToScreen();
  }

  delay(1000);

}

//////////////////////////////////////////////////
// WiFi, Time
//////////////////////////////////////////////////

void connectWiFi(void) {

  if (WiFi.status() == WL_CONNECTED) return;

  sprintf(timeAdjustInfo, "connecting...");

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

//////////////////////////////////////////////////
// e-Paper
//////////////////////////////////////////////////

void outputToScreen(void) {

  display.firstPage();

  // 時刻
  char timeStrHour1[2];
  char timeStrHour2[2];
  char timeStrMin1[2];
  char timeStrMin2[2];
  if (currentHour > 9) {
    sprintf(timeStrHour1, "%d", currentHour / 10);
  } else {
    sprintf(timeStrHour1, "%s", "");
  }
  sprintf(timeStrHour2, "%d", currentHour % 10);
  sprintf(timeStrMin1,  "%d", currentMin / 10);
  sprintf(timeStrMin2,  "%d", currentMin % 10);
  // for (int i = 0; i < 3; i++) {
  //   drawTime(timeStrHour1, timeStrHour2, timeStrMin1, timeStrMin2);
  // }
  //drawTime(" ", " ", " ", " ");
  drawTime(timeStrHour1, timeStrHour2, timeStrMin1, timeStrMin2);

  // 年月日
  char dateStr[32];
  sprintf(dateStr, "%d/%d/%d", currentYear, currentMon, currentMDay);
  display.setFont(DATE_FONT);
  drawStrRight(0, 120, 200, dateStr, -2, -4);

  // 曜日
  if (currentWDay >= 0 && currentWDay <= 6) {
    drawBitmap(208, 88, weekKanji + currentWDay * (4 * 32), 32, 32, GxEPD_BLACK);
  }

  // 同期情報
  //display.setFont(INFO_FONT);
  //drawStrLeft(130, 115, timeAdjustInfo);


  display.hibernate();

}

void drawTime(char * timeStrHour1, char * timeStrHour2, char * timeStrMin1, char * timeStrMin2) {

  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(timeStrHour2, 0, 0, &tbx, &tby, &tbw, &tbh);

  const int numWidth   = 54;
  const int colonWidth = 28;
  const int top = 80;
  display.setFont(TIME_FONT);
  display.setPartialWindow(0, 0, numWidth * 4 + colonWidth, 88);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    drawStrCenterPartial(numWidth * 0 + colonWidth * 0, top, numWidth,   " ", 0);
    drawStrCenterPartial(numWidth * 1 + colonWidth * 0, top, numWidth,   " ", 0);
    drawStrCenterPartial(numWidth * 2 + colonWidth * 1, top, numWidth,   " ", 0);
    drawStrCenterPartial(numWidth * 3 + colonWidth * 1, top, numWidth,   " ", 0);

    display.fillScreen(GxEPD_WHITE);
    drawStrCenterPartial(numWidth * 0 + colonWidth * 0, top, numWidth,   timeStrHour1, 0);
    drawStrCenterPartial(numWidth * 1 + colonWidth * 0, top, numWidth,   timeStrHour2, 0);
    drawStrCenterPartial(numWidth * 2 + colonWidth * 0, top, colonWidth, ":", -4);
    drawStrCenterPartial(numWidth * 2 + colonWidth * 1, top, numWidth,   timeStrMin1, 0);
    drawStrCenterPartial(numWidth * 3 + colonWidth * 1, top, numWidth,   timeStrMin2, 0);
  } while (display.nextPage());

}

void drawStrCenterPartial(int16_t x, int16_t y, int16_t areaWidth, char * str, int16_t offset_y) {

  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(str, 0, 0, &tbx, &tby, &tbw, &tbh);

  if (strlen(str) > 0) {
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(x + (areaWidth - tbw) / 2, y + offset_y);
    display.print(str);
  }

}

void drawStrRight(int16_t x, int16_t y, int16_t areaWidth, char * str, int16_t offset_x, int16_t offset_y) {

  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(str, 0, 0, &tbx, &tby, &tbw, &tbh);

  display.setPartialWindow(x, y - tbh, areaWidth, ((tbh / 8) + 1) * 8);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(x + (areaWidth - tbw) + offset_x, y + offset_y);
    display.print(str);
  } while (display.nextPage());

}

void drawBitmap(int16_t x, int16_t y, const unsigned char * bitmap, int16_t w, int16_t h, uint16_t color) {

  display.setPartialWindow(x, y, w, ((h / 8) + 1) * 8);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    //display.setTextColor(GxEPD_BLACK);
    display.drawBitmap(x, y, bitmap, w, h, GxEPD_BLACK);
  } while (display.nextPage());

}

void drawStrLeft(int x, int y, char * str) {
  display.setCursor(x, y);
  display.print(str);
}


