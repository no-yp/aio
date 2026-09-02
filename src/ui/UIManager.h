#pragma once
#include <SDL3/SDL.h>
#include <imgui.h>
#include <memory>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

class UIManager {
  public:
    UIManager();
    ~UIManager();
    
    bool Initialize(SDL_Window* window, SDL_Renderer* renderer);
    void Shutdown();
    
    void ProcessEvent(const SDL_Event* event);
    void Update(float deltaTime);
    void BeginFrame();
    void EndFrame();
    void Render();
    
    // Register UI panels
    using UIPanel = std::function<void()>;
    void RegisterPanel(const std::string& name, UIPanel panel);
    void UnregisterPanel(const std::string& name);
    
  private:
    struct PanelData {
        std::string name;
        UIPanel panel;
        bool visible;
    };
    
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::vector<PanelData> m_panels;
    bool m_showDemoWindow;
    ImGuiContext* m_imguiContext;
    
    void SetupImGuiStyle();
};
