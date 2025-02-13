#pragma once

#include <SDL.h>
#include <SDL_events.h>

#include <string>

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

  void handle_algorithm_change(std::string algorithm);
  void handle_speed_change(int speed);

 private:
  void handle_target_source_hover();
  void handle_not_visited_hover(std::pair<int, int> cell_id);
  void handle_visited_hover();
  void handle_wall_hover();
  void handle_shortest_path_hover();

  bool m_target_pressed_down;
  bool m_source_pressed_down;
  SDL_Event m_event;
  bool m_mouse_button_down;
};
