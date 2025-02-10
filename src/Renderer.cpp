#include "renderer.hpp"

#include <iostream>

Renderer::Renderer(SDL_Window *window) {
  // Create renderer
  m_renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!m_renderer) {
    // TODO: Implement error reporting
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
  }
}

Renderer::~Renderer() { SDL_DestroyRenderer(m_renderer); }

void Renderer::draw() {
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  SDL_SetRenderDrawColor(rendererGlobal, rectangle->red, rectangle->green,
                         rectangle->blue, rectangle->alpha);
  SDL_RenderFillRect(rendererGlobal, &(rectangle->rect));

  SDL_RenderPresent(m_renderer);
}
