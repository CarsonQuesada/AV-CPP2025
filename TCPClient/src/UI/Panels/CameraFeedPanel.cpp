#include "CameraFeedPanel.h"

#include <glad/glad.h>
#include <iostream>

#ifndef IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "Shared/Keys.h"

CameraFeedPanel::CameraFeedPanel(UIContext& uiContext)
    : UIPanel(uiContext), videoStream(BuildMjpegUrl(ConnectionType::None), frameProcessor)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    frameProcessor.start();
}

CameraFeedPanel::~CameraFeedPanel()
{
    stopStream();
    frameProcessor.stop();
    glDeleteTextures(1, &texture);
}

void CameraFeedPanel::onUpdate()
{
    bool open = true;
    const bool showContents = ImGui::Begin("Camera Feed", &open);

    // --- Controls ---
    ImGui::Checkbox("Enable stream", &userEnabled);

    // Route-based override (only meaningful on Local route)
    const ConnectionType route = uiContext.connectionType();
    if (route == ConnectionType::Local) {
        ImGui::SameLine();
        ImGui::Checkbox("Use remote relay (even on local)", &forceRemoteOnLocal);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Prefer remote stream even when connected locally.");
    }
    ImGui::Separator();

    const bool connected = uiContext.isConnected();
    const bool visible   = showContents && !ImGui::IsWindowCollapsed();
    const bool wantStream = connected && userEnabled && visible;

    // --- Decide which host to target ---
    // Default: remote when Remote route; local when Local route (unless user forces remote).
    ConnectionType preferredHost = ConnectionType::None;
    switch (route) {
        case ConnectionType::Local:
            preferredHost = forceRemoteOnLocal ? ConnectionType::Remote : ConnectionType::Local;
            break;
        case ConnectionType::Remote:
            preferredHost = ConnectionType::Remote;
            break;
        default: // None / Unknown
            // If we don't know, stick with whatever we last used; if none yet, default to remote.
            break;
    }

    // Remember and apply only when changed (so we don’t spam setUrl)
    static ConnectionType lastHost = ConnectionType::None;
    if (preferredHost != lastHost) {
        videoStream.setUrl(BuildMjpegUrl(preferredHost));
        lastHost = preferredHost;
    }

    // --- Start/Stop gating (no changes to your helpers) ---
    if (wantStream && !streaming) {
        startStream();
    } else if (!wantStream && streaming) {
        stopStream();
    }

    // --- Status line ---
    const char* routeText =
        (route == ConnectionType::Local)  ? "Local" :
        (route == ConnectionType::Remote) ? "Remote" : "Unknown";
    ImGui::Text("Connection: %s (%s)", connected ? "Connected" : "Not connected", routeText);
    ImGui::SameLine();
    ImGui::Text("| Stream: %s", streaming ? "Running" : "Stopped");
    std::string hosttext = (lastHost == ConnectionType::Local) ? LOCAL_PI_IP :
                           (lastHost == ConnectionType::Remote) ? VM_PUBLIC_IP : "None";
    if (lastHost != ConnectionType::None) { ImGui::SameLine(); ImGui::Text("| Target: %s", hosttext.c_str()); }

    // --- Rendering (only when visible) ---
    if (showContents) {
        ImVec2 contentSize = ImGui::GetContentRegionAvail();
        const float aspect = 640.0f / 480.0f;
        float w = contentSize.x, h = w / aspect;
        if (h > contentSize.y) { h = contentSize.y; w = h * aspect; }
        float offsetX = (contentSize.x - w) * 0.5f;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);

        if (streaming) {
            Frame frame = frameProcessor.getFrame();
            if (frame.ready) {
                glBindTexture(GL_TEXTURE_2D, texture);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                if (frame.width != prevWidth || frame.height != prevHeight) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.width, frame.height,
                                 0, GL_RGB, GL_UNSIGNED_BYTE, frame.pixels.data());
                    prevWidth = frame.width; prevHeight = frame.height;
                } else {
                    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frame.width, frame.height,
                                    GL_RGB, GL_UNSIGNED_BYTE, frame.pixels.data());
                }
                glBindTexture(GL_TEXTURE_2D, 0);
                ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(w, h));
            } else {
                ImGui::TextColored(ImVec4(1,0,0,1), "Waiting for frames...");
            }
        } else {
            if (!connected && userEnabled)
                ImGui::TextWrapped("Not connected. The stream will start automatically when the vehicle connects.");
            else
                ImGui::TextWrapped("Stream is stopped. Enable it above to start.");
        }
    }

    ImGui::End();
}

bool CameraFeedPanel::canToggle() const {
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now() - lastToggle).count() > 500;
}

void CameraFeedPanel::startStream() {
    if (streaming || !canToggle()) return;
    videoStream.start();
    streaming = true;
    lastToggle = std::chrono::steady_clock::now();
}

void CameraFeedPanel::stopStream() {
    if (!streaming || !canToggle()) return;
    videoStream.stop();
    streaming = false;
    lastToggle = std::chrono::steady_clock::now();
}
