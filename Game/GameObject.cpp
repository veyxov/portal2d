#include "GameObject.hpp"
#include "Game.hpp"
#include "Settings.cpp"
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

void GameObject::update(GameObject *box) {
  destRect.x = xpos;
  destRect.y = ypos;

  // also check for out of bounds
  if (this->xpos < 0) {
    this->xpos = 0;
  }
  if (this->xpos + this->destRect.w > Settings.SCREEN_WIDTH) {
    this->xpos = Settings.SCREEN_WIDTH - this->destRect.w;
  }
  if (this->ypos < 0) {
    this->ypos = 0;
  }
  if (this->ypos + this->destRect.h > Settings.SCREEN_HEIGHT) {
    this->ypos = Settings.SCREEN_HEIGHT - this->destRect.h;
  }

  // check for collision
  if (box == nullptr) {
    return;
  }
  if (this->xpos + this->destRect.w > box->xpos &&
      this->xpos<box->xpos + box->destRect.w &&this->ypos + this->destRect.h>
          box->ypos &&
      this->ypos < box->ypos + box->destRect.h) {

    // if there is a collision we should move the box in the direction
    // that the user is pussing towards
    if (this->xpos + this->destRect.w > box->xpos &&
        this->xpos < box->xpos + box->destRect.w) {
      if (this->ypos > box->ypos) {
        box->ypos -= 10;
      } else if (this->ypos < box->ypos) {
        box->ypos += 10;
      } else if (this->xpos > box->xpos) {
        box->xpos -= 10;
      } else if (this->xpos < box->xpos) {
        box->xpos += 10;
      }
    }
  }
}

void GameObject::render() {
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
