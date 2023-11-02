#include "GameObject.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <iostream>

GameObject::GameObject(const char* textureSheet, SDL_Renderer* ren) {
  renderer = ren;
  objTexture = IMG_LoadTexture(renderer, textureSheet);
}

GameObject::~GameObject() {}

void GameObject::update() {
    xpos = 0;
    ypos = 0;
}

void GameObject::render() {
objTexture = IMG_LoadTexture(renderer, "player.png");
  SDL_RenderCopy(renderer, objTexture, NULL, NULL);
  SDL_RenderPresent(renderer);
}
