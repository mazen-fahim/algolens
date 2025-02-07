#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL2/SDL.h>
#include "LinkedList.h"

typedef struct WindowGlobal{
    SDL_Window *window;
    int windowWidth;
    int windowHeight;
}WindowGlobal;

// Defined in Init.c
extern SDL_Renderer *rendererGlobal;
extern WindowGlobal windowGlobal;

// Defined in GameObjects.c
extern List lines;
extern List rectangles;
extern List polygons;

#endif
