#pragma once
#include <SDL3/SDL.h>

class GameObject {
  //  Constructor
 public:
  GameObject(float x, float y, float width, float height, int red, int green,
             int blue, int alpha, bool fill);

  // Update the object state
  virtual void draw() = 0;

  // Render the object to screen
  virtual void render(SDL_Renderer *renderer) = 0;

  // Needs to be virtual to avoid memory leaks
  virtual ~GameObject() = default;

  // Getters
  float get_x();
  float get_y();
  float get_width();
  float get_height();
  int get_red();
  int get_green();
  int get_blue();
  int get_alpha();
  int get_fill();

  // Setters
  void set_x(float x);
  void set_y(float y);
  void set_width(float width);
  void set_height(float height);
  void set_red(int red);
  void set_green(int green);
  void set_blue(int blue);
  void set_alpha(int alpha);
  void set_fill(bool fill);

 private:
  float m_x;
  float m_y;
  float m_width;
  float m_height;
  int m_red;
  int m_green;
  int m_blue;
  int m_alpha;
  bool m_fill;
};
