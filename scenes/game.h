#define STATE_SHELL_CHECK   0
#define STATE_PLAYER_TURN   1
#define STATE_PLAYER_SHOOT  2
#define STATE_PLAYER_SHOT_D 3
#define STATE_PLAYER_SHOT_P 4
int game_state = STATE_SHELL_CHECK;

#define HEAD_NORMAL  0
#define HEAD_CRUSHED 1
int dealer_h = HEAD_NORMAL;

#define HANDS_NORMAL 0
int dealer_hands = HANDS_NORMAL;

#define ITEM_NONE  0
#define ITEM_CUFFS 1
#define ITEM_MAG   2
#define ITEM_BEER  3
#define ITEM_CIG   4
#define ITEM_KNIFE 5
char player_items[8] = {1, 2, 3, 4, 5, 0, 0};
char dealer_items[8] = {0, 0, 0, 0, 0, 3, 0};

void drawGunChoice() {
  bool dealerChosen = scene_selection == 0;
  uint16_t textBg = 0x89e7;
  uint16_t dealerHighlight = dealerChosen ? HIGHLIGHT_COLOR : 0x0000;
  uint16_t playerHighlight = dealerChosen ? 0x0000 : HIGHLIGHT_COLOR;
  tft.setTextSize(1);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(dealerHighlight, textBg);
  tft.drawString(F("DEALER"), TFT_WIDTH/2, 133);
  tft.setTextColor(playerHighlight, textBg);
  tft.drawString(F("YOU"), TFT_WIDTH/2, 209);
  drawPngOutline(Ip_gun_inspect, playerHighlight);
  drawPng(Ip_gun_inspect);
}

void drawOverlay() {
  switch (game_state) {
    case STATE_PLAYER_SHOOT:
      drawGunChoice();
      break;
    case STATE_PLAYER_SHOT_D:
      drawPngOutline(Ip_gun_shoot_d, 0x0000);
      drawPng(Ip_gun_shoot_d);
      break;
    case STATE_PLAYER_SHOT_P:
      drawPngOutline(Ip_gun_shoot_p, 0x0000);
      drawPng(Ip_gun_shoot_p);
      break;
  }
}

void drawTable(bool player_only) {
  if (!player_only)
    drawPng(Itable_1);
  drawPng(Itable_2);
  switch (game_state) {
    case STATE_PLAYER_TURN:
      drawPngOutline(Ip_gun_table, 6, 9, scene_selection == 0 ? HIGHLIGHT_COLOR : 0x0000);
      drawPng(Ip_gun_table, 6, 9);
      if (scene_selection > 0) {
        // TODO: draw item description
        tft.drawRect(scene_selection*16 - 15 + (scene_selection > 4 ? 6 : 0), 224, 15, 15, HIGHLIGHT_COLOR);
      }
      break;
  }
}

void drawTableItems(bool player_only) {
  for (char i = 0; i < 8; i++) {
    int item_offset_x = i*16 + (i > 3 ? 6 : 0);
    switch (player_items[i]) {
      case ITEM_NONE:
        break;
      case ITEM_CUFFS:
        drawPng(Iitem_cuffs, item_offset_x, 224);
        break;
      case ITEM_MAG:
        drawPng(Iitem_mag, item_offset_x, 224);
        break;
      case ITEM_BEER:
        drawPng(Iitem_beer, item_offset_x, 224);
        break;
      case ITEM_CIG:
        drawPng(Iitem_cig, item_offset_x, 224);
        break;
      case ITEM_KNIFE:
        drawPng(Iitem_knife, item_offset_x, 224);
        break;
    }
    if (player_only) continue;
    switch (dealer_items[i]) {
      case ITEM_NONE:
        break;
      case ITEM_CUFFS:
        drawPng(Iitem_cuffs, item_offset_x, 130);
        break;
      case ITEM_MAG:
        drawPng(Iitem_mag, item_offset_x, 130);
        break;
      case ITEM_BEER:
        drawPng(Iitem_beer, item_offset_x, 130);
        break;
      case ITEM_CIG:
        drawPng(Iitem_cig, item_offset_x, 130);
        break;
      case ITEM_KNIFE:
        drawPng(Iitem_knife, item_offset_x, 130);
        break;
    }
  }
}

void drawDealer(uint16_t dealerHighlight, bool highlightOnly) {
  if (dealer_h == HEAD_NORMAL) {
    drawPngOutline(Idealer_head, dealerHighlight);
    if (!highlightOnly)
      drawPng(Idealer_head);
  } else if (dealer_h == HEAD_CRUSHED) {
    drawPngOutline(Idealer_head_crushed, dealerHighlight);
    if (!highlightOnly)
      drawPng(Idealer_head_crushed);
  }
  switch (dealer_hands) {
    case HANDS_NORMAL:
      drawPngOutline(Idealer_hand_left, dealerHighlight);
      drawPngOutline(Idealer_hand_right, dealerHighlight);
      if (!highlightOnly) {
        drawPng(Idealer_hand_left);
        drawPng(Idealer_hand_right);
      }
      break;
  }
}

void drawScores() {
  tft.setTextColor(0x07e0, 0x0000);
  tft.setTextSize(1);
  tft.setTextDatum(TL_DATUM);
  tft.drawString(F("DEALER"), 1, 1);
  String health = "*****";
  health.remove(dealerHealth);
  tft.drawString(health, 1, 10);
  tft.setTextDatum(TR_DATUM);
  tft.drawString(player_name, TFT_WIDTH - 1, 1);
  health = "*****";
  health.remove(playerHealth);
  tft.drawString(health, TFT_WIDTH - 1, 10);
}

void drawGame() {
  drawTable(false);
  drawTableItems(false);
  drawDealer((game_state == STATE_PLAYER_SHOOT && scene_selection == 0) ? HIGHLIGHT_COLOR : 0x0000, false);
  drawScores();
  drawOverlay();
}

void drawShowShells() {
  drawPng(Ishow_shells);
  delay(1000);
  char liveShellsRemaining = liveShellCount;
  char blankShellsRemaining = blankShellCount;
  for (char i = 0; i < 8; i++) {
    short showShellX = i > 3 ? 1 : 0;
    short showShellY = 188 - i*22; 
    if (i > shellCount - 1) {
      drawPng(Ishow_none, showShellX, showShellY);
    } else if (liveShellsRemaining && (!blankShellsRemaining || random(2) == 1)) {
      drawPng(Ishow_live, showShellX, showShellY);
      liveShellsRemaining--;
    } else {
      drawPng(Ishow_blank, showShellX, showShellY);
      blankShellsRemaining--;
    }
  }
}

void startRound() {
  tft.fillScreen(0x0000);
  game_state = STATE_SHELL_CHECK;
  generateShells();
  drawShowShells();
  delay(2750);
  game_state = STATE_PLAYER_TURN;
  tft.fillScreen(0x0000);
  drawGame();
}

void handleSceneSwitchGame() {
  tft.fillScreen(0x0000);
  startRound();
}

void useItem() {
  // TODO: check if item use is allowed
  char used_item = player_items[scene_selection - 1];
  player_items[scene_selection - 1] = ITEM_NONE;
  scene_selection = 0;
  drawGame();
}

void shootCallback(char shell, char whoGotShot) {
  if (shell == SHELL_LIVE) {
    if (scene_selection) {
      for (char i = 0; i < 16; i++) {
        tft.fillScreen(vic_colors[random(0,16)]);
        delay(20);
      }
    } else {
      tft.fillScreen(VIC_BLACK);
      for (char i = 0; i < 8; i++) {
        drawDealer(vic_colors[random(0,16)], true);
      }
    }
  } else {
    game_state = STATE_PLAYER_SHOOT;
    tft.fillScreen(0x0000);
    drawGame();
    delay(300);
  }

  char dead = whoIsDead();
  if (dead != E_NONE) {
    tft.fillScreen(dead == E_PLAYER ? 0xE000 : 0x0EE0);
  } else if (nextRound()) {
    drawGame();
    delay(300);
    startRound();
  } else {
    game_state = STATE_PLAYER_TURN;
    tft.fillScreen(0x0000);
    drawGame();
  }
  // TODO: do this part
  // if (dead == E_NONE) {}
}

void handleInputGame(char button) {
  if (game_state == STATE_PLAYER_TURN) {
    while (scene_selection > 0) {
      if (player_items[scene_selection - 1] != ITEM_NONE) break;
      scene_selection++;
      if (scene_selection > 8)
        scene_selection = 0;
    }
  } else if (game_state == STATE_PLAYER_SHOOT) {
    if (scene_selection > 1)
      scene_selection = 0;
  } else {
    if (scene_selection > 8)
      scene_selection = 0;
  }
  if (button == 1) {
    if (game_state == STATE_PLAYER_TURN) {
      if (scene_selection == 0) {
        game_state = STATE_PLAYER_SHOOT;
        drawPngOutline(Ip_gun_pickup, 6, 9);
        drawPng(Ip_gun_pickup, 6, 9);
        delay(100);
        drawGame();
      } else {
        useItem();
      }
    } else if (game_state == STATE_PLAYER_SHOOT) {
      char whoGotShot = scene_selection ? E_PLAYER : E_DEALER;
      scene_selection = 0;
      game_state = whoGotShot == E_PLAYER ? STATE_PLAYER_SHOT_P : STATE_PLAYER_SHOT_D;
      drawGame();
      delay(500);
      char shell = shootGun(E_PLAYER, whoGotShot);
      shootCallback(shell, whoGotShot);
    }
  } else if (button == 0) {
    if (game_state == STATE_PLAYER_TURN) {
      drawTable(true);
      drawTableItems(true);
      drawOverlay();
    } else {
      drawGame();
    }
  }
}

