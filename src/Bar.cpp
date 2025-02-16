#include "Bar.hpp"

Bar::Bar(float x, float y, float width, float height, int red, int green,
         int blue, int alpha, bool fill, BarState state)
    : GameObject(x, y, width, height, red, green, blue, alpha, fill),
      m_state{state} {}

void Bar::draw() {
  if (m_state == BarState::SORTED) {
    set_red(171);
    set_green(235);
    set_blue(125);
    set_alpha(255);
    set_fill(true);
  } else if (m_state == BarState::NOT_SORTED) {
    set_red(238);
    set_green(69);
    set_blue(64);
    set_alpha(255);
    set_fill(true);
  } else if (m_state == BarState::BEING_COMPARED) {
    set_red(54);
    set_green(23);
    set_blue(77);
    set_alpha(255);
    set_fill(true);
  }
}

void Bar::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, get_red(), get_green(), get_blue(),
                         get_alpha());
  SDL_FRect rect = {get_x(), get_y(), get_width(), get_height()};
  if (get_fill())
    SDL_RenderFillRect(renderer, &rect);
  else
    SDL_RenderRect(renderer, &rect);
}

void Bar::set_state(BarState state) { m_state = state; }
BarState Bar::get_state() { return m_state; }
