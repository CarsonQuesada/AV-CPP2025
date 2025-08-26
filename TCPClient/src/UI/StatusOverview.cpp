#include "StatusOverview.h"

#include "imgui.h"
#include "UI.h"
#include "FontManager.h"

StatusOverview::StatusOverview(UILayout& layout)
: layout(layout)
{
}

void StatusOverview::onUpdate()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2.5f, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // Removes the border
    ImGui::SetNextWindowPos(ImVec2(layout.viewport->Pos.x, layout.viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(layout.viewport->Size.x, layout.statusOverviewHeight));
    ImGui::SetNextWindowViewport(layout.viewport->ID);
    ImGui::PushFont(FontManager::GetInstance().GetRegularFontLarge().font);

    ImGui::Begin("Status Overview", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking);

    ImGui::SetCursorPos(ImVec2(2.5f, (layout.statusOverviewHeight - FontManager::GetInstance().GetRegularFontLarge().size) / 2.0));
    ImGui::Text("Speed: %.2f km/h", 42.0f); ImGui::SameLine();
    ImGui::Text("GPS: "); ImGui::SameLine();
    ImGui::TextColored(ImVec4(0, 1, 0, 1), "Online"); ImGui::SameLine();
    ImGui::Text("Connection: "); ImGui::SameLine();
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Unstable");

    ImGui::End();
    ImGui::PopStyleVar(2);
    ImGui::PopFont();
}