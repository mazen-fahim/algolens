
#include <SDL.h>
#include <SDL_events.h>

#include "Maze.hpp"
class EventHandler {
 public:
  EventHandler();
  ~EventHandler() = default;

  void handle_mouse_down(Maze &maze);
  void handle_mouse_up();

  void handle_mouse_motition(Maze &maze);
  void set_event(SDL_Event event);

 private:
  SDL_Event m_event;
  std::pair<int, int> get_cell_id(int mouse_x, int mouse_y, Maze &maze);
  bool m_mouse_button_down;
};
