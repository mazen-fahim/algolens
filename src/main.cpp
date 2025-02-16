#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <iostream>

#include "App.hpp"
#include "EventHandler.hpp"
#include "SDL3/SDL_timer.h"
#include "UI.hpp"
#include "defs.hpp"
using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int main(int argc, char *argv[]) {
  /***** Initialize my App *****/
  App &app = App::get_instance();
  app.create_maze();
  app.create_sort();
  Maze &maze = app.get_maze();
  app.set_algorithm("dfs");

  /***** Initialization (window and renderer) ******/
  srand((unsigned int)time(NULL));

  // Setup SDL
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

  if (!SDL_CreateWindowAndRenderer(App::window_title, app.get_window_width(),
                                   app.get_window_height(), App::window_flags,
                                   &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(window);

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
  ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);

  /***** Start the game loop *****/
  EventHandler event_handler;
  SDL_Event event;
  bool quit = false;

  Uint64 pt = SDL_GetTicks();

  while (!quit) {
    /***** Event handling *****/
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      event_handler.set_event(event);
      switch (event.type) {
        case SDL_EVENT_QUIT:
          quit = true;
          break;
        case SDL_EVENT_MOUSE_MOTION:
          if (!io.WantCaptureMouse) event_handler.handle_mouse_motition();
          break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
          if (!io.WantCaptureMouse) event_handler.handle_mouse_down();
          break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
          if (!io.WantCaptureMouse) event_handler.handle_mouse_up();
          break;
        case SDL_EVENT_WINDOW_RESIZED:
          int w, h;
          SDL_GetCurrentRenderOutputSize(renderer, &w, &h);
          app.set_window_size(w, h);
          event_handler.handle_window_resize();
          SDL_SetRenderViewport(renderer, NULL);
          break;
      }
    }

    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
      SDL_Delay(10);
      continue;
    }

    /***** Start the Dear ImGui frame *****/
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    /***** Update the UI *****/
    UI::draw(event_handler);

    /***** Update states *****/

    app.draw();

    /***** Rendering *****/
    ImGui::Render();
    SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x,
                       io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderClear(renderer);

    app.render(renderer);

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(app.get_delay_time());
  }

  /***** Free memory *****/
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
