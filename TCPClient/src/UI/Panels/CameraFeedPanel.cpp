#include "CameraFeedPanel.h"

#include <glad/glad.h>
#include <iostream>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

CameraFeedPanel::CameraFeedPanel(UIContext& uiContext, FrameProcessor& fp)
    : UIPanel(uiContext), frameProcessor(fp)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
}

CameraFeedPanel::~CameraFeedPanel()
{
    glDeleteTextures(1, &texture);
}

void CameraFeedPanel::onUpdate()
{
    ImGui::Begin("Camera Feed");

    // Get available space in the content region
    ImVec2 contentSize = ImGui::GetContentRegionAvail();

    // Original frame size
    const float frameWidth = 640.0f;
    const float frameHeight = 480.0f;
    const float aspectRatio = frameWidth / frameHeight;

    // Calculate scaled size maintaining aspect ratio
    float drawWidth = contentSize.x;
    float drawHeight = drawWidth / aspectRatio;

    if (drawHeight > contentSize.y) {
        drawHeight = contentSize.y;
        drawWidth = drawHeight * aspectRatio;
    }

    // Center the image horizontally
    ImVec2 cursorPos = ImGui::GetCursorPos();
    float offsetX = (contentSize.x - drawWidth) * 0.5f;
    ImGui::SetCursorPos(ImVec2(cursorPos.x + offsetX, cursorPos.y));

    Frame frame = frameProcessor.getFrame();
    if (frame.ready) {
        glBindTexture(GL_TEXTURE_2D, texture);
        if (frame.width != prevWidth || frame.height != prevHeight) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.width, frame.height, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.pixels.data());
            prevWidth = frame.width;
            prevHeight = frame.height;
        } else {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frame.width, frame.height, GL_RGB, GL_UNSIGNED_BYTE, frame.pixels.data());
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(drawWidth, drawHeight));
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Undergoing test");
    } else {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Camera feed unavailable");
        ImGui::TextWrapped("Please ensure the vehicle is powered on and the camera is connected.");
    }
    ImGui::Text("Skipping frame logic completely");

    ImGui::End();
}
