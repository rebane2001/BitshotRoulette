bool isHoldingEstrogen = false;

void drawBathroom() {
  drawPng(Ibathroom);
  if (isHoldingEstrogen) {
    drawPng(Icheckerboard);
    drawPngOutline(Iestrogen);
    drawPng(Iestrogen);
  } else if (scene_selection == 0) {
    drawPngOutline(Ibathroom_door);
    drawPng(Ibathroom_door);
  } else {
    drawPngOutline(Ibathroom_estrogen);
    drawPng(Ibathroom_estrogen);
  }
}

void handleSceneSwitchBathroom() {
  drawBathroom();
}

void handleInputBathroom(char button) {
  if (isHoldingEstrogen) {
    isHoldingEstrogen = false;
    scene_selection = 1;
    drawBathroom();
    return;
  }
  if (scene_selection > 1) {
    scene_selection = 0;
  }
  if (button == 1) {
    switch (scene_selection) {
      case 0:
        switchScene(SCENE_BACKROOM);
        break;
      case 1:
        isHoldingEstrogen = true;
        drawBathroom();
        break;
    }
  } else {
    drawBathroom();
  }
}
