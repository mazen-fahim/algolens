#include "App.hpp"

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

App::App() : m_window_width{1080}, m_window_height{720} {}

void App::set_window_size(int width, int height) {
  m_window_height = height;
  m_window_width = width;
}

int App::get_window_height() const { return m_window_height; }
int App::get_window_width() const { return m_window_width; }

void App::create_maze(int number_of_rows, int number_of_cols) {
  m_maze = std::make_unique<Maze>(number_of_rows, number_of_cols);
}

App::~App() = default;
