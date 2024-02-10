#define STATE_PLAYER 0
int game_state = STATE_PLAYER;

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

void drawTable() {
  drawPng(Itable);
  if (game_state == STATE_PLAYER) {
    drawPngOutline(Ip_gun_table, 6, 9, scene_selection == 0 ? HIGHLIGHT_COLOR : 0x0000);
    drawPng(Ip_gun_table, 6, 9);
    if (scene_selection > 0) {
      tft.drawRect(scene_selection*16 - 15 + (scene_selection > 4 ? 6 : 0), 224, 15, 15, HIGHLIGHT_COLOR);
    }
  }
}

void drawTableItems() {
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

void drawDealer() {
  if (dealer_h == HEAD_NORMAL) {
    drawPngOutline(Idealer_head, 0x0000);
    drawPng(Idealer_head);
  } else if (dealer_h == HEAD_CRUSHED) {
    drawPngOutline(Idealer_head_crushed, 0x0000);
    drawPng(Idealer_head_crushed);
  }
  switch (dealer_hands) {
    case HANDS_NORMAL:
      drawPngOutline(Idealer_hand_left, 0x0000);
      drawPngOutline(Idealer_hand_right, 0x0000);
      drawPng(Idealer_hand_left);
      drawPng(Idealer_hand_right);
      break;
  }
}

void drawGame() {
  drawTable();
  drawTableItems();
  drawDealer();
}

void handleSceneSwitchGame() {
  tft.fillScreen(0x0000);
  drawGame();
}

void handleInputGame(char button) {
  if (scene_selection > 8) {
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

