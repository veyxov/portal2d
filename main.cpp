#include "Game/Game.hpp"

int main(int argc, char* argv[]) 
{
    cwt::game game(800, 600);

    const char* box_path = "assets/box.png";
    const char* player_path = "assets/player.png";

    cwt::entity box_1 = cwt::create_entity();
    game.get_registry().sprites[box_1] = cwt::sprite_component {
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{10, 10, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), box_path)
    };
    game.get_registry().transforms[box_1] = cwt::transform_component { 10, 10, 0, 0};
    game.get_registry().keys[box_1] = cwt::keyinputs_component { };

    cwt::entity box_2 = cwt::create_entity();
    game.get_registry().sprites[box_2] = cwt::sprite_component {
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{0, 0, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), player_path)
    };
    game.get_registry().transforms[box_2] = cwt::transform_component { 10, 500, 0.01f, -0.01f};

    cwt::entity box_3 = cwt::create_entity();
    game.get_registry().sprites[box_3] = cwt::sprite_component {
        SDL_Rect{0, 0, 300, 230}, 
        SDL_Rect{200, 300, 100, 73}, 
        IMG_LoadTexture(game.get_renderer(), box_path)
    };

    while(game.is_running()) 
    {
        game.read_input();
        game.update();
        game.render();
    }
    
    return 0;
}
