#pragma once

#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace cwt {

using entity = std::size_t;
entity max_entity = 0;
std::size_t create_entity() {
  static std::size_t entities = 0;
  ++entities;
  max_entity = entities;
  return entities;
}

struct sprite_component {
  SDL_Rect src;
  SDL_Rect dst;
  SDL_Texture *texture;
};

struct transform_component {
  float pos_x;
  float pos_y;
  float vel_x;
  float vel_y;
};

struct keyinputs_component {};

struct registry {
  std::unordered_map<entity, sprite_component> sprites;
  std::unordered_map<entity, transform_component> transforms;
  std::unordered_map<entity, keyinputs_component> keys;
};

struct sprite_system {
  void update(registry &reg) {
    for (int e = 1; e <= max_entity; e++) {
      if (reg.sprites.contains(e) && reg.transforms.contains(e)) {
        reg.sprites[e].dst.x = reg.transforms[e].pos_x;
        reg.sprites[e].dst.y = reg.transforms[e].pos_y;
      }
    }
  }
  void render(registry &reg, SDL_Renderer *renderer) {
    for (int e = 1; e <= max_entity; e++) {
      if (reg.sprites.contains(e)) {
        SDL_RenderCopy(renderer, reg.sprites[e].texture, &reg.sprites[e].src,
                       &reg.sprites[e].dst);
      }
    }
  }
};

struct transform_system {
  float dt = 0.1f;

  void update(registry &reg) {
    for (int e = 1; e <= max_entity; e++) {
      if (reg.transforms.contains(e)) {
        reg.transforms[e].pos_x += reg.transforms[e].vel_x * dt;
        reg.transforms[e].pos_y += reg.transforms[e].vel_y * dt;
      }
    }
  }
};

struct movement_system {
  void update(registry &reg) {
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

class game {
public:
  game(std::size_t width, std::size_t height)
      : m_width(width), m_height(height) {
    m_window =
        SDL_CreateWindow("sdl window", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, m_width, m_height, NULL);

    if (m_window == NULL) {
      std::cout << "Could not create window: " << SDL_GetError() << '\n';
      m_is_running = false;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!m_renderer) {
      std::cout << "Error creating SDL renderer.\n";
      m_is_running = false;
    }

    m_is_running = true;
  }
  ~game() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }

  registry &get_registry() { return m_registry; }
  SDL_Renderer *get_renderer() { return m_renderer; }

  bool is_running() { return m_is_running; }
  void read_input() {
    SDL_Event sdl_event;
    SDL_PollEvent(&sdl_event);
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_ESCAPE] || sdl_event.type == SDL_QUIT) {
      m_is_running = false;
    }
  }
  void update() {
    m_transform_system.update(m_registry);
    m_movement_system.update(m_registry);
    m_sprite_system.update(m_registry);
  }
  void render() {
    SDL_RenderClear(m_renderer);

    m_sprite_system.render(m_registry, m_renderer);

    SDL_RenderPresent(m_renderer);
  }

private:
  std::size_t m_width;
  std::size_t m_height;
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  bool m_is_running;

  registry m_registry;

  sprite_system m_sprite_system;
  transform_system m_transform_system;
  movement_system m_movement_system;
};
} // namespace cwt
