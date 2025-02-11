
#include <SDL.h>
#include <SDL_events.h>

#include "Maze.hpp"
class EventHandler {
 public:
  EventHandler();
  ~EventHandler() = default;

  void handle_mouse_down(Maze &maze);
  void handle_mouse_up(Maze &maze);
  void handle_mouse_motition(Maze &maze);

  void handle_window_resize(Maze &maze);

  void set_event(SDL_Event event);

 private:
  bool m_target_pressed_down;
  bool m_source_pressed_down;
  SDL_Event m_event;
  bool m_mouse_button_down;
};
