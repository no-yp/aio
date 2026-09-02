#pragma once
#include <memory>
#include "Window.h"
#include <renderer/Renderer.h>
#include <ui/UIManager.h>
#include <features/FeatureManager.h>

class Application {
  public:
    Application();
    ~Application();

    bool Initialize();
    void Run();
    void Shutdown();

  private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<UIManager> m_uiManager;
    std::unique_ptr<FeatureManager> m_featureManager;

    bool m_running;

    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void HandleSDLEvent(const SDL_Event& event);
};
