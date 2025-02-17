#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Maze.hpp"
#include "SDL3/SDL.h"
#include "SDL3/SDL_stdinc.h"
#include "Sort.hpp"

enum class AlgoState {
  RESET,
  ALGORITHM_RUN,
  ALGORITHM_PAUSE,
  PATH_PAUSE,
  PATH_RUN,
  FINISH,
  FINISH_TARGET_NOT_FOUND,
};

enum class CursorState {
  ARROW,
  TEXT_INPUT,
  RESIZE_ALL,
  RESIZE_NS,
  RESIZE_EW,
  RESIZE_NESW,
  RESIZE_NWSE,
  HAND,
  NOT_ALLOWED,

};

// A singelton
class App {
 public:
  // this way you have a controlled access to the global App state
  // Singelton pattern
  static App& get_instance();

  Maze& get_maze();
  Sort& get_sort();

  void create_maze();
  void create_sort();

  void set_window_size(int width, int height);
  int get_window_width() const;
  int get_window_height() const;

  CursorState get_cursor_state();
  void set_cursor_state(CursorState state);

  void set_animation_speed(int speed);
  int get_animation_speed();
  bool is_pathfinding_algorithm(std::string algorithm);
  bool is_sorting_algorithm(std::string algorithm);

  std::string get_current_algorithm();
  void set_algorithm(std::string algorithm);

  const static SDL_WindowFlags window_flags;
  const static char window_title[];

  AlgoState get_algo_state();
  void set_algo_state(AlgoState state);

  std::vector<std::string> get_supported_algorithms();
  std::vector<std::string> get_supported_pf_algorithms();
  std::vector<std::string> get_supported_s_algorithms();

  void reset();
  void resume();
  void start();
  void pause();
  void update();
  void draw();
  void render(SDL_Renderer* renderer);

  Uint32 get_delay_time();
  bool should_update();

  std::string get_current_algorithm_complexity();

 private:
  App();
  ~App() = default;
  std::unique_ptr<Maze> m_maze;
  std::unique_ptr<Sort> m_sort;
  int m_window_width;
  int m_window_height;
  int m_animation_speed;
  CursorState m_cursor_state;
  std::vector<std::string> m_supported_pf_algorithms;
  std::vector<std::string> m_supported_s_algorithms;
  std::string m_algorithm;

  Uint64 m_time_since_last_update;
  Uint64 m_previous_tick_frame;
  Uint64 m_previous_tick_update;
  std::map<std::string, std::string> m_algorithm_complexity;

  AlgoState m_algo_state;
};
