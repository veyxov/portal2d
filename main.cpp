#include "Game/Game.hpp"
#include "Game/GameObject.hpp"

int main(int argc, char *argv[]) {
  cwt::game game(800, 600);

  GameObject box(game, "assets/box.png", 10, 10);
  GameObject player(game, "assets/player.png", 100, 100, true);

  while (game.is_running()) {
    game.read_input();
    game.update();
    game.render();
  }

  return 0;
}
