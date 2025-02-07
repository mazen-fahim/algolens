#include "init.hpp"

#include <SDL_render.h>
#include <SDL_video.h>

#include <iostream>
using namespace std;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void kill() {
  // Quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool init(SDL_Window **window, const char *title, int w, int h,
          Uint32 windowFlags, SDL_Renderer **renderer, Uint32 rendererFlags) {
  // will use rand() in coinFlip function
  srand((unsigned int)time(NULL));

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Failed to initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  // Create window
  *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, w, h, windowFlags);
  if (!window) {
    cout << "Error creating window: " << SDL_GetError() << endl;
    return false;
  }

  // Create renderer
  *renderer = SDL_CreateRenderer(*window, -1, rendererFlags);
  if (!renderer) {
    cout << "Error creating renderer: " << SDL_GetError() << endl;
    return false;
  }
  return true;
}
