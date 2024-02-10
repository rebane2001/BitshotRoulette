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

#include <PNGdec.h>
#include "assets.h"
PNG png;

#define MAX_IMAGE_WIDTH 135
int16_t xpos = 0;
int16_t ypos = 0;

int textPos = 120;

// https://github.com/Bodmer/TFT_eSPI/blob/master/examples/PNG%20Images/Flash_transparent_PNG/png_support.ino
void pngDrawHelper(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];          // Line buffer for rendering
  uint8_t  maskBuffer[1 + MAX_IMAGE_WIDTH / 8];  // Mask buffer

  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);

  if (png.getAlphaMask(pDraw, maskBuffer, 255)) {
    // Note: pushMaskedImage is for pushing to the TFT and will not work pushing into a sprite
    tft.pushMaskedImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer, maskBuffer);
  }
}

void drawPng(const void *image, uint64_t size, int x, int y) {
  xpos = x;
  ypos = y;
  uint16_t pngw = 0, pngh = 0;
  int16_t rc = png.openFLASH((uint8_t *)image, size, pngDrawHelper);

  if (rc == PNG_SUCCESS) {
    pngw = png.getWidth();
    pngh = png.getHeight();

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
  }
}

void drawPng(const void *image, uint64_t size) {
  drawPng(image, size, 0, 0);
}

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
  drawPng(Id_beer, 0, 0);
  drawPng(Id_cuff, 0, 0);
  drawPng(Id_gun, 0, 0);
  drawPng(Id_gun_rack, 0, 0);
  drawPng(Id_gun_shoot_d, 0, 0);
  drawPng(Id_gun_shoot_p, 0, 0);
  drawPng(Id_knife, 0, 0);
  drawPng(Id_mag_1, 0, 0);
  drawPng(Id_mag_2, 0, 0);
  drawPng(Id_smoke_1, 0, 0);
  drawPng(Id_smoke_2, 0, 0);
  drawPng(Idealer_hands, 0, 0);
  drawPng(Idealer_hands_cuff, 0, 0);
  drawPng(Idealer_head, 0, 0);
  drawPng(Idealer_head_crushed, 0, 0);
  drawPng(Iestrogen, 0, 0);
  drawPng(Iguy_1, 0, 0);
  drawPng(Iguy_2, 0, 0);
  drawPng(Ikeypad, 0, 0);
  drawPng(Iliability, 0, 0);
  drawPng(Iliability_god, 0, 0);
  drawPng(Ip_beer_1, 0, 0);
  drawPng(Ip_beer_2, 0, 0);
  drawPng(Ip_cig_1, 0, 0);
  drawPng(Ip_cig_2, 0, 0);
  drawPng(Ip_cig_3, 0, 0);
  drawPng(Ip_cuff_1, 0, 0);
  drawPng(Ip_cuff_2, 0, 0);
  drawPng(Ip_gun_inspect, 0, 0);
  drawPng(Ip_gun_pickup, 0, 0);
  drawPng(Ip_gun_rack_1, 0, 0);
  drawPng(Ip_gun_rack_2, 0, 0);
  drawPng(Ip_gun_shoot_d, 0, 0);
  drawPng(Ip_gun_shoot_p, 0, 0);
  drawPng(Ip_gun_table, 0, 0);
  drawPng(Ip_knife_1, 0, 0);
  drawPng(Ip_knife_2, 0, 0);
  drawPng(Ip_knife_3, 0, 0);
  drawPng(Ip_knife_4, 0, 0);
  drawPng(Ip_mag_1, 0, 0);
  drawPng(Ip_mag_2, 0, 0);
  drawPng(Ip_mag_3, 0, 0);
  drawPng(Ip_sig_4, 0, 0);
  drawPng(Ishow_shells, 0, 0);
  drawPng(Ishow_shells_trans, 0, 0);
  //delay(200);

  // pict2
  //tft.fillScreen(0x00FF);
  //tft.drawRGBBitmap(0, 0, lyra,  35, 140);
  //delay(200);
  }