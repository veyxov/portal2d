#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimension constants
static class Settings {
public:
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 720;
} Settings;

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;

  SDL_Surface *screenSurface = NULL;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    // Create window
    window = SDL_CreateWindow("Main", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, Settings.SCREEN_WIDTH,
                              Settings.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window != NULL) {
      // Get window surface
      screenSurface = SDL_GetWindowSurface(window);

      // Update the surface
      SDL_UpdateWindowSurface(window);

      // Hack to get window to stay up
      SDL_Event e;
      bool quit = false;
      while (quit == false) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT)
            quit = true;
        }
      }
    } else {
      printf("SDL_Error: %s\n", SDL_GetError());
    }
  } else {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
