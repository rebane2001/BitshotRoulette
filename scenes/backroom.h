void drawBackroom() {
  drawPng(Iguy_1);
}

void handleSceneSwitchBackroom() {
  drawBackroom();
}

void handleInputBackroom(char button) {
  if (scene_selection > 0) {
    scene_selection = 0;
  }
  if (button == 1) {
    switch (scene_selection) {
      case 0:
        switchScene(SCENE_WAIVER);
        break;
    }
  } else {
    drawBackroom();
  }
}
