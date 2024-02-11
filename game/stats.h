long long game_score = 0;
int stat_shots_fired = 0;
int stat_shells_ejected = 0;
int stat_cigarettes_smoked = 0;
int stat_ml_of_beer_drank = 0;
int stat_endless_rounds = 0;

void increaseScore() {
  if (game_score == 0) {
    game_score = 70000;
    game_score -= stat_cigarettes_smoked * 220;
    game_score -= stat_ml_of_beer_drank * 3 / 2;
  } else {
    game_score = game_score + game_score;
  }
}
