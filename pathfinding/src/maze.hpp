#ifndef MAZEN_H
#define MAZEN_H

#include <SDL.h>
#include <SDL_rect.h>

#include <stack>
#include <string>
#include <vector>

#include "cell.hpp"

enum class CellState {
  VISITED,
  NOT_VISITED,
  SOURCE,
  TARGET,
  WALL,
};

class Maze {
 public:
  Maze(int width, int height, int posx, int posy);
  bool update();

 private:
  // it returns whether or not it actually made and changes to the state of the
  // maze
  bool dfs_ss();
  // check the validity of this cell
  // cell is not valid if
  // it's a wall
  // it's out of range
  bool is_valid(int x, int y);
  int m_maze_x_pos;
  int m_maze_y_pos;

  int m_maze_width;
  int m_maze_height;

  const int m_number_of_rows = 25;
  const int m_number_of_cols = 40;
  const int m_number_of_cells = m_number_of_rows * m_number_of_cols;

  int m_cell_width;
  int m_cell_height;

  std::string m_current_algorithm;
  std::vector<std::vector<CellState>> m_mtrx;
  std::vector<std::vector<SDL_Rect>> m_cells;

  std::pair<int, int> m_source;
  std::pair<int, int> m_target;

  std::stack<std::pair<int, int>> m_dfs_stk;

  SDL_Rect m_maze_border;
};

#endif
