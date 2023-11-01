#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

// Screen dimension constants
static class Settings {
public:
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 720;
} Settings;

Game::Game() {}
Game::~Game() {}

void Game::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window = SDL_CreateWindow("main", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, Settings.SCREEN_WIDTH,
                              Settings.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window) {
      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer) {
        is_running = true;
      }
    }
  }
}

void Game::handle_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
        is_running = false;
      break;
    }
  }
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
