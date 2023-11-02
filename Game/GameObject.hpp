#include <SDL2/SDL.h>

class GameObject {
public:
  GameObject(const char* textureSheet);
  ~GameObject();
  void update();
  void render();

  private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
