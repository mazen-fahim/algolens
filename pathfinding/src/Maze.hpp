#pragma once

#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>

#include <stack>
#include <string>
#include <vector>

#include "Cell.hpp"
#include "GameObject.hpp"

class Maze : public GameObject {
 public:
  Maze(int number_of_rows, int number_of_cols);
  ~Maze() = default;
  void draw();
  void render(SDL_Renderer *renderer);

  // TODO: Error checking
  void set_algorithm(const std::string &algo);
  void set_cell_state(int row, int col, CellState state);
  CellState get_cell_state(int row, int col);

 private:
  void dfs_ss();
  void bfs_ss();
  void dijkstra_ss();
  // check the validity of this cell
  // cell is not valid if
  // it's a wall
  // it's out of range
  bool is_valid(int x, int y);
  int m_number_of_rows;
  int m_number_of_cols;
  int m_number_of_cells;

  std::string m_algorithm;
  std::vector<std::vector<Cell>> m_maze;

  std::pair<int, int> m_source;
  std::pair<int, int> m_target;

  std::stack<std::pair<int, int>> m_dfs_stk;
};
