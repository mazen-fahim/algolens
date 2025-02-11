#include "App.hpp"

#include <SDL_video.h>

char App::window_title[] = "algolens";
SDL_WindowFlags App::window_flags =
    (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
SDL_RendererFlags App::renderer_flags =
    (SDL_RendererFlags)(SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
int App::window_width = 1080;
int App::window_height = 720;
