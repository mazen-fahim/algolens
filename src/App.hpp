#pragma once
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>

class App {
 public:
  static int window_width;
  static int window_height;
  static SDL_WindowFlags window_flags;
  static char window_title[];
  static SDL_RendererFlags renderer_flags;
};
