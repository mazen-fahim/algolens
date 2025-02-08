#pragma once
#include <SDL.h>
#include <SDL_rect.h>

#include "Renderer.hpp"

class GameObject {
  //  Constructor
 public:
  GameObject(int x, int y, int width, int height, int red, int green, int blue,
             int alpha, bool fill);

  // Update the object state
  virtual void draw() = 0;

  // Render the object to screen
  virtual void render(const Renderer &renderer) = 0;

  // Needs to be virtual to avoid memory leaks
  virtual ~GameObject();

  // Getters
  int get_x();
  int get_y();
  int get_width();
  int get_height();
  int get_red();
  int get_green();
  int get_blue();
  int get_alpha();
  int get_fill();
  SDL_Rect *get_rect();

  // Setters
  void set_x(int x);
  void set_y(int y);
  void set_width(int width);
  void set_height(int height);
  void set_red(int red);
  void set_green(int green);
  void set_blue(int blue);
  void set_alpha(int alpha);
  void set_fill(bool fill);
  void set_rect(SDL_Rect *rect);

 private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;
  int m_red;
  int m_green;
  int m_blue;
  int m_alpha;
  bool m_fill;
  SDL_Rect *m_rect;
};
