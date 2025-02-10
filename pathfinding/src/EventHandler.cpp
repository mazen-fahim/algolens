#include "EventHandler.hpp"

#include <iostream>

#include "Cell.hpp"
#include "defs.hpp"
EventHandler::EventHandler() { m_mouse_button_down = false; }
void EventHandler::handle_mouse_down(Maze &maze) {
  m_mouse_button_down = true;
  handle_mouse_motition(maze);
}
void EventHandler::handle_mouse_up() { m_mouse_button_down = false; }

void EventHandler::handle_mouse_motition(Maze &maze) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  if (x >= maze.get_x() && x < maze.get_x() + maze.get_width() &&
      y >= maze.get_y() && y < maze.get_y() + maze.get_height()) {
    if (m_mouse_button_down) {
      std::pair<int, int> cell_id = get_cell_id(x, y, maze);
      if (maze.get_cell_state(cell_id.first, cell_id.second) ==
          CellState::NOT_VISITED) {
        maze.set_cell_state(cell_id.first, cell_id.second, CellState::WALL);
      }
    }
  }
}

// return the id of the cell {row, col}
// this function is called only when the mouse is inside the maze
std::pair<int, int> EventHandler::get_cell_id(int mouse_x, int mouse_y,
                                              Maze &maze) {
  int cell_c = (mouse_x - maze.get_x()) / CELL_SIZE;
  int cell_r = (mouse_y - maze.get_y()) / CELL_SIZE;
  return {cell_r, cell_c};
}
void EventHandler::set_event(SDL_Event event) { m_event = event; }
