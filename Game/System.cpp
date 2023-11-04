#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <cstddef>
#include <unordered_map>
using entity = std::size_t;

entity max_entity = 0;

std::size_t create_entity() {
  static entity entity = 0;
  ++entity;
  max_entity = entity;

  return entity;
}

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
  void update(registry &reg) {
    for (int e = 1; e <= max_entity; ++e) {
      if (reg.sprites.contains(e) && reg.transforms.contains(e)) {
        auto &sprite = reg.sprites[e];
        auto &transform = reg.transforms[e];

        sprite.dest.x = transform.pos_x;
        sprite.dest.y = transform.pos_y;
      }
    }
  }

  void render(registry &reg, SDL_Renderer *renderer) {
    for (int e = 1; e <= max_entity; ++e) {
      if (reg.sprites.contains(e)) {
        SDL_RenderCopy(renderer, reg.sprites[e].texture, &reg.sprites[e].src,
                       &reg.sprites[e].dest);
      }
    }
  }
};

struct transform_system {
  const float dt = 0.1f;
  void update(registry &reg) {
    for (int e = 1; e <= max_entity; ++e) {
      if (reg.transforms.contains(e)) {
        auto &cur = reg.transforms[e];

        cur.pos_x += cur.vel_x * dt;
        cur.pos_y += cur.vel_y * dt;
      }
    }
  }
};

struct movement_system {
  void update(registry &reg) {
    // here we get an array of all keys from sdl
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
      }
    }
  }
};
