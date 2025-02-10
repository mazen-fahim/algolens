#include "EventHandler.hpp"

#include "Cell.hpp"

EventHandler::EventHandler() {
  m_mouse_button_down = false;
  m_source_pressed_down = false;
  m_target_pressed_down = false;
}

void EventHandler::handle_mouse_down(Maze &maze) {
  m_mouse_button_down = true;
  int x, y;
  SDL_GetMouseState(&x, &y);
  std::pair<int, int> cell_id = maze.get_cell_id(x, y);
  if (cell_id.first != -1) {
    if (maze.get_cell_state(cell_id) == CellState::NOT_VISITED) {
      maze.set_cell_state(cell_id, CellState::WALL);
    } else if (maze.get_cell_state(cell_id) == CellState::SOURCE) {
      m_source_pressed_down = true;
    } else if (maze.get_cell_state(cell_id) == CellState::TARGET) {
      m_target_pressed_down = true;
    }
  }
}

void EventHandler::handle_mouse_up(Maze &maze) {
  m_mouse_button_down = false;
  m_source_pressed_down = false;
  m_target_pressed_down = false;
}

void EventHandler::handle_mouse_motition(Maze &maze) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  std::pair<int, int> cell_id = maze.get_cell_id(x, y);
  if (cell_id.first != -1) {
    if (m_mouse_button_down) {
      if (maze.get_cell_state(cell_id) == CellState::NOT_VISITED) {
        if (m_source_pressed_down) {  // moving the source
          maze.set_source_cell(cell_id);
        } else if (m_target_pressed_down) {  // moving the target
          maze.set_target_cell(cell_id);
        } else {  // putting a wall
          maze.set_cell_state(cell_id, CellState::WALL);
        }
      }
    }
  }
}

void EventHandler::set_event(SDL_Event event) { m_event = event; }
