#include <SDL2/SDL.h>

class GameObject {
public:
  GameObject(const char* textureSheet);
  ~GameObject();
  void update();
  void render();

    int xpos = 0;
    int ypos = 0;
  private:

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
