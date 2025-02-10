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
  Maze(int number_of_rows, int number_of_cols);
  ~Maze() = default;
  void draw();
  void render(SDL_Renderer *renderer);

  // TODO: Error checking
  // reutrns wheter or not the point(x, y) is inside of the maze borders

  // returns the cell id of the point(x, y)
  // the point(x, y) needs to be inside the maze
  // otherwise return {-1, -1}
  std::pair<int, int> get_cell_id(int x, int y);
  std::pair<int, int> get_source_cell_id();
  std::pair<int, int> get_target_cell_id();
  CellState get_cell_state(std::pair<int, int> cell_id);

  // updates both the source/target cell id
  // and updates the states accordingly
  void set_source_cell(std::pair<int, int> source_cell);
  void set_target_cell(std::pair<int, int> source_cell);
  void set_algorithm(const std::string &algo);
  void set_cell_state(std::pair<int, int> cell_id, CellState state);

 private:
  void construct_shortest_path();
  void dfs_ss();
  void bfs_ss();
  void dijkstra_ss();
  bool is_valid(std::pair<int, int> cell_id);
  bool is_inside(int x, int y);
  bool is_not_visited(std::pair<int, int> cell_id);
  bool is_visited(std::pair<int, int> cell_id);
  int m_number_of_rows;
  int m_number_of_cols;
  int m_number_of_cells;

  std::string m_algorithm;
  std::vector<std::vector<Cell>> m_maze;

  std::pair<int, int> m_source;
  std::pair<int, int> m_target;
  std::vector<std::vector<std::pair<int, int>>> m_parent;

  std::stack<std::pair<int, int>> m_dfs_stk;
  std::queue<std::pair<int, int>> m_bfs_q;
  std::queue<std::pair<int, int>> m_dijkstra_q;
  bool m_target_found;
  std::vector<std::pair<int, int>> m_path;
  int m_path_length;
  bool m_path_animation_finished;
  int m_path_index;
};
