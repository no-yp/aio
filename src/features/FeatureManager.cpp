#include "FeatureManager.h"
#include "ExampleFeature.h"

FeatureManager::FeatureManager() : m_uiManager(nullptr) {}
FeatureManager::~FeatureManager() { Shutdown(); }

void FeatureManager::Initialize(UIManager* uiManager) {
  m_uiManager = uiManager;
    
  // Register default features
  RegisterFeature<ExampleFeature>();
}

void FeatureManager::Update(float deltaTime) {
  for (auto& feature : m_features) {
    feature->Update(deltaTime);
  }
}

void FeatureManager::Render() {
  for (auto& feature : m_features) {
    feature->Render();
  }
}

void FeatureManager::Shutdown() {
  for (auto& feature : m_features) {
    feature->Shutdown();
  }
  m_features.clear();
}
