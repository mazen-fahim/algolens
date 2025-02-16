#include "EventHandler.hpp"

#include "App.hpp"
#include "Maze.hpp"
#include "defs.hpp"

EventHandler::EventHandler() {
  m_mouse_button_down = false;
  m_source_pressed_down = false;
  m_target_pressed_down = false;
}

void EventHandler::handle_mouse_down() {
  App &app = App::get_instance();
  if (app.is_sorting_algorithm(app.get_current_algorithm())) return;

  Maze &maze = app.get_maze();
  m_mouse_button_down = true;
  float x, y;
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
  App &app = App::get_instance();
  if (app.is_sorting_algorithm(app.get_current_algorithm())) return;

  m_mouse_button_down = false;
  m_source_pressed_down = false;
  m_target_pressed_down = false;
}

void EventHandler::handle_mouse_motition() {
  App &app = App::get_instance();
  if (app.is_sorting_algorithm(app.get_current_algorithm())) return;

  Maze &maze = app.get_maze();
  float x, y;
  SDL_GetMouseState(&x, &y);
  std::pair<int, int> cell_id = maze.get_cell_id(x, y);
  if (cell_id.first != -1) {
    CellState cell_state = maze.get_cell_state(cell_id);
    if (cell_state == CellState::SOURCE || cell_state == CellState::TARGET) {
      handle_target_source_hover();
    } else if (cell_state == CellState::NOT_VISITED) {
      handle_not_visited_hover(cell_id);
    } else if (cell_state == CellState::VISITED) {
      handle_visited_hover();
    } else if (cell_state == CellState::WALL) {
      handle_wall_hover();
    } else if (cell_state == CellState::SHORTEST_PATH) {
      handle_shortest_path_hover();
    }
  }
}

void EventHandler::handle_target_source_hover() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();

  AlgoState algo_state = app.get_algo_state();
  if (algo_state == AlgoState::RESET)
    app.set_cursor_state(CursorState::HAND);
  else
    app.set_cursor_state(CursorState::NOT_ALLOWED);
}

void EventHandler::handle_not_visited_hover(std::pair<int, int> cell_id) {
  App &app = App::get_instance();

  Maze &maze = app.get_maze();
  AlgoState maze_state = app.get_algo_state();

  // Update cursor state
  // I don't care what state the maze is in as the user
  // can put walls whever he wants so there is always
  // something to do if hovering over a not_visited cell
  app.set_cursor_state(CursorState::HAND);

  if (m_mouse_button_down) {
    if (m_source_pressed_down && maze_state == AlgoState::RESET) {
      // move the source only in the RESET state
      maze.set_source_cell(cell_id);
      // move the target only in the RESET state
    } else if (m_target_pressed_down && maze_state == AlgoState::RESET) {
      maze.set_target_cell(cell_id);
      // can put walls pretty much in any state.
    } else {
      maze.set_cell_state(cell_id, CellState::WALL);
    }
  }
}

void EventHandler::handle_visited_hover() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  app.set_cursor_state(CursorState::ARROW);
}

void EventHandler::handle_wall_hover() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  app.set_cursor_state(CursorState::ARROW);
}

void EventHandler::handle_shortest_path_hover() {
  App &app = App::get_instance();
  Maze &maze = app.get_maze();
  app.set_cursor_state(CursorState::ARROW);
}

void EventHandler::set_event(SDL_Event event) { m_event = event; }

// TODO: put this in in App?
void EventHandler::handle_window_resize() {
  App &app = App::get_instance();
  float window_width = app.get_window_width();
  float window_height = app.get_window_height();
  float algo_x = (window_width - ALGO_WINDOW_WIDTH) / 2;
  float algo_y = (window_height - ALGO_WINDOW_HEIGHT) / 2;

  std::string current_algorithm = app.get_current_algorithm();
  if (app.is_pathfinding_algorithm(current_algorithm)) {
    Maze &maze = app.get_maze();

    if (algo_x >= 0) {
      maze.set_x(algo_x);
    } else {
      maze.set_x(0);
    }

    if (algo_y >= 0) {
      maze.set_y(algo_y);
    } else {
      maze.set_y(0);
    }

    for (int i = 0; i < NUMBER_OF_ROWS; i++) {
      for (int j = 0; j < NUMBER_OF_COLS; j++) {
        float x = algo_x + j * CELL_WIDTH;
        float y = algo_y + i * CELL_HEIGHT;
        maze.m_maze[i][j].set_x(x);
        maze.m_maze[i][j].set_y(y);
      }
    }

  } else {
    Sort &sort = app.get_sort();
    if (algo_x >= 0) {
      sort.set_x(algo_x);
    } else {
      sort.set_x(0);
    }

    if (algo_y >= 0) {
      sort.set_y(algo_y);
    } else {
      sort.set_y(0);
    }

    for (int i = 0; i < NUMBER_OF_BARS; i++) {
      float height = sort.m_bars[i].get_height();
      float x = algo_x + i * BAR_WIDTH;
      float y = algo_y + ALGO_WINDOW_HEIGHT - height;
      sort.m_bars[i].set_x(x);
      sort.m_bars[i].set_y(y);
    }
  }
}

void EventHandler::handle_start_button_click() {
  App &app = App::get_instance();
  app.start();
}

void EventHandler::handle_pause_button_click() {
  App &app = App::get_instance();
  app.pause();
}

void EventHandler::handle_reset_button_click() {
  App &app = App::get_instance();
  app.reset();
}

void EventHandler::handle_resume_button_click() {
  App &app = App::get_instance();
  app.resume();
}

// TODO:
void EventHandler::handle_algorithm_change(std::string algorithm) {
  App &app = App::get_instance();
  app.reset();
  app.set_algorithm(algorithm);
}

void EventHandler::handle_speed_change(int speed) {
  App &app = App::get_instance();
  app.set_animation_speed(speed);
}
