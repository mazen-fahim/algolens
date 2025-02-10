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

  int default_src_col = m_number_of_cols / 4;
  int default_src_row = m_number_of_rows / 4;
  int default_target_col = m_number_of_cols * 3 / 4;
  int default_target_row = m_number_of_rows * 3 / 4;
  m_maze[default_src_row][default_src_col].set_state(CellState::SOURCE);
  m_maze[default_target_row][default_target_col].set_state(CellState::TARGET);

  m_dfs_stk.push({default_src_row, default_src_col});
}

void Maze::draw() {
  if (m_algorithm == "dfs") {
    dfs_ss();
  }
  // else if (m_algorithm == "bfs") {
  //   bfs_ss();
  // } else if (m_algorithm == "dijkstra") {
  //   dijkstra_ss();
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

// it returns whether or not it actually made any changes to the state of the
// maze
void Maze::dfs_ss() {
  int dr[] = {1, -1, 0, 0};
  int dc[] = {0, 0, 1, -1};

  if (!m_dfs_stk.empty()) {
    auto cn = m_dfs_stk.top();
    m_dfs_stk.pop();
    int cnr = cn.first;
    int cnc = cn.second;

    // Note if two parents share the same child the child will be pushed twice.
    // so if the child is already visited no need to do anything.
    if (m_maze[cnr][cnc].get_state() == CellState::VISITED) return;

    if (m_maze[cnr][cnc].get_state() != CellState::VISITED &&
        m_maze[cnr][cnc].get_state() != CellState::SOURCE) {
      m_maze[cnr][cnc].set_state(CellState::VISITED);
    }

    // so you would think this should be also single stepped through but in fact
    // pushing the 4 children of a particular cell is not actually transitioning
    // to these children I'm just preparing the stack for the next step in the
    // dfs algorithm
    for (int i = 0; i < 4; i++) {
      int new_r = dr[i] + cnr;
      int new_c = dr[i] + cnr;
      if (is_valid(new_r, new_c) &&
          // note if the state is SOURCE then it's of course visited
          m_maze[new_r][new_c].get_state() != CellState::VISITED &&
          m_maze[new_r][new_c].get_state() != CellState::SOURCE) {
        m_dfs_stk.push({new_r, new_c});
      }
    }
  }
}

void Maze::set_algorithm(const std::string &algo) { m_algorithm = algo; }

void Maze::set_cell_state(int row, int col, CellState state) {
  m_maze[row][col].set_state(state);
}

CellState Maze::get_cell_state(int row, int col) {
  return m_maze[row][col].get_state();
}
