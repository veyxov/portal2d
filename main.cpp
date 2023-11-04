#include "Game/Game.hpp"
#include "Game/GameObject.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <stdio.h>

Game *game = nullptr;

int main() {
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;
  game = new Game();
  game->init();

  while (game->running()) {
    frameStart = SDL_GetTicks();

    game->handle_events();
    game->update();
    game->render();

    frameTime = SDL_GetTicks64() - frameStart;

    // NOTE: this causes collission errors sometimes
  }
  game->clear();
}
