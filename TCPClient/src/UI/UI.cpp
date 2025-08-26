#include "UI.h"

#include <iostream>
#include <algorithm>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "StatusOverview.h"
#include "ResourceManager.h"
#include "FontManager.h"
#include "FrameProcessor.h"

UI::UI(GLFWwindow *imguiContext, VehicleClient& client, VehicleController& controller)
    : window(imguiContext), statusOverview(StatusOverview(layout)), dockspace(Dockspace(layout)), 
      videoStream("http://192.168.8.132:8080/stream", frameProcessor)
{
    uiContext.client = &client;
    uiContext.controller = &controller;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Load custom font
    FontManager::GetInstance().LoadFonts();

    // Configure layout
    layout.viewport = ImGui::GetMainViewport();
    layout.statusOverviewHeight = 30.0f;

    frameProcessor.start();
    videoStream.start();

    panels.push_back(std::make_unique<VehiclePanel>(uiContext));
    panels.push_back(std::make_unique<MessagePanel>(uiContext));
    panels.push_back(std::make_unique<CameraFeedPanel>(uiContext, frameProcessor));
    panels.push_back(std::make_unique<ConnectionPanel>(uiContext));
    panels.push_back(std::make_unique<ControllsPanel>(uiContext));
    panels.push_back(std::make_unique<AutopilotPanel>(uiContext));
}

UI::~UI() {
    frameProcessor.stop();
    videoStream.stop();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "Pause 3" << std::endl;
}

void UI::onUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::PushFont(FontManager::GetInstance().GetRegularFont().font);

    statusOverview.onUpdate();

    dockspace.begin();
    for (auto& panel : panels)
    {
        panel->onUpdate();
    }
    dockspace.end();

    ImGui::PopFont();
}    

void UI::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
