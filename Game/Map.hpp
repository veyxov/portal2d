#include "Game.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL_render.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
enum class MapCell {
  Empty = 0,
  Wall = 1,
};

class Map {
public:
  Map(std::string path) {

    std::ifstream file(path);

    if (!file.is_open()) {
      std::cerr << "could not open file: " << path;
      return;
    }

    std::string line;

    while (std::getline(file, line)) {
      std::vector<MapCell> row;
      for (const auto &c : line) {
        MapCell cur;
        switch (c) {
        case ' ':
          cur = MapCell::Empty;
          break;
        case '#':
          cur = MapCell::Wall;
          break;
        default:
          std::cerr << "cannot parse: " << c << " for a map tile\n";
          return;
        }
        row.push_back(cur);
      }
      m_map.push_back(row);
    }
  }
  std::vector<cwt::entity> to_game_objects(cwt::game& game) {
    std::vector<cwt::entity> entities;
    for (int i = 0; i < m_map.size(); ++i) {
      for (int j = 0; j < m_map[i].size(); ++j) {
          if (m_map[i][j] == MapCell::Wall) {
              GameObject cur(game, "assets/wall.png", i + 10, j + 10, false);
          }
      }
    }
  GameObject player(game, "assets/wall.png", 100, 100, true);

    return entities;
  }
  ~Map() { std::cerr << "not implemented!"; }

private:
  std::vector<std::vector<MapCell>> m_map;
};
