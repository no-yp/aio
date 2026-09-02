#pragma once
#include "FeatureManager.h"

class ExampleFeature : public IFeature {
  public:
    ExampleFeature();
    ~ExampleFeature() override;
    
    std::string GetName() const override;
    void Initialize(UIManager* uiManager) override;
    void Update(float deltaTime) override;
    void Render() override;
    void Shutdown() override;
    
  private:
    UIManager* m_uiManager;
    bool m_showWindow;
    float m_floatValue;
    int m_intValue;
    bool m_boolValue;
    char m_textBuffer[256];
};
