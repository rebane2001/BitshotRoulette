void drawCredits() {
  const int TFT_WC = TFT_WIDTH/2;
  const int BASE_HEIGHT = 30;
  const int LINE_HEIGHT = 9;

  tft.fillScreen(0x0000);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(F("CREDITS"), TFT_WC, BASE_HEIGHT);
  tft.setTextDatum(ML_DATUM);
  tft.setTextSize(1);
  tft.drawString(F("Original game by"), 8, BASE_HEIGHT + LINE_HEIGHT*3);
  tft.drawString(F("Mike Klubnika"), 8, BASE_HEIGHT + LINE_HEIGHT*4);
  // TODO QR CODE to game page
  tft.drawString(F("ESP32 port by"), 8, BASE_HEIGHT + LINE_HEIGHT*6);
  tft.drawString(F("Lyra Rebane"), 8, BASE_HEIGHT + LINE_HEIGHT*7);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(F("Press any key"), TFT_WC, TFT_HEIGHT - 25 - LINE_HEIGHT);
  tft.drawString(F("to next"), TFT_WC, TFT_HEIGHT - 25);
}

void handleSceneSwitchCredits() {
  drawCredits();
}

void handleInputCredits(char button) {
  switchScene(SCENE_MAIN_MENU);
}
