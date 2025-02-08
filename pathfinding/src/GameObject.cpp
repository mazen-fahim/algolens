#include "GameObject.hpp"

GameObject::GameObject(int x, int y, int width, int height, int red, int green,
                       int blue, int alpha, bool fill)
    : m_x{x},
      m_y{y},
      m_width{width},
      m_height{height},
      m_red{red},
      m_green{green},
      m_blue{blue},
      m_alpha{alpha},
      m_fill{fill} {
  m_rect = new SDL_Rect;
  m_rect->x = x;
  m_rect->y = y;
  m_rect->w = width;
  m_rect->h = height;
}

GameObject::~GameObject() { delete m_rect; }

// Getters
int GameObject::get_x() { return m_x; }
int GameObject::get_y() { return m_y; }
int GameObject::get_width() { return m_width; }
int GameObject::get_height() { return m_height; }
int GameObject::get_red() { return m_red; }
int GameObject::get_green() { return m_green; }
int GameObject::get_blue() { return m_blue; }
int GameObject::get_alpha() { return m_alpha; }
int GameObject::get_fill() { return m_fill; }
SDL_Rect *GameObject::get_rect() { return m_rect; }

// Setters
void GameObject::set_x(int x) { m_x = x; }
void GameObject::set_y(int y) { m_y = y; }
void GameObject::set_width(int width) { m_width = width; }
void GameObject::set_height(int height) { m_height = height; }
void GameObject::set_red(int red) { m_red = red; }
void GameObject::set_green(int green) { m_green = green; }
void GameObject::set_blue(int blue) { m_blue = blue; }
void GameObject::set_alpha(int alpha) { m_alpha = alpha; }
void GameObject::set_fill(bool fill) { m_fill = fill; }
void GameObject::set_rect(SDL_Rect *rect) { m_rect = rect; }
