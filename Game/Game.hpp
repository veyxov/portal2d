#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <unordered_map>
#include "ecs.hpp"

class Game {
public:
  Game();
  ~Game();
  void init();
  void handle_events();
  void update();
  void render();
  void clear();
  bool running() { return m_is_running; }

  ecs::registry *get_registry();

  static SDL_Renderer *renderer;
  static SDL_Event event;

private:
  bool m_is_running = false;
  SDL_Window *window = NULL;

  ecs::registry m_registry;
  ecs::sprite_system m_sprite_system;
  ecs::transform_system m_transform_system;
  ecs::movement_system m_movement_system;
};
