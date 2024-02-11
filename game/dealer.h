#define DEALER_ACTION_NONE    0
#define DEALER_ACTION_SHOOT_P 1
#define DEALER_ACTION_SHOOT_D 2

char getDealerAction() {
  return (random(0,2) == 0) ? DEALER_ACTION_SHOOT_P : DEALER_ACTION_SHOOT_D;
}
