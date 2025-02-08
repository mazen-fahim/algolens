#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>

#include <iostream>
#include <vector>

#include "defs.hpp"
#include "init.hpp"
#include "maze.hpp"
using namespace std;

SDL_Rect mtrx[NUMBER_OF_CELLS_R][NUMBER_OF_CELLS_C];

void handle_input() {}

void update(float elapsed) { return; }
void draw();

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int main() {
  /***** Initialization (window and renderer) ******/
  SDL_Window *window;
  SDL_Renderer *renderer;
  const unsigned windowWidth = 680;
  const unsigned windowHeight = 420;
  const char *title = "Pong";
  Uint32 windowFlags = SDL_WINDOW_SHOWN;
  if (!init(&window, title, windowWidth, windowHeight, windowFlags, &renderer,
            rendererFlags)) {
    kill();
    exit(1);
  }

  /***** Create the maze *****/
  Maze maze = Maze(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0);

  /***** Start the game loop *****/
  SDL_Event event;
  bool quit = false;
  Uint32 lastTick = SDL_GetTicks();
  Uint32 currentTick = 0;
  Uint32 diff = 0;
  float elapsed = 0;

  while (!quit) {
    // event loop
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEMOTION:
          break;
        case SDL_MOUSEBUTTONDOWN:
          break;
      }
    }

    if (!quit) {
      currentTick = SDL_GetTicks();
      diff = currentTick - lastTick;
      elapsed = diff / 1000.0f;
      maze.update();
      renderer.draw(maze);
      lastTick = currentTick;
      SDL_Delay(100);
    }
  }

  /***** Free memory *****/
  kill();
  return 0;
}
