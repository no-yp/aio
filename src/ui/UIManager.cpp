#include "UIManager.h"
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <iostream>

UIManager::UIManager() 
  : m_window(nullptr),
  m_renderer(nullptr),
  m_showDemoWindow(false),
  m_imguiContext(nullptr)
{}

UIManager::~UIManager() { Shutdown(); }

bool UIManager::Initialize(SDL_Window* window, SDL_Renderer* renderer)
{
  m_window = window;
  m_renderer = renderer;

  IMGUI_CHECKVERSION();
  m_imguiContext = ImGui::CreateContext();
  ImGui::SetCurrentContext(m_imguiContext);

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Setup ImGui SDL3 dan SDL Renderer
  if (!ImGui_ImplSDL3_InitForSDLRenderer(window, renderer)) {
    std::cerr << "Failed to initialize ImGui SDL3 backend" << std::endl;
    return false;
  }

  if (!ImGui_ImplSDLRenderer3_Init(renderer)) {
    std::cerr << "Failed to initialize ImGui SDL Renderer backend" << std::endl;
    return false;
  }

  SetupImGuiStyle();
    
  // Register default panels
  RegisterPanel("ImGui Demo", [this]() {
    if (m_showDemoWindow) {
      ImGui::ShowDemoWindow(&m_showDemoWindow);
    }
  });
  return true;
}

void UIManager::Shutdown() {
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  if (m_imguiContext) {
    ImGui::DestroyContext(m_imguiContext);
    m_imguiContext = nullptr;
  }
}

void UIManager::ProcessEvent(const SDL_Event* event) {
  ImGui_ImplSDL3_ProcessEvent(event);
}

void UIManager::Update(float deltaTime) {
  // Update UI logic here if needed
}

void UIManager::BeginFrame() {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void UIManager::EndFrame() {
    // Render dilakukan di Render()
}

void UIManager::Render() {
  ImGui::Render();
  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());

  // Update and render additional platform windows
  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    SDL_Window* backup_current_window = SDL_GetWindowFromID(SDL_GetCurrentWindowID());
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    if (backup_current_window) {
      SDL_SetWindowFocus(backup_current_window);
    }
  }
}

void UIManager::RegisterPanel(const std::string& name, UIPanel panel) {
  // Check if panel already exists
  for (auto& p : m_panels) {
    if (p.name == name) {
      p.panel = panel;
      return;
    }
  }
  m_panels.push_back({name, panel, true});
}

void UIManager::UnregisterPanel(const std::string& name) {
  m_panels.erase(
    std::remove_if(m_panels.begin(), m_panels.end(),
    [&name](const PanelData& p) { return p.name == name; }),
    m_panels.end()
  );
}

void UIManager::SetupImGuiStyle() {
  // Style yang sama seperti sebelumnya
  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowPadding = ImVec2(8.0f, 8.0f);
  style.WindowRounding = 0.0f;
  style.FramePadding = ImVec2(4.0f, 3.0f);
  style.FrameRounding = 0.0f;
  style.ItemSpacing = ImVec2(8.0f, 4.0f);
  style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
  style.IndentSpacing = 21.0f;
  style.ScrollbarSize = 14.0f;
  style.ScrollbarRounding = 0.0f;
  style.GrabMinSize = 10.0f;
  style.GrabRounding = 0.0f;
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

  // Dark style (sama seperti sebelumnya)
  ImVec4* colors = style.Colors;
  colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg]              = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
  colors[ImGuiCol_ChildBg]               = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
  colors[ImGuiCol_PopupBg]               = ImVec4(0.10f, 0.10f, 0.10f, 0.90f);
  colors[ImGuiCol_Border]                = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
  colors[ImGuiCol_FrameBgActive]         = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
  colors[ImGuiCol_TitleBg]               = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_TitleBgActive]         = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_MenuBarBg]             = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_CheckMark]             = ImVec4(0.80f, 0.50f, 0.20f, 1.00f);
  colors[ImGuiCol_SliderGrab]            = ImVec4(0.80f, 0.50f, 0.20f, 1.00f);
  colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.90f, 0.60f, 0.30f, 1.00f);
  colors[ImGuiCol_Button]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_ButtonHovered]         = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
  colors[ImGuiCol_ButtonActive]          = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
  colors[ImGuiCol_Header]                = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_HeaderHovered]         = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_HeaderActive]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_Separator]             = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_SeparatorActive]       = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_ResizeGrip]            = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_Tab]                   = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_TabHovered]            = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_TabActive]             = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_TabUnfocused]          = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_DockingPreview]        = ImVec4(0.80f, 0.50f, 0.20f, 0.50f);
  colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_PlotLines]             = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.50f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram]         = ImVec4(0.80f, 0.50f, 0.20f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_TableBorderLight]      = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_TableRowBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.00f, 1.00f, 1.00f, 0.03f);
  colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.80f, 0.50f, 0.20f, 0.50f);
  colors[ImGuiCol_DragDropTarget]        = ImVec4(0.80f, 0.50f, 0.20f, 0.50f);
  colors[ImGuiCol_NavHighlight]          = ImVec4(0.80f, 0.50f, 0.20f, 0.50f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.80f, 0.50f, 0.20f, 0.50f);
  colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
  colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
}
