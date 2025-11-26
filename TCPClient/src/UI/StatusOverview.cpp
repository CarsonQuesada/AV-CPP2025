#include "StatusOverview.h"

#include "imgui.h"
#include "UI.h"
#include "FontManager.h"
#include "VehicleState.h"

StatusOverview::StatusOverview(UILayout& layout, UIContext& uiContext)
: layout(layout), uiContext(uiContext)
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
    ImGui::Text("Battery: %i%", VehicleState::getInstance().genStatus.batteryPercent); ImGui::SameLine();
    ImGui::Text("Speed: %.2f m/s", VehicleState::getInstance().genStatus.speed / 1000.0f); ImGui::SameLine();
    ImGui::Text("Connection: "); ImGui::SameLine();
    switch (uiContext.client->getConnectionState())
    {
        case ClientConnectionState::Connected:
            ImGui::Text("Connected   "); ImGui::SameLine();
            break;
        case ClientConnectionState::Connecting:
            ImGui::Text("Connecting  "); ImGui::SameLine();
            break;
        case ClientConnectionState::Disconnected:
            ImGui::Text("Offline     "); ImGui::SameLine();
            break;
        case ClientConnectionState::Reconnecting:
            ImGui::Text("Reconnecting"); ImGui::SameLine();
            break;
    }

    ImGui::End();
    ImGui::PopStyleVar(2);
    ImGui::PopFont();
}