#include "Game/Game.hpp"

int main(int argc, char *argv[]) {
  cwt::game game(800, 600);

  const char *box_path = "assets/box.png";
  const char *player_path = "assets/player.png";

  cwt::entity box = cwt::create_entity();
  game.get_registry().sprites[box] =
      cwt::sprite_component{SDL_Rect{0, 0, 300, 230}, SDL_Rect{10, 10, 100, 73},
                            IMG_LoadTexture(game.get_renderer(), box_path)};
  game.get_registry().transforms[box] = cwt::transform_component{10, 10, 0, 0};
  //game.get_registry().keys[box] = cwt::keyinputs_component{};

  cwt::entity player = cwt::create_entity();
  game.get_registry().sprites[player] =
      cwt::sprite_component{SDL_Rect{0, 0, 300, 230}, SDL_Rect{10, 10, 100, 73},
                            IMG_LoadTexture(game.get_renderer(), player_path)};
  game.get_registry().transforms[player] =
      cwt::transform_component{10, 10, 0, 0};
  game.get_registry().keys[player] = cwt::keyinputs_component{};

  while (game.is_running()) {
    game.read_input();
    game.update();
    game.render();
  }

  return 0;
}
