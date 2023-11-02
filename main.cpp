#include <SDL2/SDL_timer.h>
#include "Game/Game.hpp"
#include <stdio.h>

Game *game = nullptr;

int main(int argc, char *args[]) {
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

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
  game->clear();
}
