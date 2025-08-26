#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

#include "imgui.h"
#include "StatusOverview.h"
#include "Dockspace.h"
#include "Panels/UIPanel.h"
#include "Panels/AutopilotPanel.h"
#include "Panels/CameraFeedPanel.h"
#include "Panels/ConnectionPanel.h"
#include "Panels/ControllsPanel.h"
#include "Panels/MessagePanel.h"
#include "Panels/VehiclePanel.h"
#include "Communication/VehicleClient.h"
#include "VehicleController.h"
#include "UIContext.h"

struct UILayout 
{
    ImGuiViewport* viewport = nullptr;
    float statusOverviewHeight = 0.0f;

    ImVec2 getDockspacePos() const {
        return ImVec2(viewport->Pos.x, viewport->Pos.y + statusOverviewHeight);
    }

    ImVec2 getDockspaceSize() const {
        return ImVec2(viewport->Size.x, viewport->Size.y - statusOverviewHeight);
    }
};

class UI
{
public:
    UI(GLFWwindow* imguiContext, VehicleClient& client, VehicleController& controller);
    ~UI();

    void onUpdate();
    void render();

private:
    GLFWwindow* window;
    UILayout layout;
    std::vector<std::unique_ptr<UIPanel>> panels;
    StatusOverview statusOverview;
    Dockspace dockspace;
    FrameProcessor frameProcessor;
    MJPEGClient videoStream;
    UIContext uiContext;
};