#pragma once

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdint>

#include "debug.h"

namespace HeartEngine
{
class FileManager
{
public:
    FileManager();
    ~FileManager();

    std::vector<std::byte> getBytes(std::string_view path);
    std::string getString(std::string_view path);
    unsigned char* getCharData(std::string_view path);
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