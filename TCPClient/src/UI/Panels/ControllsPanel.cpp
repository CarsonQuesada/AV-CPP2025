#include "ControllsPanel.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void ControllsPanel::onUpdate()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Begin("Controls");

    // === Drive Controls ===
    ImGui::Text("Drive Controls"); ImGui::Separator();
    ImGui::Text("  Forward (W):   %s", io.KeysDown[ImGuiKey_W] ? "Pressed" : "Released");
    ImGui::Text("  Reverse (S):   %s", io.KeysDown[ImGuiKey_S] ? "Pressed" : "Released");
    ImGui::Text("  Turn Right (D): %s", io.KeysDown[ImGuiKey_D] ? "Pressed" : "Released");
    ImGui::Text("  Turn Left (A):  %s", io.KeysDown[ImGuiKey_A] ? "Pressed" : "Released");
    ImGui::Text("  Brake (Space):  %s", io.KeysDown[ImGuiKey_Space] ? "Pressed" : "Released");

    ImGui::Spacing();

    // === Camera Controls ===
    ImGui::Text("Camera Controls"); ImGui::Separator();
    ImGui::Text("  Pan Left (J):   %s", io.KeysDown[ImGuiKey_J] ? "Pressed" : "Released");
    ImGui::Text("  Center (K):     %s", io.KeysDown[ImGuiKey_K] ? "Pressed" : "Released");
    ImGui::Text("  Pan Right (L):  %s", io.KeysDown[ImGuiKey_L] ? "Pressed" : "Released");
    

    ImGui::End();
}
