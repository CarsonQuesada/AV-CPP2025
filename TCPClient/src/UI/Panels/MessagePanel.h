#pragma once

#include <string>
#include <vector>

#include "imgui.h"
#include "UIPanel.h"

enum class UIMessageType
{
    Info,
    Warning,
    Error
};

struct UIMessage
{
    std::string text;
    UIMessageType type;
};

class MessagePanel : public UIPanel
{
public:
    MessagePanel(UIContext& uiContext) : UIPanel(uiContext) {}
    ~MessagePanel() = default;

    void onUpdate() override;
    void addMessage(const std::string& text, UIMessageType type = UIMessageType::Info);
    void clearMessages();

private:
    std::vector<UIMessage> messages;
    ImGuiTextFilter filter;
};
