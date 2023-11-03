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

GameObject *player;
GameObject *box;

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
        is_running = true;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      }
    }
    player = new GameObject("assets/player.png", 0, 0);
    box = new GameObject("assets/box.png", 100, 100);
  }
}

void Game::handle_events() {
  const int velocity = 10;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      is_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        is_running = false;
      }
      // check for arrow right
      if (event.key.keysym.sym == SDLK_RIGHT) {
        player->xpos += velocity;
      }
      // check for left
      if (event.key.keysym.sym == SDLK_LEFT) {
        player->xpos -= velocity;
      }
      // check for up
      if (event.key.keysym.sym == SDLK_UP) {
        player->ypos -= velocity;
      }
      // check for down
      if (event.key.keysym.sym == SDLK_DOWN) {
        player->ypos += velocity;
      }
      break;
    }
  }
}

void Game::update() {
    player->update(box);
    box->update();

}

void Game::render() {
  SDL_RenderClear(renderer);
  player->render();
  box->render();
  SDL_RenderPresent(renderer);
}

void Game::clear() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
