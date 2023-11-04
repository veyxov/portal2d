#pragma once

#include <SDL2/SDL_render.h>
#include <cstddef>
#include <unordered_map>

namespace ecs {
  using entity = std::size_t;

  std::size_t create_entity();

  struct sprite_component {
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture *texture;
  };

  struct transform_component {
    float pos_x;
    float pos_y;
    float vel_x;
    float vel_y;
  };

  struct key_component {};

  struct registry {
    std::unordered_map<entity, sprite_component> sprites;
    std::unordered_map<entity, transform_component> transforms;
    std::unordered_map<entity, key_component> keys;
  };

  struct sprite_system {
    void update(registry &reg);
    void render(registry &reg, SDL_Renderer *renderer);
  };

  struct transform_system {
    const float dt = 0.1f;
    void update(registry &reg);
  };

  struct movement_system {
    void update(registry &reg);
  };
}
