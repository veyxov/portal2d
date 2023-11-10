#include "Game.hpp"
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
  Map(std::string path, cwt::game &game) {
    m_renderer = game.get_renderer();

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
        default:
          std::cerr << "cannot parse: " << c << " for a map tile";
          return;
        }
        row.push_back(cur);
      }
      m_map.push_back(row);
    }
  }
  ~Map() {
      std::cerr << "not implemented!";
  }
  void render() const {
    const int cellSize = 20;

    for (size_t i = 0; i < m_map.size(); ++i) {
      for (size_t j = 0; j < m_map[i].size(); ++j) {
        SDL_Rect rect = {static_cast<int>(j * cellSize),
                         static_cast<int>(i * cellSize), cellSize, cellSize};

        // Adjust rendering based on your needs
        switch (m_map[i][j]) {
        case MapCell::Empty:
          SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // White
          break;
        case MapCell::Wall:
          SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Black
          break;
        }

        SDL_RenderFillRect(m_renderer, &rect);
      }
    }

    SDL_RenderPresent(m_renderer);
  }

private:
  std::vector<std::vector<MapCell>> m_map;
  SDL_Renderer *m_renderer;
};
