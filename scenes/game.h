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
    case STATE_PLAYER_ITEM:
      switch (last_item) {
        case ITEM_CUFFS:
          drawPngOutline(Ip_cuff_1, 0x0000);
          drawPng(Ip_cuff_1);
          break;
        case ITEM_MAG:
          if (item_frame == 0) {
            drawPngOutline(Ip_mag_1, 0x0000);
            drawPng(Ip_mag_1);
          } else if (item_frame == 1) {
            drawPngOutline(Ip_mag_2, 0x0000);
            drawPng(Ip_mag_2);
          } else if (item_frame >= 2) {
            drawPngOutline(Ip_mag_3, 0x0000);
            drawPng(Ip_mag_3);
            if (item_frame == 3) {
              drawPngOutline(Ip_gun_rack_1, 0x0000);
              drawPng(Ip_gun_rack_1);
            } else if (item_frame == 4) {
              if (peekShell() == SHELL_LIVE) {
                drawPngOutline(Ip_gun_rack_live, 0x0000);
                drawPng(Ip_gun_rack_live);
              } else {
                drawPngOutline(Ip_gun_rack_blank, 0x0000);
                drawPng(Ip_gun_rack_blank);
              }
              // Putting delay here is cursed but works
              delay(1000);
            }
            // TODO: reveal bullet contents
          }
          break;
        case ITEM_BEER:
          if (item_frame == 0) {
            drawPngOutline(Ip_beer_1, 0x0000);
            drawPng(Ip_beer_1);
          } else if (item_frame == 1) {
            drawPngOutline(Ip_beer_2, 0x0000);
            drawPng(Ip_beer_2);
          }
          break;
        case ITEM_CIG:
          if (item_frame == 0) {
            drawPngOutline(Ip_cig_1, 0x0000);
            drawPng(Ip_cig_1);
          } else if (item_frame == 1) {
            drawPngOutline(Ip_cig_2, 0x0000);
            drawPng(Ip_cig_2);
          } else if (item_frame == 2) {
            drawPngOutline(Ip_cig_3, 0x0000);
            drawPng(Ip_cig_3);
          } else if (item_frame >= 3) {
            drawPngOutline(Ip_cig_4, 0x0000);
            drawPng(Ip_cig_4);
          }
          break;
        case ITEM_KNIFE:
          if (item_frame == 0) {
            drawPngOutline(Ip_knife_1, 0x0000);
            drawPng(Ip_knife_1);
          } else if (item_frame == 1) {
            drawPngOutline(Ip_knife_2, 0x0000);
            drawPng(Ip_knife_2);
          } else if (item_frame == 2) {
            drawPngOutline(Ip_knife_3, 0x0000);
            drawPng(Ip_knife_3);
          }
          break;
      }
      break;
  }
  if (who_cuffed == E_PLAYER) {
    drawPngOutline(Ip_cuff_2, 0x0000);
    drawPng(Ip_cuff_2);
  }
}

void drawTable(bool player_only) {
  if (!player_only)
    drawPng(Itable_1);
  drawPng(Itable_2);
  switch (game_state) {
    case STATE_PLAYER_TURN:
    case STATE_DEALER_TURN:
      drawPngOutline(Ip_gun_table, 6, 9, (scene_selection == 0 && game_state == STATE_PLAYER_TURN) ? HIGHLIGHT_COLOR : 0x0000);
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
  if (who_cuffed == E_DEALER && (last_item != ITEM_CUFFS || game_state != STATE_PLAYER_ITEM)) {
    drawPngOutline(Idealer_hands_cuff, dealerHighlight);
    if (!highlightOnly)
      drawPng(Idealer_hands_cuff);
  } else {
    switch (game_state) {
      case STATE_DEALER_SHOOT:
        drawPngOutline(Id_gun, 0x0000);
        drawPng(Id_gun);
        break;
      case STATE_DEALER_SHOT_D:
        drawPngOutline(Id_gun_shoot_d, 0x0000);
        drawPng(Id_gun_shoot_d);
        break;
      case STATE_DEALER_SHOT_P:
        drawPngOutline(Id_gun_shoot_p, 0x0000);
        drawPng(Id_gun_shoot_p);
        break;
      case STATE_DEALER_ITEM:
        switch (last_item) {
          case ITEM_CUFFS:
            drawPngOutline(Id_cuff, 0x0000);
            drawPng(Id_cuff);
            break;
          case ITEM_MAG:
            if (item_frame == 0) {
              drawPngOutline(Id_mag_1, 0x0000);
              drawPng(Id_mag_1);
            } else {
              drawPngOutline(Id_mag_2, 0x0000);
              drawPng(Id_mag_2);
            }
            break;
          case ITEM_BEER:
            drawPngOutline(Id_beer, 0x0000);
            drawPng(Id_beer);
            break;
          case ITEM_CIG:
            if (item_frame == 0) {
              drawPngOutline(Id_smoke_1, 0x0000);
              drawPng(Id_smoke_1);
            } else {
              drawPngOutline(Id_smoke_2, 0x0000);
              drawPng(Id_smoke_2);
            }
            break;
          case ITEM_KNIFE:
            drawPngOutline(Id_knife, 0x0000);
            drawPng(Id_knife);
            break;
        }
        break;
      default:
        drawPngOutline(Idealer_hand_left, dealerHighlight);
        drawPngOutline(Idealer_hand_right, dealerHighlight);
        if (!highlightOnly) {
          drawPng(Idealer_hand_left);
          drawPng(Idealer_hand_right);
        }
        break;
    }
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
    } else if (liveShellsRemaining && (!blankShellsRemaining || random(2))) {
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

void handleDealer();

void playerUseItem(char itemIndex) {
  game_state = STATE_PLAYER_ITEM;
  item_frame = 0;
  char usedItem = useItem(E_PLAYER, itemIndex);
  scene_selection = 0;
  while (true) {
    tft.fillScreen(0x0000);
    drawGame();
    delay((usedItem == ITEM_KNIFE || usedItem == ITEM_MAG || usedItem == ITEM_CIG) ? 500 : 1500);
    item_frame++;
    if (usedItem == ITEM_CUFFS && item_frame == 1) break;
    if (usedItem == ITEM_NONE  && item_frame == 1) break;
    if (usedItem == ITEM_BEER  && item_frame == 2) break;
    if (usedItem == ITEM_KNIFE && item_frame == 3) break;
    if (usedItem == ITEM_CIG   && item_frame == 5) break;
    if (usedItem == ITEM_MAG   && item_frame == 5) break;
  }
  game_state = STATE_PLAYER_TURN;
  tft.fillScreen(0x0000);
  drawGame();
}

void dealerUseItem(char itemIndex) {
  game_state = STATE_DEALER_ITEM;
  item_frame = 0;
  char usedItem = useItem(E_DEALER, itemIndex);
  tft.fillScreen(0x0000);
  drawGame();
  delay(1500);
  if (usedItem == ITEM_MAG || usedItem == ITEM_CIG) {
    item_frame++;
    drawGame();
    delay(1500);
  }
  game_state = STATE_DEALER_TURN;
}

void shootCallback(char shell, char whoGotShot) {
  if (shell == SHELL_LIVE) {
    if (whoGotShot == E_PLAYER) {
      for (char i = 0; i < 32; i++) {
        tft.fillScreen(vic_colors[random(16)]);
        delay(16);
      }
    } else {
      tft.fillScreen(VIC_BLACK);
      for (char i = 0; i < 8; i++) {
        drawDealer(vic_colors[random(16)], true);
      }
    }
  } else {
    delay(1000);
  }

  char dead = whoIsDead();
  if (dead != E_NONE) {
    tft.fillScreen(dead == E_PLAYER ? 0xE000 : 0x0EE0);
  } else if (nextRound()) {
    tft.fillScreen(0x0000);
    game_state = STATE_PLAYER_TURN;
    drawGame();
    delay(300);
    startRound();
  } else {
    game_state = getNextTurn(shell);
    tft.fillScreen(0x0000);
    drawGame();
    resetDealerTurn();
    handleDealer();
  }
  // TODO: do this part
  // if (dead == E_NONE) {}
}

void handleDealer() {
  if (game_state != STATE_DEALER_TURN) return;
  drawGame();
  delay(1750);
  char dealerAction = getDealerAction();
  if (dealerAction == DEALER_ACTION_SHOOT_P || dealerAction == DEALER_ACTION_SHOOT_D) {
    game_state = STATE_DEALER_SHOOT;
    tft.fillScreen(0x0000);
    drawGame();
    delay(1000);
    char whoGotShot = dealerAction == DEALER_ACTION_SHOOT_P ? E_PLAYER : E_DEALER;
    game_state = whoGotShot == E_PLAYER ? STATE_DEALER_SHOT_P : STATE_DEALER_SHOT_D;
    tft.fillScreen(0x0000);
    drawGame();
    delay(1750);
    char shell = shootGun(E_DEALER, whoGotShot);
    shootCallback(shell, whoGotShot);
  } else if (dealerAction == DEALER_ACTION_USE_ITEM) {
    dealerUseItem(desiredItemSlot);
    handleDealer();
  }
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
        playerUseItem(scene_selection - 1);
      }
    } else if (game_state == STATE_PLAYER_SHOOT) {
      char whoGotShot = scene_selection ? E_PLAYER : E_DEALER;
      scene_selection = 0;
      game_state = whoGotShot == E_PLAYER ? STATE_PLAYER_SHOT_P : STATE_PLAYER_SHOT_D;
      drawGame();
      delay(1750);
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
