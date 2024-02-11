#define STATE_SHELL_CHECK   0
#define STATE_PLAYER_TURN   1
#define STATE_PLAYER_SHOOT  2
#define STATE_PLAYER_SHOT_D 3
#define STATE_PLAYER_SHOT_P 4
#define STATE_PLAYER_ITEM   6
#define STATE_DEALER_TURN   7
#define STATE_DEALER_SHOOT  8
#define STATE_DEALER_SHOT_D 9
#define STATE_DEALER_SHOT_P 9
#define STATE_DEALER_ITEM   10
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

char who_cuffed = E_NONE;

bool handsawActive = false;

char shootGun(char whoShot, char whoGotShot) {
  char shell = popShell();
  if (shell == SHELL_LIVE)
    changeHealth(whoGotShot, handsawActive ? -2 : -1);
  handsawActive = false;
  return shell;
}

char whoIsDead() {
  if (!dealerHealth) return E_DEALER;
  if (!playerHealth) return E_PLAYER;
  return E_NONE;
}

bool nextRound() {
  return shellCount == 0;
}

char getNextTurn(char shell) {
  if (game_state == STATE_PLAYER_SHOT_P && shell == SHELL_BLANK) return STATE_PLAYER_TURN;
  if (game_state == STATE_DEALER_SHOT_D && shell == SHELL_BLANK) return STATE_DEALER_TURN;
  if ((game_state == STATE_PLAYER_SHOT_P || game_state == STATE_PLAYER_SHOT_D) && who_cuffed == E_DEALER) {
    who_cuffed = E_NONE;
    return STATE_PLAYER_TURN;
  }
  if ((game_state == STATE_DEALER_SHOT_P || game_state == STATE_DEALER_SHOT_D) && who_cuffed == E_PLAYER) {
    who_cuffed = E_NONE;
    return STATE_DEALER_TURN;
  }
  return (game_state == STATE_PLAYER_SHOT_P || game_state == STATE_PLAYER_SHOT_D) ? STATE_DEALER_TURN : STATE_PLAYER_TURN;
}

void useItem(char entity, char itemIndex) {
  // TODO: check if item use is allowed
  char used_item = (entity == E_PLAYER ? player_items : dealer_items)[itemIndex];
  switch (used_item) {
    case ITEM_MAG:
      knowShell = peekShell();
      break;
    case ITEM_CIG:
      changeHealth(entity, 1);
      break;
    case ITEM_BEER:
      popShell();
      // TODO: check for whether round is over now
      break;
    case ITEM_CUFFS:
      if (who_cuffed != E_NONE) return ITEM_NONE;
      who_cuffed = entity == E_PLAYER ? E_DEALER : E_PLAYER;
      break;
    case ITEM_KNIFE:
      handsawActive = true;
      break;
  }
  (entity == E_PLAYER ? player_items : dealer_items)[itemIndex] = ITEM_NONE;
  return used_item;
}
