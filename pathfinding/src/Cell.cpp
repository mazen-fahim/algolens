#include "Cell.hpp"

#include <SDL_render.h>

Cell::Cell(int x, int y, int width, int height, int red, int green, int blue,
           int alpha, bool fill)
    : GameObject(x, y, width, height, red, green, blue, alpha, fill) {}

void Cell::draw() {
  //  if (m_state == CellState::VISITED) {
  //    set_red();
  //    set_blue();
  //    set_green();
  //    set_alpha();
  //    set_fill(true);
  //  } else if (m_state == CellState::NOT_VISITED) {
  //    set_red();
  //    set_blue();
  //    set_green();
  //    set_alpha();
  //    set_fill(false);
  //  } else if (m_state == CellState::TARGET) {
  //    set_red();
  //    set_blue();
  //    set_green();
  //    set_alpha();
  //    set_fill(true);
  //  } else if (m_state == CellState::SOURCE) {
  //    set_red();
  //    set_blue();
  //    set_green();
  //    set_alpha();
  //    set_fill(true);
  //  } else if (m_state == CellState::WALL) {
  //    set_red();
  //    set_blue();
  //    set_green();
  //    set_alpha();
  //    set_fill(true);
  //  }
}

void Cell::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, get_red(), get_green(), get_blue(),
                         get_alpha());
  if (get_fill()) SDL_RenderFillRect(renderer, get_rect());
}
