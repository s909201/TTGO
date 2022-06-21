// TTGO Tutorial 01
// Reference: https://www.youtube.com/watch?v=WFVjsxFMbSM&ab_channel=VolosProjects
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_RED);
  tft.drawString("Hello World!",10,10);
  tft.setTextColor(TFT_GREEN);
  tft.drawString("This is Font 2",10,30,2);
  tft.setTextColor(TFT_BLUE);
  tft.drawString("Font 4",10,50,4);
  
  tft.setTextColor(TFT_YELLOW, TFT_BLUE);
  tft.drawString("5",30,100,5);
  
}

int number = 0;

void loop() {
  // put your main code here, to run repeatedly:
  tft.drawString(String(number), 30, 100, 7);
  number++;
  delay(500);
}
