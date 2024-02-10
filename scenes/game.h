void drawGame() {
  tft.fillScreen(0x0000);
}

void handleSceneSwitchGame() {
  drawGame();
}

void handleInputGame(char button) {
  if (scene_selection > 1) {
    scene_selection = 0;
  }
  if (button == 1) {
    switch (scene_selection) {
      case 0:
        switchScene(SCENE_GAME);
        break;
      case 1:
        switchScene(SCENE_CREDITS);
        break;
    }
  } else {
    drawGame();
  }
}
