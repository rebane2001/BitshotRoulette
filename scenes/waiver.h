void drawBathroom() {
}

void handleSceneSwitchBathroom() {
  drawBathroom();
}

void handleInputBathroom(char button) {
  if (scene_selection > 1) {
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
    }
  } else {
    drawBathroom();
  }
}
