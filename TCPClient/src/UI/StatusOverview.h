#pragma once

#include "UIContext.h"

struct UILayout;

class StatusOverview
{
public:
    StatusOverview(UILayout& layout, UIContext& uiContext);
    ~StatusOverview() = default;

    void onUpdate();
private:
    UILayout& layout;
    UIContext& uiContext;
};