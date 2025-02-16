#ifndef RENDERER_H
#define RENDERER_H
#include "SDL3/SDL.h"

class Renderer {
 public:
  Renderer(SDL_Window *window);
  ~Renderer();
  void draw();

 private:
  SDL_Renderer *m_renderer;
};

#endif
