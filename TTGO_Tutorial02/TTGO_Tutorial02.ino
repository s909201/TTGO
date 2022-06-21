// TTGO Tutorial 02
// Reference: https://www.youtube.com/watch?v=AyumJUAFdZ0&ab_channel=VolosProjects

#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.drawPixel(120,20,TFT_RED);
  tft.drawPixel(125,25,TFT_BLUE);
  
  tft.drawLine(0,0,135,240,TFT_GREEN); // tft.drawLine(x1, y1, x2, y2, color)
  tft.drawLine(135,0,0,240,TFT_RED);

  tft.drawRect(125, 120, 10, 10, TFT_WHITE); // tft.drawRect(x, y, w, h, color)
  tft.fillRect(20, 20, 30, 30, TFT_YELLOW);  // tft.fillRect(x, y, w, h, color)

  tft.drawCircle(70, 30, 20, TFT_GREEN); // tft.drawCircle(x, y, r, color)
  tft.fillCircle(70, 140, 40, TFT_BLUE); // tft.fillCircle(x, y, r, color)

}

void loop() {
  // put your main code here, to run repeatedly:

}
