#include <SDL2/SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>

#include <iostream>

#include "App.hpp"
#include "EventHandler.hpp"
#include "Maze.hpp"
#include "UI.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void kill() {
  // Quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  /***** Initialize my App *****/
  App &app = App::get_instance();
  app.set_window_size(1080, 720);
  app.create_maze(25, 40);
  Maze &maze = app.get_maze();
  maze.set_algorithm("dfs");

  /***** Initialization (window and renderer) ******/
  srand((unsigned int)time(NULL));

  // Setup SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
      0) {
    std::cout << "Error: " << SDL_GetError() << std::endl;
    return -1;
  }

  // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

  // Create window with SDL_Renderer graphics context
  window = SDL_CreateWindow(App::window_title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, app.get_window_width(),
                            app.get_window_height(), App::window_flags);
  if (window == nullptr) {
    printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, App::renderer_flags);
  if (renderer == nullptr) {
    SDL_Log("Error creating SDL_Renderer!");
    return -1;
  }

  // SDL_RendererInfo info;
  // SDL_GetRendererInfo(renderer, &info);
  // SDL_Log("Current SDL_Renderer: %s", info.name);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  bool show_demo_window = true;
  bool show_another_window = false;

  /***** Start the game loop *****/
  EventHandler event_handler;
  SDL_Event event;
  bool quit = false;

  while (!quit) {
    /***** Event handling *****/
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      event_handler.set_event(event);
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEMOTION:
          event_handler.handle_mouse_motition();
          break;
        case SDL_MOUSEBUTTONDOWN:
          event_handler.handle_mouse_down();
          break;
        case SDL_MOUSEBUTTONUP:
          event_handler.handle_mouse_up();
          break;
        case SDL_WINDOWEVENT:
          if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            int w, h;
            SDL_GetRendererOutputSize(renderer, &w, &h);
            app.set_window_size(w, h);
            event_handler.handle_window_resize();
          }
          break;
      }
    }
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
      SDL_Delay(10);
      continue;
    }

    /***** Start the Dear ImGui frame *****/
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    /***** Update the UI *****/
    UI::draw(event_handler);

    /***** Update states *****/
    maze.draw();

    /***** Rendering *****/
    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x,
                       io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderClear(renderer);
    maze.render(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
  }

  /***** Free memory *****/
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
