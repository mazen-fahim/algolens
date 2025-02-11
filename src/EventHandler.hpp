#pragma once
#include <SDL.h>
#include <SDL_events.h>

class EventHandler {
 public:
  EventHandler();
  ~EventHandler() = default;

  void handle_mouse_down();
  void handle_mouse_up();
  void handle_mouse_motition();

  void handle_window_resize();
  void handle_start_button_click();
  void handle_pause_button_click();
  void handle_resume_button_click();
  void handle_reset_button_click();

  void set_event(SDL_Event event);

 private:
  bool m_target_pressed_down;
  bool m_source_pressed_down;
  SDL_Event m_event;
  bool m_mouse_button_down;
};
