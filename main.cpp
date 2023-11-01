#include "Game/Game.hpp"
#include <stdio.h>

Game *game = nullptr;

int main(int argc, char *args[]) {
  game = new Game();
  game->init();

  while (game->running()) {
    game->handle_events();
    game->update();
    game->render();
  }
  game->clear();
}
