#include "Maze.hpp"

#include <utility>

#include "GameObject.hpp"

Maze::Maze(int x, int y, int width, int height)
    : GameObject(x, y, width, height)

{}

void Maze::render(const Renderer &renderer) {
  SDL_SetRenderDrawColor(renderer, rectangle->red, rectangle->green,
                         rectangle->blue, rectangle->alpha);
  SDL_Rect *rect;
  SDL_RenderFillRect(renderer, rect);
}

void Maze::draw() {
  if (m_current_algorithm == "dfs") {
    dfs_ss();
  } else if (m_current_algorithm == "bfs") {
  } else if (m_current_algorithm == "dijkstra") {
  }
}

bool Maze::is_valid(int r, int c) {
  // this cell is out of range
  if (r < 0 || r >= m_number_of_rows || c < 0 || c >= m_number_of_cols)
    return false;
  // this cell is a wall
  if (m_mtrx[r][c] == CellState::WALL) return false;
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
    if (m_mtrx[cnr][cnc] == CellState::VISITED) return;

    if (m_mtrx[cnr][cnc] != CellState::VISITED &&
        m_mtrx[cnr][cnc] != CellState::SOURCE) {
      m_mtrx[cnr][cnc] = CellState::VISITED;
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
          m_mtrx[new_r][new_c] != CellState::VISITED &&
          m_mtrx[new_r][new_c] != CellState::SOURCE) {
        m_dfs_stk.push({new_r, new_c});
      }
    }
  }
}
