void drawMainMenuOptions() {
  const int TFT_WC = TFT_WIDTH/2;
  const int BASE_HEIGHT = 60;
  const int LINE_HEIGHT = 9;

  tft.setTextColor(scene_selection == 0 ? 0xFFFF : 0x8410, 0x0000);
  tft.drawString(F("START"), TFT_WC, BASE_HEIGHT + 60 + LINE_HEIGHT*1);
  tft.setTextColor(scene_selection == 1 ? 0xFFFF : 0x8410, 0x0000);
  tft.drawString(F("CREDITS"), TFT_WC, BASE_HEIGHT + 60 + LINE_HEIGHT*2);
  tft.setTextColor(scene_selection == 2 ? 0xFFFF : 0x8410, 0x0000);
  tft.drawString(F("EXIT"), TFT_WC, BASE_HEIGHT + 60 + LINE_HEIGHT*3);
}

void drawMainMenu() {
  const int TFT_WC = TFT_WIDTH/2;
  const int BASE_HEIGHT = 60;
  const int LINE_HEIGHT = 9;

  tft.fillScreen(0x0000);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(F("BITSHOT"), TFT_WC, BASE_HEIGHT);
  tft.drawString(F("ROULETTE"), TFT_WC, BASE_HEIGHT + LINE_HEIGHT*2);
  tft.setTextSize(1);
  tft.drawString(F("AN ESP32 PORT"), TFT_WC, BASE_HEIGHT + LINE_HEIGHT*4);
  tft.drawString(F("BY LYRA REBANE"), TFT_WC, BASE_HEIGHT + LINE_HEIGHT*5);

  drawMainMenuOptions();
}

void handleSceneSwitchMainMenu() {
  drawMainMenu();
}

void handleInputMainMenu(char button) {
  if (scene_selection > 2) {
    scene_selection = 0;
  }
  if (button == 1) {
    switch (scene_selection) {
      case 0:
        switchScene(SCENE_BATHROOM);
        break;
      case 1:
        switchScene(SCENE_CREDITS);
        break;
      case 2:
        tft.fillScreen(0x0000);
        if (TFT_BL)
          digitalWrite(TFT_BL, LOW);
        break;
    }
  } else {
    drawMainMenuOptions();
  }
}
