#pragma once
#include <memory>
#include <vector>
#include <string>
#include "ui/UIManager.h"

class IFeature {
  public:
    virtual ~IFeature() = default;
    virtual std::string GetName() const = 0;
    virtual void Initialize(UIManager* uiManager) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void Shutdown() = 0;
};

class FeatureManager {
  public:
    FeatureManager();
    ~FeatureManager();
    
    void Initialize(UIManager* uiManager);
    void Update(float deltaTime);
    void Render();
    void Shutdown();
    
    template<typename T, typename... Args>
    void RegisterFeature(Args&&... args) {
      auto feature = std::make_unique<T>(std::forward<Args>(args)...);
      feature->Initialize(m_uiManager);
      m_features.push_back(std::move(feature));
    }
    
  private:
    UIManager* m_uiManager;
    std::vector<std::unique_ptr<IFeature>> m_features;
};
