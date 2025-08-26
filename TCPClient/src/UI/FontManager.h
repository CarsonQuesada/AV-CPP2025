#pragma once

#include <iostream>
#include <string>

#include "imgui.h"
#include "ResourceManager.h"

struct Font
{
    ImFont* font;
    float size;
};

class FontManager
{
public:
    static inline FontManager& GetInstance() {
        static FontManager instance;
        return instance;
    }

    // Load fonts and store references
    void LoadFonts()
    {
        ImGuiIO& io = ImGui::GetIO();

        // Define font paths
        std::string fontPath;
        fontPath = ResourceManager::getPath("assets/fonts/Inter-Bold.ttf");
        boldFont.font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);
        if (!boldFont.font) {
            std::cerr << "Failed to load bold font: " << fontPath << std::endl;
        }
        boldFont.size = 16.0f;
        boldFontLarge.font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 20.0f);
        if (!boldFontLarge.font) {
            std::cerr << "Failed to load bold font large: " << fontPath << std::endl;
        }
        boldFontLarge.size = 20.0f;

        fontPath = ResourceManager::getPath("assets/fonts/Inter-Thin.ttf");
        lightFont.font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);
        if (!lightFont.font) {
            std::cerr << "Failed to load light font: " << fontPath << std::endl;
        }
        lightFont.size = 16.0f;

        fontPath = ResourceManager::getPath("assets/fonts/Inter-Medium.ttf");
        regularFont.font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);
        if (!regularFont.font) {
            std::cerr << "Failed to load regular font: " << fontPath << std::endl;
        }
        regularFont.size = 16.0f;
        regularFontLarge.font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 20.0f);
        if (!regularFontLarge.font) {
            std::cerr << "Failed to load regular font large: " << fontPath << std::endl;
        }
        regularFontLarge.size = 20.0f;

        // Build the fonts
        io.Fonts->Build();
    }

    // Getters for fonts
    inline Font GetRegularFont() { return regularFont; }
    inline Font GetRegularFontLarge() { return regularFontLarge; }
    inline Font GetBoldFont() { return boldFont; }
    inline Font GetBoldFontLarge() {return boldFontLarge; }
    inline Font GetLightFont() { return lightFont; }

private:
    FontManager() = default; // private constructor
    Font regularFont;
    Font regularFontLarge;
    Font boldFont;
    Font boldFontLarge;
    Font lightFont;
};
