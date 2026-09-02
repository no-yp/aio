#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : m_renderer(nullptr) {}
Renderer::~Renderer() { Shutdown(); }


bool Renderer::Initialize(SDL_Window* window)
{
  m_renderer = SDL_CreateRenderer(window, nullptr);
  if (!m_renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }
  return true;
}


void Renderer::Shutdown() {
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
  }
}


void Renderer::BeginFrame() {
  SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
  SDL_RenderClear(m_renderer);
}

void Renderer::EndFrame() {
  SDL_RenderPresent(m_renderer);
}
