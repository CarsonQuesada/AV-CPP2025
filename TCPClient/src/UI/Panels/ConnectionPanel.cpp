#include "ConnectionPanel.h"

#include <chrono>
#include <thread>
#include <stdio.h>
#include <functional>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

void ConnectionPanel::onUpdate() {
    ImGui::Begin("Connection");

    switch (uiContext.client->getConnectionState()) {
        case ClientConnectionState::Disconnected:
            disconnectedDisplay();
            break;
        case ClientConnectionState::Connecting:
            connectingDisplay();
            break;
        case ClientConnectionState::Connected:
            connectedDisplay();
            break;
        case ClientConnectionState::Reconnecting:
            reconnectingDisplay();
            break;
    }

    ImGui::End();
}

void ConnectionPanel::disconnectedDisplay() {
    ImGui::Text("Status: Disconnected");

    float buttonWidth = 150.0f;
    float spacing = 10.0f;

    ImGui::Dummy(ImVec2(0.0f, spacing));

    float panelWidth = ImGui::GetContentRegionAvail().x;
    ImGui::SetCursorPosX((panelWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("Connect Locally", ImVec2(buttonWidth, 0))) {
        uiContext.client->connectLocally();
    }

    ImGui::Dummy(ImVec2(0.0f, spacing));

    ImGui::SetCursorPosX((panelWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("Connect Remotely", ImVec2(buttonWidth, 0))) {
        uiContext.client->connectRemotely();
    }
}

void ConnectionPanel::connectingDisplay() {
    static float dotAnim = 0.0f;
    dotAnim += ImGui::GetIO().DeltaTime * 4.0f;
    int dots = static_cast<int>(dotAnim) % 4;

    std::string connectingText = "Connecting";
    connectingText.append(dots, '.');

    ImGui::Text("Status: %s", connectingText.c_str());

    float buttonWidth = 100.0f;
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    float panelWidth = ImGui::GetContentRegionAvail().x;
    ImGui::SetCursorPosX((panelWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0))) {
        uiContext.client->cancelConnectAttempt();
    }
}

void ConnectionPanel::connectedDisplay() {
    ImGui::Text("Status: Connected");

    float buttonWidth = 120.0f;
    float panelWidth = ImGui::GetContentRegionAvail().x;

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::SetCursorPosX((panelWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("Disconnect", ImVec2(buttonWidth, 0))) {
        uiContext.client->disconnect();
    }

    ImGui::Dummy(ImVec2(0.0f, 15.0f));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 10.0f));

    lastPingMs = uiContext.client->getConnectionSpeed();
    if (lastPingMs >= 0.0f) {
        ImGui::Text("Ping: %.2f ms", lastPingMs);
    } else {
        ImGui::Text("Ping: --");
    }
}

void ConnectionPanel::reconnectingDisplay() {
    static float dotAnim = 0.0f;
    dotAnim += ImGui::GetIO().DeltaTime * 4.0f;
    int dots = static_cast<int>(dotAnim) % 4;

    std::string reconnectingText = "Reconnecting";
    reconnectingText.append(dots, '.');

    ImGui::Text("Status: %s", reconnectingText.c_str());

    float buttonWidth = 100.0f;
    float panelWidth = ImGui::GetContentRegionAvail().x;

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::SetCursorPosX((panelWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0))) {
        uiContext.client->cancelConnectAttempt();
    }

    ImGui::Dummy(ImVec2(0.0f, 5.0f));
    ImGui::TextWrapped("Attempting to reconnect using previous method.");
}

void CenteredButton(const char* label, float width, std::function<void()> onClick) {
    float panelWidth = ImGui::GetContentRegionAvail().x;
    ImGui::SetCursorPosX((panelWidth - width) * 0.5f);
    if (ImGui::Button(label, ImVec2(width, 0))) {
        onClick();
    }
}
