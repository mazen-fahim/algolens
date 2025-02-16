#pragma once

#include "GameObject.hpp"

enum class BarState {
  SORTED,
  NOT_SORTED,
  BEING_COMPARED,
};

class Bar : public GameObject {
 public:
  Bar(float x, float y, float width, float height, int red, int green, int blue,
      int alpha, bool fill, BarState state);
  void draw();
  void render(SDL_Renderer *renderer);
  ~Bar() = default;

  void set_state(BarState state);
  BarState get_state();

 private:
  BarState m_state;
};
