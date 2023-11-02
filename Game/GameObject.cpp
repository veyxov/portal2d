#include "GameObject.hpp"
#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>

GameObject::GameObject(const char *textureSheet) {
  srcRect.h = 32;
  srcRect.w = 32;
  srcRect.x = 0;
  srcRect.y = 0;

  destRect.h = 32;
  destRect.w = 32;
  destRect.x = 0;
  destRect.y = 0;
  objTexture = IMG_LoadTexture(Game::renderer, textureSheet);
}

GameObject::~GameObject() {}

void GameObject::update() {
  static int utsk = 0;
  xpos = 0 + utsk++;
  ypos = 0 + utsk++;
}

void GameObject::render() {
  objTexture = IMG_LoadTexture(Game::renderer, "assets/player.png");
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
