#ifndef MAZEN_H
#define MAZEN_H

#include <SDL.h>
#include <SDL_rect.h>

#include <stack>
#include <string>
#include <vector>

#include "GameObject.hpp"
#include "cell.hpp"
#include "renderer.hpp"

enum class CellState {
  VISITED,
  NOT_VISITED,
  SOURCE,
  TARGET,
  WALL,
};

class Maze : public GameObject {
 public:
  Maze(int x, int y, int width, int height);
  ~Maze();
  void draw();
  void render(const Renderer &renderer);

 private:
  // it returns whether or not it actually made and changes to the state of the
  // maze
  bool dfs_ss();
  // check the validity of this cell
  // cell is not valid if
  // it's a wall
  // it's out of range
  bool is_valid(int x, int y);

  const int m_number_of_rows = 25;
  const int m_number_of_cols = 40;
  const int m_number_of_cells = m_number_of_rows * m_number_of_cols;

  std::string m_current_algorithm;
  std::vector<std::vector<Cell>> m_maze;

  std::pair<int, int> m_source;
  std::pair<int, int> m_target;

  std::stack<std::pair<int, int>> m_dfs_stk;
};

#endif
