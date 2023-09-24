#pragma once

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <memory>

#include <raylib-cpp.hpp>
#include <sol.hpp>

#include "debug.h"

namespace HeartEngine
{
class FileManager
{
public:
    FileManager();
    ~FileManager();

    void loadScript(std::string_view path, sol::state& lua, sol::environment* env = nullptr);
    raylib::Image loadImage(std::string_view path);

    std::vector<std::byte> getBytes(std::string_view path);
    std::string getString(std::string_view path);
    std::tuple<std::vector<unsigned char>, std::uint32_t> getCharData(std::string_view path);
private:
    // Seekg to the appropriate data location.
    void seekPath(std::string_view path);

    std::uint32_t* findResource(std::string_view path);

    // Path - File Byte Count
    std::map<std::string, std::uint32_t, std::less<>> resourcePaths;

    std::ifstream packageFile;

    std::streamsize fileDataStart;
};
}