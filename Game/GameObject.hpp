#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#pragma once

class GameObject {
public:
  GameObject(cwt::game &game, const char *texture_path, int x, int y, bool has_keys = false) {
    cwt::entity ent = cwt::create_entity();

    auto& registry = game.get_registry();
    registry.sprites[ent] = cwt::sprite_component{
        SDL_Rect{0, 0, width, height}, SDL_Rect{x, y, width, height},
        IMG_LoadTexture(game.get_renderer(), texture_path)};

    registry.transforms[ent] =
        cwt::transform_component{(float)x, (float)y, 0, 0};

    if (has_keys) {
        registry.keys[ent] = cwt::keyinputs_component{};
    }
  }

private:
  int height = 100;
  int width = 100;
};
