#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
class Game {
    public:
        Game();
        ~Game();
        void init();
        void handle_events();
        void render();
        void clear();
    private:
        bool is_running = false;
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
};
