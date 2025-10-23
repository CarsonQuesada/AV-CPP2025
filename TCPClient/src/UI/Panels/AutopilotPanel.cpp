#include "AutopilotPanel.h"

#include "stdio.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void AutopilotPanel::onUpdate() 
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Begin("Autopilot Control");

    ImGui::Spacing(); 
    ImGui::Text("Autopilot"); 
    ImGui::Separator();

    if (ImGui::BeginTable("AutopilotTable", 3, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_SizingFixedSame))
    {
        ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed, 120); // Label
        ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed, 50);  // Status
        ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed, 100); // Toggle

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Enabled [1]");

        ImGui::TableNextColumn();
        if (VehicleState::getInstance().stateMode.mode == 3) { // Autopilot active
            ImVec4 color = ImVec4(0, 1, 0, 1);
            ImGui::TextColored(color, "YES");
        } else {
            ImVec4 color = ImVec4(1, 0, 0, 1);
            ImGui::TextColored(color, "NO");
        }

        ImGui::TableNextColumn();
        if (ImGui::Button("Toggle##Autopilot", ImVec2(100, 0))) {
            uiContext.controller->updateUIButton(ButtonID::ToggleAutopilot, true);
        } else {
            uiContext.controller->updateUIButton(ButtonID::ToggleAutopilot, false);
        }

        ImGui::EndTable();
    }

    ImGui::Text("Target Waypoint: Not yet implemented");

    ImGui::End();
}
