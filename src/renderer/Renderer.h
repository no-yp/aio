#pragma once
#include <SDL3/SDL.h>

class Renderer {
  public:
    Renderer();
    ~Renderer();

    bool Initialize(SDL_Window* window);
    void Shutdown();

    SDL_Renderer* GetRenderer() const { return m_renderer; }
    
    void BeginFrame();
    void EndFrame();
    
  private:
    SDL_Renderer* m_renderer;
};
