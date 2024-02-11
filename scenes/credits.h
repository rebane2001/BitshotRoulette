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
  tft.drawString(F("(rebane2001)"), 8, BASE_HEIGHT + LINE_HEIGHT*8);
  //
  tft.drawString(F("Libraries used:"), 8, BASE_HEIGHT + LINE_HEIGHT*10);
  tft.drawString(F("TFT_eSPI"), 8, BASE_HEIGHT + LINE_HEIGHT*11);
  tft.drawString(F("Button2"), 8, BASE_HEIGHT + LINE_HEIGHT*12);
  tft.drawString(F("PNGdec"), 8, BASE_HEIGHT + LINE_HEIGHT*13);
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
