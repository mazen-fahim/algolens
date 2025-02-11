#include "EventHandler.hpp"

#include "App.hpp"
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

void EventHandler::handle_window_resize(Maze &maze) {
  // make it responsive
  // update the maze x, y, width, height,
  // cells x, y, width, height

  int number_of_cols = maze.get_number_of_cols();
  int number_of_rows = maze.get_number_of_rows();
  // The maze only take 75% of the width and 75% of the height
  int cell_width =
      static_cast<int>(std::round((App::window_width * 0.75) / number_of_cols));
  int cell_height = static_cast<int>(
      std::round((App::window_height * 0.75) / number_of_rows));

  int maze_width = cell_width * number_of_cols;
  int maze_height = cell_height * number_of_rows;
  int maze_x = (App::window_width - maze_width) / 2;
  int maze_y = (App::window_height - maze_height);
  maze.set_width(maze_width);
  maze.set_height(maze_height);
  maze.set_x(maze_x);
  maze.set_y(maze_y);
  maze.set_cell_width(cell_width);
  maze.set_cell_height(cell_height);

  for (int i = 0; i < number_of_rows; i++) {
    for (int j = 0; j < number_of_cols; j++) {
      int x = maze_x + j * cell_width;
      int y = maze_y + i * cell_height;
      maze.m_maze[i][j].set_x(x);
      maze.m_maze[i][j].set_y(y);
      maze.m_maze[i][j].set_width(cell_width);
      maze.m_maze[i][j].set_height(cell_height);
    }
  }
}
