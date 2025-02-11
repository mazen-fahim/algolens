#pragma once
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <memory>

#include "Maze.hpp"

// A singelton
class App {
 public:
  // this way you have a controlled access to the global App state
  // Singelton pattern
  static App& get_instance();
  // controlled access to the global maze inside of the global
  // singelton object
  Maze& get_maze();
  void create_maze(int number_of_rows, int number_of_cols);
  int get_window_width() const;
  int get_window_height() const;

  void set_window_size(int width, int height);

  const static SDL_WindowFlags window_flags;
  const static SDL_RendererFlags renderer_flags;
  const static char window_title[];

 private:
  App();
  ~App();
  std::unique_ptr<Maze> m_maze;
  int m_window_width;
  int m_window_height;
};
