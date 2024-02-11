const char buttonBounds[][4] = {
  { 28, 53, 14, 14 },
  { 51, 53, 14, 14 },
  { 71, 54, 39, 14 },
  { 28, 75, 14, 15 },
  { 51, 76, 14, 14 },
  { 73, 76, 14, 14 },
  { 0, 0, 0, 0 },
  { 28, 98, 14, 15 },
  { 51, 98, 14, 15 },
  { 28, 120, 14, 15 },
  { 51, 120, 14, 15 },
  { 73, 120, 14, 15 },
  { 94, 120, 15, 15 },
  { 28, 143, 14, 15 },
  { 51, 143, 14, 14 },
  { 73, 143, 14, 14 },
  { 94, 143, 15, 14 },
  { 28, 165, 15, 15 },
  { 51, 165, 14, 15 },
  { 73, 164, 14, 15 },
  { 94, 164, 15, 15 },
  { 28, 187, 15, 15 },
  { 51, 186, 14, 16 },
  { 73, 186, 14, 15 },
  { 94, 185, 15, 16 },
  { 29, 208, 14, 16 },
  { 51, 208, 14, 16 },
  { 73, 207, 14, 16 }
};

char keypad_index = 0;
String player_name = "";
bool waiver_ready = false;

void drawKeypad() {
  drawPng(Ikeypad);
  if (scene_selection != 6) {
    if (btn_left_long) {
      tft.fillRect(buttonBounds[scene_selection][0], buttonBounds[scene_selection][1], buttonBounds[scene_selection][2], buttonBounds[scene_selection][3], 0xf80f);
    }
    tft.drawRect(buttonBounds[scene_selection][0], buttonBounds[scene_selection][1], buttonBounds[scene_selection][2], buttonBounds[scene_selection][3], HIGHLIGHT_COLOR);
  } else {
    tft.drawFastVLine(94, 76, 23, HIGHLIGHT_COLOR);
    tft.drawFastHLine(94, 76, 16, HIGHLIGHT_COLOR);
    tft.drawFastVLine(94 + 16, 76, 37, HIGHLIGHT_COLOR);
    tft.drawFastVLine(72, 99, 14, HIGHLIGHT_COLOR);
    tft.drawFastHLine(72, 99, 22, HIGHLIGHT_COLOR);
    tft.drawFastHLine(72, 99 + 14, 38, HIGHLIGHT_COLOR);
  }
  tft.setTextColor(0x07e0, 0x0000);
  tft.setTextSize(2);
  tft.setTextDatum(TL_DATUM);
  tft.drawString(player_name, 32, 26);
}

void drawWaiver() {
  drawPng(Iguy_1);
  drawPng(Iliability);
  drawPng(Icheckerboard);
  drawKeypad();
}

void handleSceneSwitchWaiver() {
  drawWaiver();
}

void handleInputWaiver(char button) {
  if (waiver_ready) {
    switchScene(SCENE_GAME);
    return;
  }
  if (scene_selection > 27) {
    scene_selection = 0;
  }
  if (button == 1) {
    if (scene_selection == 2) {
      if (player_name.length() == 0) return;
      player_name.remove(player_name.length() - 1);
      drawKeypad();
    } else if (scene_selection == 6) {
      if (player_name.length() == 0) return;
      if (player_name.equals("GOD")) return;
      if (player_name.equals("DEALER")) return;
      drawPng(Iguy_1);
      drawPng(Iliability);
      tft.setTextColor(0x0000, 0x86BB);
      tft.setTextSize(2);
      tft.setTextDatum(TL_DATUM);
      tft.drawString(player_name, 57, 190);
      waiver_ready = true;
    } else if (player_name.length() < 7) {
      char waiver_letter = 65 + scene_selection;
      if (scene_selection > 2) {
        waiver_letter--;
      }
      if (scene_selection > 6) {
        waiver_letter--;
      }
      player_name.concat(waiver_letter);
      if (player_name.length() == 7 && !player_name.equals("AMONGUS")) {
        player_name.remove(6);
      }
      drawKeypad();
    }
  } else {
    drawKeypad();
  }
}

void waiverHold() {
  scene_selection++;
  if (scene_selection > 27) {
    scene_selection = 0;
  }
  drawKeypad();
}
