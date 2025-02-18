#include "App.hpp"

#include <memory>

#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_video.h"
#include "defs.hpp"

const char App::window_title[] = "algolens";
const SDL_WindowFlags App::window_flags =
    (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN |
                      SDL_WINDOW_OPENGL);

App& App::get_instance() {
  static App instance;
  return instance;
}

Maze& App::get_maze() { return *m_maze; }
Sort& App::get_sort() { return *m_sort; }

App::App()
    : m_window_width{DEFAULT_WINDOW_WIDTH},
      m_window_height{DEFAULT_WINDOW_HEIGHT},
      m_animation_speed{DEFAULT_ANIMATION_SPEED},
      m_algo_state{AlgoState::RESET},
      m_previous_tick_frame{0},
      m_previous_tick_update{0},
      m_time_since_last_update{0} {
  m_supported_pf_algorithms.push_back("dfs");
  m_algorithm_complexity["dfs"] = "O(V + E)";
  m_supported_pf_algorithms.push_back("bfs");
  m_algorithm_complexity["bfs"] = "O(V + E)";

  m_supported_s_algorithms.push_back("selection_sort");
  m_algorithm_complexity["selection_sort"] = "O(N^2)";
  m_supported_s_algorithms.push_back("bubble_sort");
  m_algorithm_complexity["bubble_sort"] = "O(N^2)";
  m_supported_s_algorithms.push_back("insertion_sort");
  m_algorithm_complexity["insertion_sort"] = "O(N^2)";
}

void App::create_maze() { m_maze = std::make_unique<Maze>(); }
void App::create_sort() { m_sort = std::make_unique<Sort>(); }

void App::set_window_size(int width, int height) {
  m_window_height = height;
  m_window_width = width;
}
int App::get_window_height() const { return m_window_height; }
int App::get_window_width() const { return m_window_width; }

void App::set_cursor_state(CursorState state) { m_cursor_state = state; }
CursorState App::get_cursor_state() { return m_cursor_state; }

void App::set_animation_speed(int speed) { m_animation_speed = speed; }
int App::get_animation_speed() { return m_animation_speed; }

void App::set_algorithm(std::string algorithm) { m_algorithm = algorithm; }
std::string App::get_current_algorithm() { return m_algorithm; }

bool App::is_pathfinding_algorithm(std::string algorithm) {
  for (auto& algo : m_supported_pf_algorithms)
    if (algorithm == algo) return true;
  return false;
}

bool App::is_sorting_algorithm(std::string algorithm) {
  for (auto& algo : m_supported_s_algorithms)
    if (algorithm == algo) return true;
  return false;
}

AlgoState App::get_algo_state() { return m_algo_state; }

void App::set_algo_state(AlgoState state) { m_algo_state = state; }

std::vector<std::string> App::get_supported_algorithms() {
  std::vector<std::string> supported_algorithms;
  for (auto& algo : m_supported_pf_algorithms)
    supported_algorithms.push_back(algo);
  for (auto& algo : m_supported_s_algorithms)
    supported_algorithms.push_back(algo);
  return supported_algorithms;
}

std::vector<std::string> App::get_supported_pf_algorithms() {
  return m_supported_pf_algorithms;
}
std::vector<std::string> App::get_supported_s_algorithms() {
  return m_supported_s_algorithms;
}

void App::start() {
  if (is_pathfinding_algorithm(m_algorithm)) {
    if (m_algo_state == AlgoState::RESET) {
      m_maze->start(m_algorithm);
      m_algo_state = AlgoState::ALGORITHM_RUN;
    }
  } else {
    if (m_algo_state == AlgoState::RESET) {
      m_sort->start(m_algorithm);
      m_algo_state = AlgoState::ALGORITHM_RUN;
    }
  }
}

void App::pause() {
  if (is_pathfinding_algorithm(m_algorithm)) {
    if (m_algo_state == AlgoState::ALGORITHM_RUN)
      m_algo_state = AlgoState::ALGORITHM_PAUSE;
    else if (m_algo_state == AlgoState::PATH_RUN)
      m_algo_state = AlgoState::PATH_PAUSE;
  } else {
    if (m_algo_state == AlgoState::ALGORITHM_RUN)
      m_algo_state = AlgoState::ALGORITHM_PAUSE;
  }
}

void App::resume() {
  if (is_pathfinding_algorithm(m_algorithm)) {
    if (m_algo_state == AlgoState::ALGORITHM_PAUSE)
      m_algo_state = AlgoState::ALGORITHM_RUN;
    else if (m_algo_state == AlgoState::PATH_PAUSE)
      m_algo_state = AlgoState::PATH_RUN;
  } else {
    if (m_algo_state == AlgoState::ALGORITHM_PAUSE)
      m_algo_state = AlgoState::ALGORITHM_RUN;
  }
}

void App::reset() {
  if (is_pathfinding_algorithm(m_algorithm)) {
    m_maze->reset();
  } else {
    m_sort->reset();
  }
  m_algo_state = AlgoState::RESET;
}

void App::draw() {
  if (is_pathfinding_algorithm(m_algorithm)) {
    m_maze->draw();
  } else {
    m_sort->draw();
  }
}

void App::render(SDL_Renderer* renderer) {
  if (is_pathfinding_algorithm(m_algorithm)) {
    m_maze->render(renderer);
  } else {
    m_sort->render(renderer);
  }
}

Uint32 App::get_delay_time() {
  Uint64 ct = SDL_GetPerformanceCounter();
  Uint64 elapsed =
      (ct - m_previous_tick_frame) * 1000 / SDL_GetPerformanceFrequency();
  m_previous_tick_frame = ct;

  float target_time_per_frame = 1000.0f / FPS;
  if (elapsed < target_time_per_frame)
    return static_cast<Uint32>(target_time_per_frame - elapsed);
  else
    return 0;
}

bool App::should_update() {
  Uint64 ct = SDL_GetPerformanceCounter();
  Uint64 elapsed =
      (ct - m_previous_tick_update) * 1000 / SDL_GetPerformanceFrequency();
  m_previous_tick_update = ct;
  m_time_since_last_update += elapsed;
  float target_time_per_update =
      1000.0f / (static_cast<float>(m_animation_speed) / 100.0f * UPS);

  if (m_time_since_last_update >= target_time_per_update) {
    m_time_since_last_update = 0;
    return true;
  } else
    return false;
}
std::string App::get_current_algorithm_complexity() {
  return m_algorithm_complexity[m_algorithm];
}
