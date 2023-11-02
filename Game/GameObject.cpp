#include "GameObject.hpp"
#include "Game.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <iostream>

GameObject::GameObject(const char* textureSheet) {
  objTexture = IMG_LoadTexture(Game::renderer, textureSheet);
}

GameObject::~GameObject() {}

void GameObject::update() {
    xpos = 0;
    ypos = 0;
}

void GameObject::render() {
objTexture = IMG_LoadTexture(Game::renderer, "assets/player.png");
  SDL_RenderCopy(Game::renderer, objTexture, NULL, NULL);
}
