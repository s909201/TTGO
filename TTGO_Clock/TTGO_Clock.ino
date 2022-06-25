// TTGO Tutorial 05
#include <TFT_eSPI.h>
#include "caffee.h"
#include <WiFi.h>
#include "time.h"
#include "sntp.h"

TFT_eSPI tft = TFT_eSPI(135,240);

//int org=140;
//int shift=25;
uint8_t rotation=135; // Range: 0~135, mapping to 0~270
bool show;

const char *ssid = "HH71V1_0801_2.4G";
const char *password = "thisismyhouseandhome";

char buf[5];

// -----------------------------------------------------------
// TempClock
// millis(): Get System Tick
struct _tm
{
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t min;
  uint8_t sec;
  uint32_t sec1;
} t;
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
// const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)
const char* time_zone = "CST-8";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 1200; // 0.6 sec
void (*resetFunc)(void) = 0;  // declare reset fuction at address 0


// -----------------------------------------------------------
void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  t.year = timeinfo.tm_year;
  t.month = timeinfo.tm_mon;
  t.day = timeinfo.tm_mday;
  t.hour = timeinfo.tm_hour;
  t.min = timeinfo.tm_min;
  t.sec = timeinfo.tm_sec;
  t.sec1 = millis();
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
  // printLocalTime();
}
// -----------------------------------------------------------
void initClock()
{
  // set notification call-back function
  sntp_set_time_sync_notification_cb(timeavailable);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  configTzTime(time_zone, ntpServer1, ntpServer2);
}
// -----------------------------------------------------------
// Initialize WiFi
void initWiFi()
{
  WiFi.mode(WIFI_STA);
  // WiFi Connect
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi..");
  currentTime = millis();
  previousTime = currentTime;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
    if (millis() - previousTime >= timeoutTime)
    {
      resetFunc(); // call reset
    }
  }
  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());
}
// -----------------------------------------------------------
// -----------------------------------------------------------
void SysTick()
{
  if ((millis() - t.sec1) >= 1000) // 1 sec
  {
    t.sec1 = millis(); // reset

    t.sec++;
    if (t.sec >= 60)
    {
      t.sec = 0;
      t.min++;
      if (t.min >= 60)
      {
        t.min = 0;
        t.hour++;
        if (t.hour >= 24)
        {
          t.hour = 0;
        }
      }
      UpdateTime();
    }
  }
}
// -----------------------------------------------------------
void UpdateTime()
{
  tft.fillRect(150, 0, 90, 54, TFT_BLACK); // tft.fillRect(x, y, w, h, color)
  tft.fillRect(150, 65, 90, 50, TFT_BLACK);
  //tft.drawString(String(t.hour),150,5,7);
  //tft.drawString(String(t.min),150,65,7);
  sprintf(buf, "%02d", t.hour);
  tft.drawString(buf,150,5,7);
  sprintf(buf, "%02d", t.min);
  tft.drawString(buf,150,65,7);
}
// -----------------------------------------------------------
void ClockPoint()
{
  if((millis() - currentTime) >= 500)
  {
    currentTime = millis();
    if(show==0)
    {
      tft.fillRect(145, 55, 75, 3, TFT_BLACK);
      show=1;
    }else{
      tft.fillRect(145, 55, 75, 3, TFT_WHITE);
      show=0;
    }
  }
}

// -----------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  //connect to WiFi
  initWiFi();

  initClock();
  
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.setRotation(rotation); // screen rotate
  tft.pushImage(0,5,128,128,caffee);
  tft.drawString(WiFi.localIP().toString().c_str(),140,120);
  
  tft.drawString("88",150,5,7);
  tft.drawString("88",150,65,7);
  tft.fillRect(145, 55, 75, 3, TFT_WHITE);
  
  printLocalTime();
  UpdateTime();
  
  show=0;
  currentTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  ClockPoint();
  SysTick();
}
