#include "GameObject.hpp"

GameObject::GameObject(float x, float y, float width, float height, int red,
                       int green, int blue, int alpha, bool fill)
    : m_x{x},
      m_y{y},
      m_width{width},
      m_height{height},
      m_red{red},
      m_green{green},
      m_blue{blue},
      m_alpha{alpha},
      m_fill{fill} {}

// Getters
float GameObject::get_x() { return m_x; }
float GameObject::get_y() { return m_y; }
float GameObject::get_width() { return m_width; }
float GameObject::get_height() { return m_height; }
int GameObject::get_red() { return m_red; }
int GameObject::get_green() { return m_green; }
int GameObject::get_blue() { return m_blue; }
int GameObject::get_alpha() { return m_alpha; }
int GameObject::get_fill() { return m_fill; }

// Setters
void GameObject::set_x(float x) { m_x = x; }
void GameObject::set_y(float y) { m_y = y; }
void GameObject::set_width(float width) { m_width = width; }
void GameObject::set_height(float height) { m_height = height; }
void GameObject::set_red(int red) { m_red = red; }
void GameObject::set_green(int green) { m_green = green; }
void GameObject::set_blue(int blue) { m_blue = blue; }
void GameObject::set_alpha(int alpha) { m_alpha = alpha; }
void GameObject::set_fill(bool fill) { m_fill = fill; }
