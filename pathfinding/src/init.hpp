#ifndef INIT_H
#define INIT_H
#include <SDL.h>

void kill();
bool init(SDL_Window **window, const char *title, int w, int h,
          Uint32 windowFlags, SDL_Renderer **renderer, Uint32 rendererFlags);
#endif
