#include "Maze.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "App.hpp"
#include "Cell.hpp"
#include "GameObject.hpp"

Maze::Maze(int number_of_rows, int number_of_cols)
    : GameObject(0, 0, 0, 0, 0, 0, 0, 255, false),
      m_number_of_rows{number_of_rows},
      m_number_of_cols{number_of_cols} {
  m_cell_width = (App::window_width * 3 / 4) / number_of_cols;
  m_cell_height = (App::window_height * 3 / 4) / number_of_rows;

  int maze_width = m_cell_width * m_number_of_cols;
  int maze_height = m_cell_height * m_number_of_rows;
  int maze_x = (App::window_width - maze_width) / 2;
  int maze_y = (App::window_height - maze_height);
  set_width(maze_width);
  set_height(maze_height);
  set_x(maze_x);
  set_y(maze_y);

  m_number_of_cells = m_number_of_cols * m_number_of_rows;
  for (int i = 0; i < m_number_of_rows; i++) {
    std::vector<Cell> cells;
    std::vector<std::pair<int, int>> parents;
    for (int j = 0; j < m_number_of_cols; j++) {
      int x = maze_x + j * m_cell_width;
      int y = maze_y + i * m_cell_height;
      Cell cell(x, y, m_cell_width, m_cell_height, 0, 0, 0, 255, false,
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
  m_source.first = m_number_of_rows / 4;
  m_source.second = m_number_of_cols / 4;
  m_target.first = m_number_of_rows * 3 / 4;
  m_target.second = m_number_of_cols * 3 / 4;
  set_source_cell(m_source);
  set_target_cell(m_target);

  m_dfs_stk.push(m_source);
  m_target_found = false;
  m_path_length = 0;
  m_path_index = 0;
  m_path_animation_finished = false;
}

void Maze::draw() {
  if (!m_target_found) {
    if (m_algorithm == "dfs") {
      dfs_ss();
    }
    // else if (m_algorithm == "bfs") {
    //   bfs_ss();
    // } else if (m_algorithm == "dijkstra") {
    //   dijkstra_ss();
    // }
  }

  if (m_target_found && !m_path_animation_finished) {
    if (m_path_index == m_path_length) {
      m_path_animation_finished = true;
    } else {
      std::pair<int, int> cell = m_path[m_path_index++];
      if (cell != m_target) set_cell_state(cell, CellState::SHORTEST_PATH);
    }
  }

  for (auto &row : m_maze) {
    for (auto &cell : row) {
      cell.draw();
    }
  }
}

// TODO: make the render method apart of the GameObject so
// that any sort of game object has the ability to render itself
// TODO: Abstract away the renderer used to be able to switch
// between graphics api backends easily. (Seperating the backend
// from my application logic)
void Maze::render(SDL_Renderer *renderer) {
  // render the maze
  SDL_SetRenderDrawColor(renderer, get_red(), get_green(), get_blue(),
                         get_alpha());
  SDL_Rect rect = {get_x(), get_y(), get_width(), get_height()};
  if (get_fill())
    SDL_RenderFillRect(renderer, &rect);
  else
    SDL_RenderDrawRect(renderer, &rect);

  // render all the cells inside the maze
  for (auto &row : m_maze) {
    for (auto &cell : row) {
      cell.render(renderer);
    }
  }
}

void Maze::dfs_ss() {
  if (m_dfs_stk.empty()) return;

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
    m_target_found = true;
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

bool Maze::is_valid(std::pair<int, int> cell_id) {
  // this cell is out of range
  int r = cell_id.first;
  int c = cell_id.second;
  if (r < 0 || r >= m_number_of_rows || c < 0 || c >= m_number_of_cols)
    return false;
  // this cell is a wall
  if (m_maze[r][c].get_state() == CellState::WALL) return false;
  return true;
}

bool Maze::is_not_visited(std::pair<int, int> cell_id) {
  return (get_cell_state(cell_id) == CellState::NOT_VISITED ||
          get_cell_state(cell_id) == CellState::TARGET);
}

void Maze::set_algorithm(const std::string &algo) { m_algorithm = algo; }

void Maze::set_cell_state(std::pair<int, int> cell_id, CellState state) {
  m_maze[cell_id.first][cell_id.second].set_state(state);
}

CellState Maze::get_cell_state(std::pair<int, int> cell_id) {
  return m_maze[cell_id.first][cell_id.second].get_state();
}

bool Maze::is_inside(int x, int y) {
  return (x >= get_x() && x < get_x() + get_width() && y >= get_y() &&
          y < get_y() + get_height());
}

std::pair<int, int> Maze::get_cell_id(int x, int y) {
  if (!is_inside(x, y))
    return {-1, -1};
  else {
    int cell_r = (y - get_y()) / m_cell_height;
    int cell_c = (x - get_x()) / m_cell_width;
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

int Maze::get_number_of_rows() { return m_number_of_rows; }
int Maze::get_number_of_cols() { return m_number_of_cols; }

int Maze::get_cell_width() { return m_cell_width; }
int Maze::get_cell_height() { return m_cell_height; }

void Maze::set_cell_width(int width) { m_cell_width = width; }
void Maze::set_cell_height(int height) { m_cell_height = height; }
