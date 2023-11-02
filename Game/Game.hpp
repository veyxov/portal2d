#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
class Game {
    public:
        Game();
        ~Game();
        void init();
        void handle_events();
        void update();
        void render();
        void clear();
        bool running() { return is_running; }
        static SDL_Renderer *renderer;
    private:
        bool is_running = false;
        SDL_Window *window = NULL;
};
