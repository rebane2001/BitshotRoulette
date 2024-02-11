#define SHELL_NONE  0
#define SHELL_LIVE  1
#define SHELL_BLANK 2

char shells[8] = {0, 0, 0, 0, 0, 0, 0, 0};
char shellCount = 0;
char liveShellCount = 0;
char blankShellCount = 0;

void generateShells() {
  shellCount = random(2, 9);
  liveShellCount = shellCount/2;
  blankShellCount = shellCount - liveShellCount;
  char liveShellsRemaining = liveShellCount;
  char blankShellsRemaining = blankShellCount;
  for (char i = 0; i < 8; i++) {
    if (i > shellCount - 1) {
      shells[i] = SHELL_NONE;
    } else if (liveShellsRemaining && (!blankShellsRemaining || random(2))) {
      shells[i] = SHELL_LIVE;
      liveShellsRemaining--;
    } else {
      shells[i] = SHELL_BLANK;
      blankShellsRemaining--;
    }
  }
}

char peekShell() {
  if (shellCount == 0) {
    Serial.println("Logic Error: Out of shells but trying to pop one"); 
    return 0;
  }
  return shells[shellCount - 1];
}

char popShell() {
  if (shellCount == 0) {
    Serial.println("Logic Error: Out of shells but trying to pop one"); 
    return 0;
  }
  char shell = shells[--shellCount];
  if (shell == SHELL_LIVE) {
    liveShellCount--; 
  } else if (shell == SHELL_BLANK) {
    blankShellCount--;
  }
  return shell;
}