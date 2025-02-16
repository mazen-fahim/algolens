#pragma once

#include <SDL3/SDL.h>

#include <string>
#include <vector>

#include "Bar.hpp"
#include "GameObject.hpp"

class Sort : public GameObject {
 public:
  Sort();
  ~Sort() = default;
  void draw();
  void render(SDL_Renderer* renderer);

  void start(std::string algorithm);
  void pause();
  void resume();
  void reset();

  int get_number_of_comparisons();

  BarState get_bar_state(int bar_id);
  void set_bar_state(int bar_id, BarState state);

  // Make it public because the resizing event wants
  // to access the individual bars to update them
  std::vector<Bar> m_bars;
  void swap_bars(Bar& bar1, Bar& bar2);

 private:
  int m_number_of_comparisons;
  void randomize();
  void selection_sort_ss();
  int m_i;
  int m_j;
  int m_min_idx;
  int m_i_prv;
  int m_j_prv;
  int m_min_idx_prv;
};
