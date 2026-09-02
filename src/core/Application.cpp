#include "Application.h"
#include <SDL3/SDL.h>
#include <imgui.h>
#include <iostream>

Application::Application(): m_running(false) {}
Application::~Application() {}


bool Application::Initialize()
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
    SDL_Log("SDL Init failed: %s", SDL_GetError());
    return false;
  }

  m_window = std::make_unique<Window>();
  if ( !m_window->Initialize("aio window", 1280, 720) )
  { return false; }

  m_renderer = std::make_unique<Renderer>();
  if ( !m_renderer->Initialize( m_window->GetWindow() ))
  { return false; }

  m_uiManager = std::make_unique<UIManager>();
  if ( !m_uiManager->Initialize( m_window->GetWindow(),
        m_renderer->GetRenderer())) { return false; }
  
  m_featureManager = std::make_unique<FeatureManager>();
  m_featureManager->Initialize( m_uiManager.get() );

  m_running = true;
  return true;
}


void Application::Run() {
  uint64_t previousTime = SDL_GetPerformanceCounter();
  const uint64_t frequency = SDL_GetPerformanceFrequency();

  while (m_running) {
    const uint64_t currentTime = SDL_GetPerformanceCounter();
    const float deltaTime =
      static_cast<float>(currentTime - previousTime) / frequency;
    previousTime = currentTime;

    ProcessEvents();
    Update(deltaTime);
    Render();
  }
}


void Application::Shutdown() {
  if (m_featureManager)
  { m_featureManager->Shutdown(); }

  if (m_uiManager)
  { m_uiManager->Shutdown(); }

  if (m_renderer)
  { m_renderer->Shutdown(); }

  if (m_window)
  { m_window->Shutdown(); }

  SDL_Quit();
}

void Application::ProcessEvents()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    m_uiManager->ProcessEvent(&event);
    HandleSDLEvent(event);

    if ( event.type == SDL_EVENT_QUIT )
    { m_running = false; }
  }
}


void Application::Update( float deltaTime ) {
  m_uiManager->Update( deltaTime );
  m_featureManager->Update( deltaTime );
}


void Application::Render() {
  m_renderer->BeginFrame();
  m_uiManager->BeginFrame();

  m_uiManager->Render();
  m_featureManager->Render();

  m_uiManager->EndFrame();
  m_renderer->EndFrame();
}


void Application::HandleSDLEvent(const SDL_Event& event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.key == SDLK_ESCAPE) {
      m_running = false;
    }
  }
}
