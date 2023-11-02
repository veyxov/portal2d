#include "Game.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

// Screen dimension constants
static class Settings {
public:
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 720;
} Settings;

Game::Game() {}
Game::~Game() {}

GameObject *player;

void Game::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window = SDL_CreateWindow("main", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, Settings.SCREEN_WIDTH,
                              Settings.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window) {
      IMG_Init(IMG_INIT_PNG);
      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer) {
        is_running = true;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      }
    }
    player = new GameObject("player.png", renderer);
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
  player->render();
  SDL_RenderPresent(renderer);
}

void Game::clear() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::update() {}
