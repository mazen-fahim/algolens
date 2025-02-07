#ifndef INIT_H_
#define INIT_H_
#include <SDL2/SDL.h>
#include <stdbool.h>

bool init(SDL_Window **window,const char *title, int w, int h, Uint32 windowFlags, 
        SDL_Renderer **renderer, Uint32 rendererFlags);

#endif
