#include "Game.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include "Settings.cpp"

Game::Game() {}
Game::~Game() {}

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

void Game::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window = SDL_CreateWindow("main", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, Settings.SCREEN_WIDTH,
                              Settings.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window) {
      IMG_Init(IMG_INIT_PNG);
      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer) {
        m_is_running = true;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      }
    }
  }
}

ecs::registry* Game::get_registry() {
    return &m_registry;
}

void Game::handle_events() {

}

void Game::update() {
    m_transform_system.update(m_registry);
    m_movement_system.update(m_registry);
    m_sprite_system.update(m_registry);
}

void Game::render() {
  SDL_RenderClear(renderer);
  m_sprite_system.render(m_registry, renderer);
  SDL_RenderPresent(renderer);
}

void Game::clear() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
