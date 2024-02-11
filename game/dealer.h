#define DEALER_ACTION_NONE     0
#define DEALER_ACTION_SHOOT_P  1
#define DEALER_ACTION_SHOOT_D  2
#define DEALER_ACTION_USE_ITEM 3

// Defined in define.h
// char knowShell = SHELL_NONE;
char dealerTarget = E_NONE;
char desiredItemSlot = 0;

// This function name is a bit misleading
// because it gets called regardless of
// whose turn it is.
void resetDealerTurn() {
  knowShell = SHELL_NONE;
  dealerTarget = E_NONE;
  desiredItemSlot = 0;
}

// The dealer logic is recreated
// 1:1 from the original
char getDealerAction() {
  char desiredItem = ITEM_NONE;
  if (shellCount == 1)
    knowShell = peekShell();
  if (knowShell != SHELL_NONE)
    dealerTarget = knowShell == SHELL_LIVE ? E_PLAYER : E_DEALER;
  for (char i = 0; i < 8; i++) {
    switch (dealer_items[i]) {
      case ITEM_MAG:
        if (knowShell == SHELL_NONE)
          desiredItem = ITEM_MAG;
        break;
      case ITEM_CIG:
        if (dealerHealth < HEALTH_MAX)
          desiredItem = ITEM_CIG;
        break;
      case ITEM_BEER:
        if (knowShell != SHELL_LIVE && shellCount > 1) {
          desiredItem = ITEM_BEER;
          // fix not present in original game
          knowShell = SHELL_NONE;
        }
        break;
      case ITEM_CUFFS:
        if (who_cuffed != E_PLAYER && shellCount > 1)
          desiredItem = ITEM_CUFFS;
        break;
      case ITEM_KNIFE:
        if (!handsawActive && knowShell == SHELL_LIVE)
          desiredItem = ITEM_KNIFE;
        break;
    }
    if (desiredItem != ITEM_NONE) {
      desiredItemSlot = i;
      return DEALER_ACTION_USE_ITEM;
    }
  }

  for (char i = 0; i < 8; i++) {
    if (dealer_items[i] == ITEM_KNIFE && !handsawActive && knowShell != SHELL_BLANK) {
      dealerTarget = E_DEALER;
      if (random(2)) {
        dealerTarget = E_PLAYER;
        desiredItem = ITEM_KNIFE;
        desiredItemSlot = i;
        return DEALER_ACTION_USE_ITEM;
      }
      break;
    }
  }

  if (dealerTarget == E_NONE) dealerTarget = (amongus_mode || random(2)) ? E_PLAYER : E_DEALER;
  return dealerTarget == E_PLAYER ? DEALER_ACTION_SHOOT_P : DEALER_ACTION_SHOOT_D;
}
