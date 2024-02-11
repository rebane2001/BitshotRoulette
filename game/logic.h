#define E_NONE   0
#define E_DEALER 1
#define E_PLAYER 2

char shootGun(char whoShot, char whoGotShot) {
  char shell = popShell();
  if (shell == SHELL_LIVE) {
    if (whoGotShot == E_PLAYER) {
      playerHealth--;
    } else {
      dealerHealth--;
    }
  }
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