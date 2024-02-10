#include <TFT_eSPI.h>
#include <SPI.h>
#include "Button2.h"
#include "image.c"

#define TFT_WIDTH       135
#define TFT_HEIGHT      240
#define BUTTON_UP       35
#define BUTTON_UP_S3    14
#define BUTTON_DOWN     0

TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
Button2 btn_left;
Button2 btn_right;

#include "assets.h"
#include "drawing.h"

int textPos = 120;


void setupButtons() {
  btn_left.begin(BUTTON_DOWN);
  btn_right.begin(BUTTON_UP);
  btn_left.setTapHandler(click_left);
  btn_right.setTapHandler(click_right);
}

void setupTft() {
  if (TFT_BL > 0) { // TFT_BL has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
    pinMode(TFT_BL, OUTPUT); // Set backlight pin to output mode
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON); // Turn backlight on. TFT_BACKLIGHT_ON has been set in the TFT_eSPI library in the User Setup file TTGO_T_Display.h
  }
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(0x0000);
  // tft.setSwapBytes(true);
  tft.setSwapBytes(false);
}

void setup() {
  Serial.begin(115200);
  Serial.print(F("Bitshot Roulette"));
  setupTft();
  setupButtons();
}

void click_left(Button2 &b) {
  tft.fillScreen(0x00E0);
  textPos -= 20;
}

void click_right(Button2 &b) {
  tft.fillScreen(0xE000);
  textPos += 20;
}

void buttonLoop() {
  btn_left.loop();
  btn_right.loop();
}

void loop(void) {
  buttonLoop();
  //tft.fillScreen(0x0000);

  // pict1
  // tft.setRotation(1);
  //tft.fillScreen(0xFF80);
  tft.pushImage(0, 0, 70, 70, (uint16_t *)lyra);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("BITSHOT", 67, 20);
  tft.drawString("ROULETTE", 67, 20 + 18);
  tft.setTextSize(1);
  tft.drawString("AN ESP32 GAME", 67, 20 + 18*2);
  tft.drawString("BY LYRA REBANE", TFT_WIDTH/2, 20 + 18*2 + 9);
  
  tft.drawString("START", 67, 79 + 10);
  tft.drawString("CREDITS", 67, 79 + 19);
  tft.drawString("EXIT", 67, 79 + 28);

  tft.setTextColor(0xBEEF, 0x0000);
  tft.drawString("T E S T", 67, textPos);

  drawPng(Ibathroom, 0, 0);
  drawPngOutline(Iestrogen, 0, 0);
  drawPng(Iestrogen, 0, 0);
  //delay(200);

  // pict2
  //tft.fillScreen(0x00FF);
  //tft.drawRGBBitmap(0, 0, lyra,  35, 140);
  //delay(200);
  }