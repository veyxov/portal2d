#include "GameObject.hpp"
#include "Game.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>

GameObject::GameObject(const char *textureSheet, int x, int y) {
  srcRect.h = 32;
  srcRect.w = 32;
  srcRect.x = 0;
  srcRect.y = 0;

  destRect.h = xpos = 32;
  destRect.w = ypos = 32;
  destRect.x = x;
  destRect.y = y;
  objTexture = IMG_LoadTexture(Game::renderer, textureSheet);
}

GameObject::~GameObject() {}

void GameObject::update() {
  destRect.x = xpos;
  destRect.y = ypos;
}

void GameObject::render() {
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
