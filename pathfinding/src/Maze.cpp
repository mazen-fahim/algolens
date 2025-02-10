#include "Maze.hpp"

#include <vector>

#include "Cell.hpp"
#include "GameObject.hpp"
#include "defs.hpp"

Maze::Maze(int number_of_rows, int number_of_cols)
    : GameObject(0, 0, 0, 0, 0, 0, 0, 255, false),
      m_number_of_rows{number_of_rows},
      m_number_of_cols{number_of_cols} {
  int maze_width = CELL_SIZE * m_number_of_cols;
  int maze_height = CELL_SIZE * m_number_of_rows;
  int maze_x = (WINDOW_WIDTH - maze_width) / 2;
  int maze_y = (WINDOW_HEIGHT - maze_height);
  set_width(maze_width);
  set_height(maze_height);
  set_x(maze_x);
  set_y(maze_y);

  m_number_of_cells = m_number_of_cols * m_number_of_rows;
  for (int i = 0; i < m_number_of_rows; i++) {
    std::vector<Cell> cells;
    for (int j = 0; j < m_number_of_cols; j++) {
      int x = maze_x + j * CELL_SIZE;
      int y = maze_y + i * CELL_SIZE;
      Cell cell(x, y, CELL_SIZE, CELL_SIZE, 0, 0, 0, 255, false,
                CellState::NOT_VISITED);
      cells.push_back(cell);
    }
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
}

void Maze::draw() {
  // if (!m_target_found) {
  //   if (m_algorithm == "dfs") {
  //     dfs_ss();
  //   }
  //   // else if (m_algorithm == "bfs") {
  //   //   bfs_ss();
  //   // } else if (m_algorithm == "dijkstra") {
  //   //   dijkstra_ss();
  //   // }
  // }

  // update all of the cells states
  for (auto &row : m_maze) {
    for (auto &cell : row) {
      cell.draw();
    }
  }
}

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

bool Maze::is_valid(int r, int c) {
  // this cell is out of range
  if (r < 0 || r >= m_number_of_rows || c < 0 || c >= m_number_of_cols)
    return false;
  // this cell is a wall
  if (m_maze[r][c].get_state() == CellState::WALL) return false;
  return true;
}

void Maze::dfs_ss() {
  if (!m_dfs_stk.empty()) {
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    auto [cnr, cnc] = m_dfs_stk.top();
    m_dfs_stk.pop();

    if (m_maze[cnr][cnc].get_state() == CellState::VISITED) return;

    if (m_maze[cnr][cnc].get_state() == CellState::TARGET) {
      m_target_found = true;
      return;
    }

    if (m_maze[cnr][cnc].get_state() == CellState::NOT_VISITED) {
      m_maze[cnr][cnc].set_state(CellState::VISITED);
    }

    for (int i = 0; i < 4; i++) {
      int new_r = dr[i] + cnr;
      int new_c = dc[i] + cnc;
      if (is_valid(new_r, new_c) &&
          // note if the state is SOURCE then it's of course visited
          (m_maze[new_r][new_c].get_state() == CellState::NOT_VISITED ||
           m_maze[new_r][new_c].get_state() == CellState::TARGET)) {
        m_dfs_stk.push({new_r, new_c});
      }
    }
  }
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
    int cell_r = (y - get_y()) / CELL_SIZE;
    int cell_c = (x - get_x()) / CELL_SIZE;
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
