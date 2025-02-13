#include "App.hpp"

#include <memory>

const char App::window_title[] = "algolens";
const SDL_WindowFlags App::window_flags =
    (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
const SDL_RendererFlags App::renderer_flags =
    (SDL_RendererFlags)(SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

App& App::get_instance() {
  static App instance;
  return instance;
}

Maze& App::get_maze() { return *m_maze; }

App::App()
    : m_window_width{1280},
      m_window_height{720},
      m_animation_speed{100},
      m_algo_state{AlgoState::RESET},
      m_algo_type{AlgoType::PATH_FINDING} {
  m_supported_pf_algorithms.push_back("dfs");
  m_supported_pf_algorithms.push_back("bfs");
  m_supported_pf_algorithms.push_back("dijkstra");
  m_supported_s_algorithms.push_back("selection_sort");
}

void App::create_maze() { m_maze = std::make_unique<Maze>(); }

void App::set_window_size(int width, int height) {
  m_window_height = height;
  m_window_width = width;
}

int App::get_window_height() const { return m_window_height; }
int App::get_window_width() const { return m_window_width; }

App::~App() = default;

CursorState App::get_cursor_state() { return m_cursor_state; }
void App::set_cursor_state(CursorState state) { m_cursor_state = state; }

void App::set_animation_speed(int speed) { m_animation_speed = speed; }
int App::get_animation_speed() { return m_animation_speed; }

std::string App::get_current_algorithm() { return m_algorithm; }

void App::set_algorithm(std::string algorithm) {
  m_algorithm = algorithm;
  if (is_pathfinding_algorithm(algorithm)) {
    m_algo_type = AlgoType::PATH_FINDING;
    m_maze->set_algorithm(algorithm);
    return;
  }

  if (is_sorting_algorithm(algorithm)) {
    m_algo_type = AlgoType::SORTING;
    return;
  }
}

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

AlgoType App::get_algo_type() { return m_algo_type; }
void App::set_algo_type(AlgoType type) { m_algo_type = type; }

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
