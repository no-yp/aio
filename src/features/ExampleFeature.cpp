#include "ExampleFeature.h"
#include <imgui.h>

ExampleFeature::ExampleFeature() 
  : m_uiManager(nullptr)
  , m_showWindow(true)
  , m_floatValue(0.5f)
  , m_intValue(42)
  , m_boolValue(true)
{
  memset(m_textBuffer, 0, sizeof(m_textBuffer));
  strcpy(m_textBuffer, "Hello ImGui!");
}

ExampleFeature::~ExampleFeature() {}

std::string ExampleFeature::GetName() const {
  return "Example Feature";
}

void ExampleFeature::Initialize(UIManager* uiManager) {
  m_uiManager = uiManager;
    
  // Register UI panels for this feature
  if (m_uiManager) {
    m_uiManager->RegisterPanel("Example Feature Panel", [this]() {
      this->Render();
    });
  }
}

void ExampleFeature::Update(float deltaTime) {
  // Update feature logic here
}

void ExampleFeature::Render() {
  if (!m_showWindow) return;

  ImGui::Begin("Example Feature", &m_showWindow);

  // Text input
  ImGui::InputText("Text Input", m_textBuffer, sizeof(m_textBuffer));

  // Sliders
  ImGui::SliderFloat("Float Value", &m_floatValue, 0.0f, 1.0f);
  ImGui::SliderInt("Int Value", &m_intValue, 0, 100);

  // Checkbox
  ImGui::Checkbox("Checkbox", &m_boolValue);

  // Button
  if (ImGui::Button("Click Me!")) {
    SDL_Log("Button clicked!");
  }

  // Display some info
  ImGui::Text("Application is running!");
  ImGui::Text("Float: %.3f", m_floatValue);
  ImGui::Text("Int: %d", m_intValue);
  ImGui::Text("Bool: %s", m_boolValue ? "true" : "false");

  ImGui::End();
}

void ExampleFeature::Shutdown() {
  if (m_uiManager) {
    m_uiManager->UnregisterPanel("Example Feature Panel");
  }
}
