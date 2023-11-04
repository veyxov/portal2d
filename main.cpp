#include "Game/Game.hpp"
#include "Game/GameObject.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <stdio.h>

Game *game = nullptr;

void create_obj(const char* texture_path, int x, int y) {
  ecs::entity cur_ent = ecs::create_entity();
  game->get_registry()->sprites[cur_ent] =
      ecs::sprite_component{SDL_Rect{0, 0, 202, 202}, SDL_Rect{x, y, 100, 100},
                       IMG_LoadTexture(Game::renderer, texture_path)};
  game->get_registry()->transforms[cur_ent] = ecs::transform_component{10, 20, 0, 0};
  game->get_registry()->keys[cur_ent] = ecs::key_component{};
}

int main() {
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;
  game = new Game();
  game->init();

  create_obj("assets/player.png", 111, 2);
  create_obj("assets/box.png", 2, 2);

  while (game->running()) {
    frameStart = SDL_GetTicks();

    game->handle_events();
    game->update();
    game->render();

    frameTime = SDL_GetTicks64() - frameStart;

    // NOTE: this causes collission errors sometimes
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
  game->clear();
}
