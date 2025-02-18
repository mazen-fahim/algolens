#include "Maze.hpp"

#include "App.hpp"
#include "defs.hpp"

Maze::Maze()
    : GameObject(0, 0, ALGO_WINDOW_WIDTH, ALGO_WINDOW_HEIGHT, 0, 0, 0, 255,
                 false)

{
  App &app = App::get_instance();

  float window_width = app.get_window_width();
  float window_height = app.get_window_height();
  float maze_x = (window_width - ALGO_WINDOW_WIDTH) / 2;
  float maze_y = (window_height - ALGO_WINDOW_HEIGHT) / 2;
  if (maze_x >= 0)
    set_x(maze_x);
  else
    set_x(0);
  if (maze_y >= 0)
    set_y(maze_y);
  else
    set_y(0);

  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    std::vector<Cell> cells;
    std::vector<std::pair<int, int>> parents;
    for (int j = 0; j < NUMBER_OF_COLS; j++) {
      float x = maze_x + j * CELL_WIDTH;
      float y = maze_y + i * CELL_HEIGHT;
      Cell cell(x, y, CELL_WIDTH, CELL_HEIGHT, 0, 0, 0, 255, false,
                CellState::NOT_VISITED);
      cells.push_back(cell);
      parents.push_back({-1, -1});
    }
    m_parent.emplace_back(std::move(parents));
    m_maze.emplace_back(std::move(cells));
  }

  // Set default position for source/target cells.
  std::pair<int, int> m_source = {0, 0};
  std::pair<int, int> m_target = {0, 0};
  m_source.first = NUMBER_OF_ROWS / 4;
  m_source.second = NUMBER_OF_COLS / 4;
  m_target.first = NUMBER_OF_ROWS * 3 / 4;
  m_target.second = NUMBER_OF_COLS * 3 / 4;
  set_source_cell(m_source);
  set_target_cell(m_target);

  m_path_length = 0;
  m_path_index = 0;
}

void Maze::draw() {
  App &app = App::get_instance();
  AlgoState algo_state = app.get_algo_state();
  std::string current_algorithm = app.get_current_algorithm();
  if (app.should_update()) {
    if (algo_state == AlgoState::ALGORITHM_RUN) {
      if (current_algorithm == "dfs") {
        dfs_ss();
      } else if (current_algorithm == "bfs") {
        bfs_ss();
      }
    }

    else if (algo_state == AlgoState::PATH_RUN) {
      if (m_path_index == m_path_length) {
        app.set_algo_state(AlgoState::FINISH);
      } else {
        std::pair<int, int> cell = m_path[m_path_index++];
        if (cell != m_target) set_cell_state(cell, CellState::SHORTEST_PATH);
      }
    }
  }

  for (auto &row : m_maze)
    for (auto &cell : row) cell.draw();
}

// TODO: make the render method apart of the GameObject so
// that any sort of game object has the ability to render itself
// TODO: Abstract away the renderer used to be able to switch
// between graphics api backends easily. (Seperating the backend
// from my application logic)
void Maze::render(SDL_Renderer *renderer) {
  for (auto &row : m_maze) {
    for (auto &cell : row) {
      cell.render(renderer);
    }
  }
}

void Maze::dfs_ss() {
  App &app = App::get_instance();
  AlgoState algo_state = app.get_algo_state();
  if (m_dfs_stk.empty()) {
    app.set_algo_state(AlgoState::FINISH_TARGET_NOT_FOUND);
    return;
  }

  int dr[] = {1, -1, 0, 0};
  int dc[] = {0, 0, 1, -1};

  std::pair<int, int> current_cell = m_dfs_stk.top();
  m_dfs_stk.pop();

  // You would think a "WALL" would never be pushed on the stack
  // to begin with, but the animation is interactive and the user can put
  // walls while the algorithm is running. so make sure that you don't process
  // "WALL" cells that are added at runtime.
  if (get_cell_state(current_cell) == CellState::WALL) return;

  // was visited before
  if (get_cell_state(current_cell) == CellState::VISITED) return;

  // found target
  if (get_cell_state(current_cell) == CellState::TARGET) {
    construct_shortest_path();
    app.set_algo_state(AlgoState::PATH_RUN);
    return;
  }

  // if the current cell is the source cell then no need to mark
  // it as visited. the source cell is already marked with a "SOURCE" state
  // that signifies that it's visited.
  if (get_cell_state(current_cell) == CellState::NOT_VISITED) {
    set_cell_state(current_cell, CellState::VISITED);
  }

  for (int i = 0; i < 4; i++) {
    int new_r = dr[i] + current_cell.first;
    int new_c = dc[i] + current_cell.second;
    if (is_valid({new_r, new_c}) && is_not_visited({new_r, new_c})) {
      m_parent[new_r][new_c] = current_cell;
      m_dfs_stk.push({new_r, new_c});
    }
  }
}

void Maze::bfs_ss() {
  App &app = App::get_instance();
  AlgoState algo_state = app.get_algo_state();
  if (m_bfs_q.empty()) {
    app.set_algo_state(AlgoState::FINISH_TARGET_NOT_FOUND);
    return;
  }

  int dr[] = {1, -1, 0, 0};
  int dc[] = {0, 0, 1, -1};

  std::pair<int, int> current_cell = m_bfs_q.front();
  m_bfs_q.pop();

  // You would think a "WALL" would never be pushed on the stack
  // to begin with, but the animation is interactive and the user can put
  // walls while the algorithm is running. so make sure that you don't process
  // "WALL" cells that are added at runtime.
  if (get_cell_state(current_cell) == CellState::WALL) return;

  // was visited before
  if (get_cell_state(current_cell) == CellState::VISITED) return;

  // found target
  if (get_cell_state(current_cell) == CellState::TARGET) {
    construct_shortest_path();
    app.set_algo_state(AlgoState::PATH_RUN);
    return;
  }

  // if the current cell is the source cell then no need to mark
  // it as visited. the source cell is already marked with a "SOURCE" state
  // that signifies that it's visited.
  if (get_cell_state(current_cell) == CellState::NOT_VISITED) {
    set_cell_state(current_cell, CellState::VISITED);
  }

  for (int i = 0; i < 4; i++) {
    int new_r = dr[i] + current_cell.first;
    int new_c = dc[i] + current_cell.second;
    if (is_valid({new_r, new_c}) && is_not_visited({new_r, new_c})) {
      m_parent[new_r][new_c] = current_cell;
      m_bfs_q.push({new_r, new_c});
    }
  }
}

bool Maze::is_valid(std::pair<int, int> cell_id) {
  // this cell is out of range
  int r = cell_id.first;
  int c = cell_id.second;
  if (r < 0 || r >= NUMBER_OF_ROWS || c < 0 || c >= NUMBER_OF_COLS)
    return false;
  // this cell is a wall
  if (m_maze[r][c].get_state() == CellState::WALL) return false;
  return true;
}

bool Maze::is_not_visited(std::pair<int, int> cell_id) {
  return (get_cell_state(cell_id) == CellState::NOT_VISITED ||
          get_cell_state(cell_id) == CellState::TARGET);
}

void Maze::set_cell_state(std::pair<int, int> cell_id, CellState state) {
  m_maze[cell_id.first][cell_id.second].set_state(state);
}

CellState Maze::get_cell_state(std::pair<int, int> cell_id) {
  return m_maze[cell_id.first][cell_id.second].get_state();
}

bool Maze::is_inside(float x, float y) {
  return (x >= get_x() && x < get_x() + get_width() && y >= get_y() &&
          y < get_y() + get_height());
}

std::pair<int, int> Maze::get_cell_id(float x, float y) {
  if (!is_inside(x, y))
    return {-1, -1};
  else {
    int cell_r = (y - get_y()) / CELL_HEIGHT;
    int cell_c = (x - get_x()) / CELL_WIDTH;
    return {cell_r, cell_c};
  }
}
void Maze::set_source_cell(std::pair<int, int> source_cell) {
  set_cell_state(m_source, CellState::NOT_VISITED);
  m_source = source_cell;
  set_cell_state(m_source, CellState::SOURCE);
}
std::pair<int, int> Maze::get_source_cell_id() { return m_source; }

void Maze::set_target_cell(std::pair<int, int> target_cell) {
  set_cell_state(m_target, CellState::NOT_VISITED);
  m_target = target_cell;
  set_cell_state(m_target, CellState::TARGET);
}

std::pair<int, int> Maze::get_target_cell_id() { return m_target; }

void Maze::construct_shortest_path() {
  std::pair<int, int> target = m_target;
  while (m_parent[target.first][target.second] != std::make_pair(-1, -1)) {
    m_path.push_back(target);
    target = m_parent[target.first][target.second];
  }
  m_path_length = m_path.size();
}

void Maze::start(std::string algorithm) {
  if (algorithm == "dfs")
    m_dfs_stk.push(m_source);
  else if (algorithm == "bfs")
    m_bfs_q.push(m_source);
}

void Maze::reset() {
  m_path_length = 0;
  m_path_index = 0;
  while (!m_dfs_stk.empty()) m_dfs_stk.pop();
  while (!m_bfs_q.empty()) m_bfs_q.pop();
  m_path.clear();
  for (int i = 0; i < NUMBER_OF_ROWS; i++) {
    for (int j = 0; j < NUMBER_OF_COLS; j++) {
      m_parent[i][j] = std::make_pair(-1, -1);
      m_maze[i][j].set_state(CellState::NOT_VISITED);
    }
  }
  // Recalculate default position of source and target
  std::pair<int, int> m_source = {0, 0};
  std::pair<int, int> m_target = {0, 0};
  m_source.first = NUMBER_OF_ROWS / 4;
  m_source.second = NUMBER_OF_COLS / 4;
  m_target.first = NUMBER_OF_ROWS * 3 / 4;
  m_target.second = NUMBER_OF_COLS * 3 / 4;
  set_source_cell(m_source);
  set_target_cell(m_target);
}

int Maze::get_path_length() { return m_path_length; }
