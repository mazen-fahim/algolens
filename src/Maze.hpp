#pragma once

#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "Cell.hpp"
#include "GameObject.hpp"

class Maze : public GameObject {
 public:
  Maze();
  ~Maze() = default;
  void draw();
  void render(SDL_Renderer *renderer);
  void start(std::string algorithm);
  void pause();
  void resume();
  void reset();

  // TODO: Error checking
  // reutrns wheter or not the point(x, y) is inside of the maze borders

  // returns the cell id of the point(x, y)
  // the point(x, y) needs to be inside the maze
  // otherwise return {-1, -1}
  std::pair<int, int> get_cell_id(int x, int y);
  std::pair<int, int> get_source_cell_id();
  std::pair<int, int> get_target_cell_id();
  CellState get_cell_state(std::pair<int, int> cell_id);
  int get_path_length();

  // updates both the source/target cell id
  // and updates the states accordingly
  void set_source_cell(std::pair<int, int> source_cell);
  void set_target_cell(std::pair<int, int> source_cell);
  void set_cell_state(std::pair<int, int> cell_id, CellState state);

  // Make it public because the resizing event wants
  // to access the individual cells to update them
  std::vector<std::vector<Cell>> m_maze;

 private:
  std::vector<std::vector<std::pair<int, int>>> m_parent;
  std::vector<std::pair<int, int>> m_path;
  std::pair<int, int> m_source;
  std::pair<int, int> m_target;
  int m_path_length;
  int m_path_index;

  std::stack<std::pair<int, int>> m_dfs_stk;
  std::queue<std::pair<int, int>> m_bfs_q;
  std::queue<std::pair<int, int>> m_dijkstra_q;

  void dijkstra_ss();
  bool is_valid(std::pair<int, int> cell_id);
  bool is_inside(int x, int y);
  bool is_not_visited(std::pair<int, int> cell_id);
  bool is_visited(std::pair<int, int> cell_id);
  void construct_shortest_path();
  void dfs_ss();
  void bfs_ss();
};
