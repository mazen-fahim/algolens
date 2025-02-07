#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "../include/LinkedList.h"
#include "../include/globals.h"

WindowGlobal windowGlobal;
SDL_Renderer *rendererGlobal = NULL;
static void shutDown(void){
    if(rendererGlobal){
        SDL_DestroyRenderer(rendererGlobal);
    }
    if(windowGlobal.window){
        SDL_DestroyWindow(windowGlobal.window);
    }
    if(rectangles.size != 0){
        list_destroy(&rectangles);
    }
    if(lines.size != 0){
        list_destroy(&lines);
    }

    if(lines.size != 0){
        list_destroy(&polygons);
    }

    SDL_Quit();
}

bool init(SDL_Window **window,const char *title, int w, int h, Uint32 windowFlags, 
        SDL_Renderer **renderer, Uint32 rendererFlags){
    // will use rand() in coinFlip function
    srand((unsigned int)time(NULL));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    // Create window
    *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            w, h, windowFlags);
    if(!window){
        return false;
    }
    windowGlobal.window = *window;
    windowGlobal.windowWidth = w;
    windowGlobal.windowHeight = h;

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, rendererFlags);
    if(!renderer){
        return false;
    }
    rendererGlobal = *renderer;

    // set shutDown as a callback when exiting
    atexit(shutDown);
    return true;
}

bool coinFlip(void){return rand() % 2 == 1? true : false;}
