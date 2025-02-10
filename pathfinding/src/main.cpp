#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>

#include <iostream>

#include "EventHandler.hpp"
#include "Maze.hpp"
#include "defs.hpp"
using namespace std;

SDL_Rect mtrx[NUMBER_OF_CELLS_R][NUMBER_OF_CELLS_C];

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void kill() {
  // Quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main() {
  /***** Initialization (window and renderer) ******/
  srand((unsigned int)time(NULL));

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    printf("Failed to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Create window
  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    cout << "Error creating window: " << SDL_GetError() << endl;
    exit(1);
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    cout << "Error creating renderer: " << SDL_GetError() << endl;
    exit(1);
  }

  /***** Create the maze *****/
  Maze maze = Maze(25, 40);
  maze.set_algorithm("dfs");

  /***** Start the game loop *****/
  EventHandler event_handler;
  SDL_Event event;
  bool quit = false;
  Uint32 lastTick = SDL_GetTicks();
  Uint32 currentTick = 0;
  Uint32 diff = 0;
  float elapsed = 0;

  while (!quit) {
    // event loop
    while (SDL_PollEvent(&event)) {
      event_handler.set_event(event);
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEMOTION:
          event_handler.handle_mouse_motition(maze);
          break;
        case SDL_MOUSEBUTTONDOWN:
          event_handler.handle_mouse_down(maze);
          break;
        case SDL_MOUSEBUTTONUP:
          event_handler.handle_mouse_up(maze);
          break;
      }
    }

    if (!quit) {
      currentTick = SDL_GetTicks();
      diff = currentTick - lastTick;
      elapsed = diff / 1000.0f;
      SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
      SDL_RenderClear(renderer);
      maze.draw();
      maze.render(renderer);
      SDL_RenderPresent(renderer);
      lastTick = currentTick;
      SDL_Delay(16 - elapsed);  // 60 fps
    }
  }

  /***** Free memory *****/
  kill();
  return 0;
}
