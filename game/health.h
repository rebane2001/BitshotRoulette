#define HEALTH_START 4
#define HEALTH_MAX   4

char playerHealth = HEALTH_START;
char dealerHealth = HEALTH_START;

void changeHealth(char entity, signed char amount) {
  char health = (entity == E_PLAYER) ? playerHealth : dealerHealth;
  if (amount < 0 && health < -amount) {
    health = 0;
  } else {
    health += amount;
  }
  if (health > HEALTH_MAX)
    health = HEALTH_MAX;
  if (entity == E_PLAYER) {
    playerHealth = health;
  } else {
    dealerHealth = health;
  }
}
