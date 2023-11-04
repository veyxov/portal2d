#include "ecs.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <iostream>

namespace ecs {
entity max_entity = 0;
std::size_t create_entity() {
  static entity entity = 0;
  ++entity;
  max_entity = entity;
  return entity;
}

void sprite_system::update(registry &reg) {
  for (int e = 1; e <= max_entity; ++e) {
    if (reg.sprites.contains(e) && reg.transforms.contains(e)) {
      auto &sprite = reg.sprites[e];
      auto &transform = reg.transforms[e];
      sprite.dest.x = transform.pos_x;
      sprite.dest.y = transform.pos_y;
    }
  }
}

void sprite_system::render(registry &reg, SDL_Renderer *renderer) {
  static int i = 0;
  ++i;
  for (int e = 1; e <= max_entity; ++e) {
    reg.sprites[e].dest.x += i;
    if (reg.sprites.contains(e)) {
      SDL_RenderCopy(renderer, reg.sprites[e].texture, &reg.sprites[e].src,
                     &reg.sprites[e].dest);
    }
  }
}

void transform_system::update(registry &reg) {
  for (int e = 1; e <= max_entity; ++e) {
    if (reg.transforms.contains(e)) {
      auto &cur = reg.transforms[e];
      cur.pos_x += cur.vel_x * dt;
      cur.pos_y += cur.vel_y * dt;
    }
  }
}

void movement_system::update(registry &reg) {
  const Uint8 *keys = SDL_GetKeyboardState(NULL);

  for (int e = 1; e <= max_entity; e++) {
    if (reg.transforms.contains(e) && reg.keys.contains(e)) {
      if (keys[SDL_SCANCODE_A]) {
        reg.transforms[e].vel_x = -1.0f;
      }
      if (keys[SDL_SCANCODE_S]) {
        reg.transforms[e].vel_y = 1.0f;
      }
      if (keys[SDL_SCANCODE_W]) {
        reg.transforms[e].vel_y = -1.0f;
      }
      if (keys[SDL_SCANCODE_D]) {
        reg.transforms[e].vel_x = 1.0f;
      }
      if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
        reg.transforms[e].vel_x = 0.0f;
      }
      if (!keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) {
        reg.transforms[e].vel_y = 0.0f;
      }

      // also handle quit
      if (keys[SDL_SCANCODE_Q]) {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
      }
    }
  }
}
} // namespace ecs
