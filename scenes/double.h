bool doubleFirstDraw = false;
bool doubleNoInput = false;

void drawDouble() {
  tft.fillScreen(0x0000);
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  if (doubleFirstDraw) {
    for (long long i = 0; i < 1000; i++) {
      tft.drawString(String(game_score/1000*i), TFT_WIDTH / 2, TFT_HEIGHT / 2 - 20);
      delay(4);
    }
  }
  tft.drawString(String(game_score), TFT_WIDTH / 2, TFT_HEIGHT / 2 - 20);
  if (doubleFirstDraw)
    delay(2000);
  tft.drawString("DOUBLE OR", TFT_WIDTH / 2, (TFT_HEIGHT / 4) - 5);
  tft.drawString("NOTHING?", TFT_WIDTH / 2, (TFT_HEIGHT / 4) + 18 - 5);
  tft.setTextColor(scene_selection == 0 ? HIGHLIGHT_COLOR : 0xFFFF, 0x0000);
  tft.drawString("YES", TFT_WIDTH / 2 - 25, (TFT_HEIGHT * 3 / 4) - 50);
  tft.setTextColor(scene_selection == 1 ? HIGHLIGHT_COLOR : 0xFFFF, 0x0000);
  tft.drawString("NO", TFT_WIDTH / 2 + 25, (TFT_HEIGHT * 3 / 4) - 50);
  doubleFirstDraw = false;
}

void drawWinText() {
  tft.setTextColor(0xFFFF, 0x0000);
  tft.setTextSize(1);
  tft.setTextDatum(TC_DATUM);
  tft.drawString("CONGRATULATIONS,", TFT_WIDTH / 2, 16 + 9*0);
  tft.setTextSize(2);
  tft.drawString(player_name + "!", TFT_WIDTH / 2, 16 + 9*1);
  tft.setTextSize(1);
  tft.drawString("rounds beat: " + String(stat_endless_rounds), TFT_WIDTH / 2, 16 + 9*4);
  tft.drawString("shots fired: " + String(stat_shots_fired), TFT_WIDTH / 2, 16 + 9*5);
  tft.drawString("shells ejected: " + String(stat_shells_ejected), TFT_WIDTH / 2, 16 + 9*6);
  tft.drawString("cigarettes smoked: " + String(stat_cigarettes_smoked), TFT_WIDTH / 2, 16 + 9*7);
  tft.drawString("ml of beer drank: " + String(stat_ml_of_beer_drank), TFT_WIDTH / 2, 16 + 9*8);
  tft.drawString("total cash:", TFT_WIDTH / 2, 16 + 9*10);
  tft.setTextSize(2);
  tft.drawString(String(game_score) + "$", TFT_WIDTH / 2, 16 + 9*11);
}

void handleSceneSwitchDouble() {
  stat_endless_rounds++;
  increaseScore();
  doubleFirstDraw = true;
  drawDouble();
}

void handleInputDouble(char button) {
  if (doubleNoInput) return;
  if (scene_selection > 1) {
    scene_selection = 0;
  }
  if (button == 1) {
    switch (scene_selection) {
      case 0:
        switchScene(SCENE_GAME);
        break;
      case 1:
        doubleNoInput = true;
        drawPng(Iending_win);
        drawWinText();
        break;
    }
  } else {
    drawDouble();
  }
}
