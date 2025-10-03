#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {

  Game game;

  if (game.initialize()) {
    game.run();
  }
}
