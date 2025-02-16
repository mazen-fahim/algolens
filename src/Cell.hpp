#pragma once

#include "GameObject.hpp"

enum class CellState {
  VISITED,
  NOT_VISITED,
  SOURCE,
  TARGET,
  WALL,
  SHORTEST_PATH,
};

class Cell : public GameObject {
 public:
  Cell(float x, float y, float width, float height, int red, int green,
       int blue, int alpha, bool fill, CellState state);
  void draw();
  void render(SDL_Renderer *renderer);
  ~Cell() = default;

  void set_state(CellState state);
  CellState get_state();

 private:
  CellState m_state;
};
