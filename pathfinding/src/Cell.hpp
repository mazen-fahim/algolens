#pragma once

#include <SDL.h>
#include <SDL_render.h>

#include "GameObject.hpp"
#include "Renderer.hpp"

enum class CellState {
  VISITED,
  NOT_VISITED,
  SOURCE,
  TARGET,
  WALL,
};

class Cell : public GameObject {
 public:
  Cell(int x, int y, int width, int height, int red, int green, int blue,
       int alpha, bool fill);
  void draw();
  void render(SDL_Renderer *renderer);
  ~Cell() = default;

 private:
  CellState m_state;
};
