#include <TFT_eSPI.h>
#include <SPI.h>
#include "Button2.h"

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

#define  SCENE_MAIN_MENU 0
#define  SCENE_CREDITS 1
#define  SCENE_BATHROOM 2
#define  SCENE_BACKROOM 3
#define  SCENE_GAME 4
#define  SCENE_WAIVER 5
int scene = SCENE_MAIN_MENU;
int scene_selection = 0;

void switchScene(char scene_id);

#include "scenes/mainmenu.h"
#include "scenes/credits.h"

void switchScene(char scene_id) {
  scene = scene_id;
  scene_selection = 0;
  switch (scene) {
    case SCENE_MAIN_MENU:
      handleSceneSwitchMainMenu();
      break;
    case SCENE_CREDITS:
      handleSceneSwitchCredits();
      break;
    case SCENE_BATHROOM:
      handleSceneSwitchMainMenu();
      break;
    case SCENE_BACKROOM:
      handleSceneSwitchMainMenu();
      break;
    case SCENE_GAME:
      handleSceneSwitchMainMenu();
      break;
    case SCENE_WAIVER:
      handleSceneSwitchMainMenu();
      break;
  }
}

void click(char button) {
  switch (scene) {
    case SCENE_MAIN_MENU:
      handleInputMainMenu(button);
      break;
    case SCENE_CREDITS:
      handleInputCredits(button);
      break;
    case SCENE_BATHROOM:
      handleInputMainMenu(button);
      break;
    case SCENE_BACKROOM:
      handleInputMainMenu(button);
      break;
    case SCENE_GAME:
      handleInputMainMenu(button);
      break;
    case SCENE_WAIVER:
      handleInputMainMenu(button);
      break;
  }
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
  drawMainMenu();
}

void click_left(Button2 &b) {
  scene_selection++;
  click(0);
}

void click_right(Button2 &b) {
  click(1);
}

void buttonLoop() {
  btn_left.loop();
  btn_right.loop();
}

void loop(void) {
  buttonLoop();
  // drawPngOutline(Iestrogen);
  // drawPng(Iestrogen);
  }