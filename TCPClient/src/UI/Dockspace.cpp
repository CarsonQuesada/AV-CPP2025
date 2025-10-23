#include "Dockspace.h"

#include "UI.h"

Dockspace::Dockspace(UILayout &layout)
: layout(layout)
{
}

void Dockspace::begin()
{
    ImGui::SetNextWindowPos(layout.getDockspacePos());
    ImGui::SetNextWindowSize(layout.getDockspaceSize());
    ImGui::SetNextWindowViewport(layout.viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGuiWindowFlags dockspace_flags =
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("MainDockSpace", nullptr, dockspace_flags);

    ImGuiID dockspace_id = ImGui::GetID("MainDockSpaceID");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
}

void Dockspace::end()
{
    ImGui::End();
    ImGui::PopStyleVar(2);
}