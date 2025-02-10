#include "Cell.hpp"

#include <SDL_rect.h>
#include <SDL_render.h>

Cell::Cell(int x, int y, int width, int height, int red, int green, int blue,
           int alpha, bool fill, CellState state)
    : GameObject(x, y, width, height, red, green, blue, alpha, fill),
      m_state{state} {}

void Cell::draw() {
  if (m_state == CellState::VISITED) {
    set_red(54);
    set_blue(23);
    set_green(77);
    set_alpha(255);
    set_fill(true);
  } else if (m_state == CellState::NOT_VISITED) {
    set_red(0);
    set_blue(0);
    set_green(0);
    set_alpha(255);
    set_fill(false);
  } else if (m_state == CellState::TARGET) {
    set_red(238);
    set_green(69);
    set_blue(64);
    set_alpha(255);
    set_fill(true);
  } else if (m_state == CellState::SOURCE) {
    set_red(171);
    set_green(235);
    set_blue(125);
    set_alpha(255);
    set_fill(true);
  } else if (m_state == CellState::WALL) {
    set_red(0);
    set_blue(0);
    set_green(0);
    set_alpha(0);
    set_fill(true);
  } else if (m_state == CellState::SHORTEST_PATH) {
    set_red(52);
    set_blue(46);
    set_green(68);
    set_alpha(255);
    set_fill(true);
  }
}

void Cell::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, get_red(), get_green(), get_blue(),
                         get_alpha());
  SDL_Rect rect = {get_x(), get_y(), get_width(), get_height()};
  if (get_fill())
    SDL_RenderFillRect(renderer, &rect);
  else
    SDL_RenderDrawRect(renderer, &rect);
}

void Cell::set_state(CellState state) { m_state = state; }
CellState Cell::get_state() { return m_state; }
