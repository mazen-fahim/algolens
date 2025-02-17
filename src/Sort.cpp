#include "Sort.hpp"

#include "App.hpp"
#include "Bar.hpp"
#include "defs.hpp"

Sort::Sort()
    : GameObject(0, 0, ALGO_WINDOW_WIDTH, ALGO_WINDOW_HEIGHT, 0, 0, 0, 255,
                 false),
      m_i{0},
      m_j{0},
      m_min_idx{0},
      m_number_of_comparisons{0},
      m_i_prv{0},
      m_j_prv{0},
      m_min_idx_prv{0} {
  App &app = App::get_instance();

  float window_width = app.get_window_width();
  float window_height = app.get_window_height();
  float sort_x = (window_width - ALGO_WINDOW_WIDTH) / 2;
  float sort_y = (window_height - ALGO_WINDOW_HEIGHT) / 2;
  if (sort_x >= 0)
    set_x(sort_x);
  else
    set_x(0);
  if (sort_y >= 0)
    set_y(sort_y);
  else
    set_y(0);

  for (int i = 0; i < NUMBER_OF_BARS; i++) {
    float height = rand() % (VALUE_RANGE + 1);
    float x = get_x() + i * BAR_WIDTH;
    float y = get_y() + ALGO_WINDOW_HEIGHT - height;
    Bar bar(x, y, BAR_WIDTH, height, 0, 0, 0, 255, true, BarState::NOT_SORTED);
    m_bars.push_back(bar);
  }
}

void Sort::draw() {
  App &app = App::get_instance();
  AlgoState algo_state = app.get_algo_state();
  std::string current_algorithm = app.get_current_algorithm();
  if (app.should_update()) {
    if (algo_state == AlgoState::ALGORITHM_RUN) {
      if (current_algorithm == "selection_sort") {
        selection_sort_ss();
      } else if (current_algorithm == "bubble_sort") {
        bubble_sort_ss();
      } else if (current_algorithm == "insertion_sort") {
        insertion_sort_ss();
      }
    }
  }

  for (auto &bar : m_bars) {
    bar.draw();
  }
}

void Sort::insertion_sort_ss() {
  App &app = App::get_instance();

  // Unmark previously compared elements before the next iteration
  // Note: unmark only if it wasn't marked as
  // sorted in the last iteration
  m_bars[m_j_prv].set_state(BarState::SORTED);
  m_bars[m_j_prv + 1].set_state(BarState::SORTED);

  m_bars[m_j].set_state(BarState::BEING_COMPARED);
  m_bars[m_j + 1].set_state(BarState::BEING_COMPARED);
  m_number_of_comparisons++;
  if (m_j >= 0 && m_bars[m_j].get_height() > m_bars[m_j + 1].get_height()) {
    swap_bars(m_bars[m_j], m_bars[m_j + 1]);

    m_j_prv = m_j;
    m_j--;

  } else {
    m_i_prv = m_i;
    m_i++;

    if (m_i < NUMBER_OF_BARS) {
      m_j_prv = m_j;
      m_j = m_i - 1;

    } else {
      // set the last bar as sorted before finishing
      app.set_algo_state(AlgoState::FINISH);
      m_bars[m_j].set_state(BarState::SORTED);
      m_bars[m_j + 1].set_state(BarState::SORTED);
      m_bars[0].set_state(BarState::SORTED);
    }
  }
}

void Sort::bubble_sort_ss() {
  App &app = App::get_instance();

  // Unmark previously compared elements before the next iteration
  // Note: unmark only if it wasn't marked as
  // sorted in the last iteration
  if (m_j_prv < NUMBER_OF_BARS &&
      m_bars[m_j_prv].get_state() != BarState::SORTED)
    m_bars[m_j_prv].set_state(BarState::NOT_SORTED);

  if (m_j_prv + 1 < NUMBER_OF_BARS &&
      m_bars[m_j_prv + 1].get_state() != BarState::SORTED)
    m_bars[m_j_prv + 1].set_state(BarState::NOT_SORTED);

  if (m_j < NUMBER_OF_BARS - m_i - 1) {
    m_bars[m_j].set_state(BarState::BEING_COMPARED);
    m_bars[m_j + 1].set_state(BarState::BEING_COMPARED);
    m_number_of_comparisons++;

    if (m_bars[m_j].get_height() > m_bars[m_j + 1].get_height()) {
      swap_bars(m_bars[m_j], m_bars[m_j + 1]);
    }

    m_j_prv = m_j;
    m_j++;

  } else {
    m_bars[m_j].set_state(BarState::SORTED);

    m_i_prv = m_i;
    m_i++;

    if (m_i < NUMBER_OF_BARS - 1) {
      m_j_prv = m_j;
      m_j = 0;

    } else {
      // set the last bar as sorted before finishing
      m_bars[0].set_state(BarState::SORTED);
      app.set_algo_state(AlgoState::FINISH);
    }
  }
}

void Sort::selection_sort_ss() {
  App &app = App::get_instance();
  // Unmark previously compared elements before the next iteration
  // Note: unmark only if it wasn't marked as
  // sorted in the last iteration
  if (m_j > 0) {
    if (m_bars[m_j_prv].get_state() != BarState::SORTED)
      m_bars[m_j_prv].set_state(BarState::NOT_SORTED);
  }
  if (m_bars[m_min_idx_prv].get_state() != BarState::SORTED)
    m_bars[m_min_idx_prv].set_state(BarState::NOT_SORTED);

  if (m_j < NUMBER_OF_BARS) {
    m_bars[m_j].set_state(BarState::BEING_COMPARED);
    m_bars[m_min_idx].set_state(BarState::BEING_COMPARED);
    m_number_of_comparisons++;

    if (m_bars[m_j].get_height() < m_bars[m_min_idx].get_height()) {
      m_min_idx_prv = m_min_idx;
      m_min_idx = m_j;
    }

    m_j_prv = m_j;
    m_j++;

  } else {
    if (m_i != m_min_idx) {
      swap_bars(m_bars[m_i], m_bars[m_min_idx]);
    }

    m_bars[m_i].set_state(BarState::SORTED);

    m_i_prv = m_i;
    m_i++;

    if (m_i < NUMBER_OF_BARS - 1) {
      m_min_idx_prv = m_min_idx;
      m_min_idx = m_i;

      m_j_prv = m_j;
      m_j = m_i + 1;

    } else {
      // set the last bar as sorted before finishing
      m_bars[m_i].set_state(BarState::SORTED);
      app.set_algo_state(AlgoState::FINISH);
    }
  }
}

void Sort::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, get_red(), get_green(), get_blue(),
                         get_alpha());
  SDL_FRect rect = {get_x(), get_y(), get_width(), get_height()};
  if (get_fill())
    SDL_RenderFillRect(renderer, &rect);
  else
    SDL_RenderRect(renderer, &rect);

  for (auto &bar : m_bars) {
    bar.render(renderer);
  }
}

void Sort::randomize() {
  m_bars.clear();
  for (int i = 0; i < NUMBER_OF_BARS; i++) {
    float height = rand() % (VALUE_RANGE + 1);
    float x = get_x() + i * BAR_WIDTH;
    float y = get_y() + ALGO_WINDOW_HEIGHT - height;
    Bar bar(x, y, BAR_WIDTH, height, 0, 0, 0, 255, true, BarState::NOT_SORTED);
    m_bars.push_back(bar);
  }
}

void Sort::start(std::string algorithm) {
  if (algorithm == "selection_sort") {
    m_i = 0;
    m_min_idx = m_i;
    m_j = m_i + 1;
  } else if (algorithm == "bubble_sort") {
    m_i = 0;
    m_j = 0;
  } else if (algorithm == "insertion_sort") {
    m_i = 1;
    m_j = 0;
  }
}

void Sort::reset() {
  m_number_of_comparisons = 0;
  m_bars.clear();
  m_i = 0;
  m_i_prv = 0;
  m_j = 0;
  m_j_prv = 0;
  m_min_idx = 0;
  m_min_idx_prv = 0;
  randomize();
}

void Sort::set_bar_state(int bar_id, BarState state) {
  m_bars[bar_id].set_state(state);
}

BarState Sort::get_bar_state(int bar_id) { return m_bars[bar_id].get_state(); }

void Sort::swap_bars(Bar &bar1, Bar &bar2) {
  int temp_x = bar1.get_x();
  bar1.set_x(bar2.get_x());
  bar2.set_x(temp_x);

  std::swap(bar1, bar2);
}
int Sort::get_number_of_comparisons() { return m_number_of_comparisons; }
