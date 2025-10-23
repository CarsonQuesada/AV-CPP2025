#pragma once

#include "UI/UIContext.h"

class UIPanel {
public:
    explicit UIPanel(UIContext& uiContext) : uiContext(uiContext) {}
    virtual ~UIPanel() = default;

    // Virtual update method to be implemented by derived panels
    virtual void onUpdate() = 0;

protected:
    UIContext& uiContext;
};
