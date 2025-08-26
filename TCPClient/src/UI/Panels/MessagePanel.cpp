#include "MessagePanel.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

void MessagePanel::addMessage(const std::string& text, UIMessageType type)
{
    messages.push_back({ text, type });

    const size_t MAX_MESSAGES = 100;
    if (messages.size() > MAX_MESSAGES)
        messages.erase(messages.begin());
}

void MessagePanel::clearMessages()
{
    messages.clear();
}

void MessagePanel::onUpdate()
{
    ImGui::Begin("Message Log", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    // Header area with filter and clear button
    ImGui::Text("Diagnostics & Errors"); 
    ImGui::Separator();

    float avail = ImGui::GetContentRegionAvail().x;
    float clearWidth = 60.0f;
    float spacing = ImGui::GetStyle().ItemSpacing.x;

    ImGui::Text("Filter:");
    ImGui::SameLine();
    filter.Draw("##Filter", avail - clearWidth - spacing - ImGui::CalcTextSize("Filter:").x);
    ImGui::SameLine();
    if (ImGui::Button("Clear", ImVec2(60, 0)))
        clearMessages();

    ImGui::Spacing();
    ImGui::BeginChild("LogRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& msg : messages)
    {
        if (!filter.PassFilter(msg.text.c_str()))
            continue;

        ImVec4 color;
        const char* icon = "";

        switch (msg.type)
        {
            case UIMessageType::Info:
                color = ImVec4(1, 1, 1, 1);
                icon = "[i] ";
                break;
            case UIMessageType::Warning:
                color = ImVec4(1, 1, 0, 1);
                icon = "[!] ";
                break;
            case UIMessageType::Error:
                color = ImVec4(1, 0.4f, 0.4f, 1);
                icon = "[x] ";
                break;
        }

        ImGui::TextColored(color, "%s%s", icon, msg.text.c_str());
    }

    // Auto-scroll to bottom
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();

    ImGui::End();
}

