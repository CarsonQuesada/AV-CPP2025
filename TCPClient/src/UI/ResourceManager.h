#pragma once

#include <string>
#include <filesystem>
#include <Windows.h>

class ResourceManager {
public:
    // Returns full path to resource relative to .exe
    static std::string getPath(const std::string& relativePath) {
        static std::string exeDir = getExecutableDir();
        return exeDir + "/" + relativePath;
    }

private:
    // Retrieves the directory that the executable is in
    static std::string getExecutableDir() {
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::filesystem::path exePath(buffer);
        return exePath.parent_path().string();
    }
};
