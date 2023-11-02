#include <SDL2/SDL.h>

class GameObject {
public:
  GameObject(const char* textureSheet, SDL_Renderer* ren);
  ~GameObject();
  void update();
  void render();

  private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
};
