#include "EventHandler.hpp"

#include <iostream>

#include "App.hpp"
#include "Cell.hpp"
#include "Maze.hpp"

EventHandler::EventHandler() {
  m_mouse_button_down = false;
  m_source_pressed_down = false;
  m_target_pressed_down = false;
}

void EventHandler::handle_mouse_down() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
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

void EventHandler::handle_mouse_up() {
  m_mouse_button_down = false;
  m_source_pressed_down = false;
  m_target_pressed_down = false;
}

void EventHandler::handle_mouse_motition() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  MazeState maze_state = maze.get_maze_state();
  int x, y;
  SDL_GetMouseState(&x, &y);
  std::pair<int, int> cell_id = maze.get_cell_id(x, y);
  if (cell_id.first != -1) {
    if (m_mouse_button_down) {
      if (maze.get_cell_state(cell_id) == CellState::NOT_VISITED) {
        // move the source only in the RESET state
        if (m_source_pressed_down && maze_state == MazeState::RESET) {
          maze.set_source_cell(cell_id);
          // move the target only in the RESET state
        } else if (m_target_pressed_down && maze_state == MazeState::RESET) {
          maze.set_target_cell(cell_id);
          // can put walls pretty much in any state.
        } else {
          maze.set_cell_state(cell_id, CellState::WALL);
        }
      }
    }
  }
}

void EventHandler::set_event(SDL_Event event) { m_event = event; }

void EventHandler::handle_window_resize() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();

  int window_width = app.get_window_width();
  int window_height = app.get_window_height();
  int number_of_cols = maze.get_number_of_cols();
  int number_of_rows = maze.get_number_of_rows();

  int cell_width =
      static_cast<int>(std::round(window_width * 0.75) / number_of_cols);
  int cell_height =
      static_cast<int>(std::round(window_height * 0.75) / number_of_rows);

  int maze_width = cell_width * number_of_cols;
  int maze_height = cell_height * number_of_rows;
  int maze_x = (window_width - maze_width) / 2;
  int maze_y = (window_height - maze_height);

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

void EventHandler::handle_start_button_click() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  maze.start();
  std::cout << "Start Button clicked" << std::endl;
}

void EventHandler::handle_pause_button_click() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  maze.pause();
  std::cout << "pause Button clicked" << std::endl;
}

void EventHandler::handle_reset_button_click() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  maze.reset();
  std::cout << "reset Button clicked" << std::endl;
}

void EventHandler::handle_resume_button_click() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  maze.resume();
  std::cout << "resume Button clicked" << std::endl;
}
