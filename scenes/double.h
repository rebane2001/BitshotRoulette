bool doubleFirstDraw = false;

void drawDouble() {
  tft.fillScreen(0x0000);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  if (doubleFirstDraw) {
    for (long long i = 0; i < 1000; i++) {
      tft.drawString(String(game_score/i*i), TFT_WIDTH / 2, 50);
      delay(4);
    }
  }
  tft.drawString(String(game_score), TFT_WIDTH / 2, 50);
  if (doubleFirstDraw)
    delay(2000);
  tft.drawString("DOUBLE OR", TFT_WIDTH / 2, 80);
  tft.drawString("NOTHING?", TFT_WIDTH / 2, 98);
  tft.setTextColor(scene_selection == 0 ? HIGHLIGHT_COLOR : 0xFFFF, 0x0000);
  tft.drawString("YES", TFT_WIDTH / 2 - 75, 110);
  tft.setTextColor(scene_selection == 1 ? HIGHLIGHT_COLOR : 0xFFFF, 0x0000);
  tft.drawString("NO", TFT_WIDTH / 2 + 75, 110);
  doubleFirstDraw = false;
}

void handleSceneSwitchDouble() {
  doubleFirstDraw = true;
  drawDouble();
}

void handleInputDouble(char button) {
  if (scene_selection > 1) {
    scene_selection = 0;
  }
  if (button == 1) {
    switch (scene_selection) {
      case 0:
        switchScene(SCENE_GAME);
        break;
    }
  } else {
    drawDouble();
  }
}
