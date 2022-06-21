// TTGO Tutorial 03
// Reference: https://www.youtube.com/watch?v=R-qFKemDFyM&ab_channel=VolosProjects
#include <TFT_eSPI.h>
#include "caffee.h"
#include "font.h"

TFT_eSPI tft = TFT_eSPI(135,240);

int org=140;
int shift=25;
uint8_t rotation=135; // Range: 0~135, mapping to 0~270

void setup() {
  // put your setup code here, to run once:
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  
  tft.setRotation(rotation); // screen rotate
  
  tft.pushImage(0,5,128,128,caffee);
  tft.setFreeFont(&Rock_Salt_Regular_12); // Select font style
  tft.drawString("Hello",160,35);
  tft.drawString("World!",160,65);
  
/*
  tft.drawString("Dear Fancy,",6,org);
  tft.drawString("Have a",11,org + shift);
  tft.drawString("wonderful",21,org + shift*2);
  tft.drawString("working day",25,org + shift*3);
*/
}

void loop() {
  // put your main code here, to run repeatedly:

}
