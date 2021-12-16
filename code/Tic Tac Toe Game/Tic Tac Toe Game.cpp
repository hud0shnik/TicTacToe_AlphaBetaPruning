#include "Game.h"

int main() {
  //setlocale(LC_ALL, "rus");

  srand(time(NULL));

  Game game;
  game.Logic();
}