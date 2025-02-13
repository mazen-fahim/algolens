#pragma once

#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>

#include "GameObject.hpp"

enum class BarState {
  SORTED,
  NOT_SORTED,
  BEING_COMPARED,
};

class Bar : public GameObject {
 public:
  Bar(int x, int y, int width, int height, int red, int green, int blue,
      int alpha, bool fill, BarState state);
  void draw();
  void render(SDL_Renderer *renderer);
  ~Bar() = default;

  void set_state(BarState state);
  BarState get_state();

 private:
  BarState m_state;
};
