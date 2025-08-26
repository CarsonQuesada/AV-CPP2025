#pragma once

#include "imgui.h"

struct UILayout;

class Dockspace
{
public:
    Dockspace(UILayout& layout);

    void begin();
    void end();

    ImGuiID getDockspaceID() const { return dockspaceID; };

private:
    UILayout& layout;
    ImGuiID dockspaceID;
};