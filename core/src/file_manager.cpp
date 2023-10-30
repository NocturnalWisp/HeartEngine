#include "file_manager.h"

#include <string.h>
#include <tuple>
#include <filesystem>

namespace HeartEngine
{
FileManager::FileManager()
{
    packageFile = std::ifstream(std::filesystem::current_path().append("data.heart"),  std::ios::binary);

    if (packageFile)
    {
        packageFile.seekg(0);
        std::uint16_t fileCount;
        if (packageFile.read(reinterpret_cast<char*>(&fileCount), 2))
        {
            for (int i = 0; i < fileCount; i++)
            {
                std::uint8_t pathSize;
                packageFile.read(reinterpret_cast<char*>(&pathSize), 1);

                std::string pathName;
                pathName.resize(pathSize);
                packageFile.read(&pathName[0], pathSize);

                std::uint32_t fileByteCount;
                packageFile.read(reinterpret_cast<char*>(&fileByteCount), 4);

                resourcePaths[pathName] = fileByteCount;
            }
            fileDataStart = packageFile.tellg();
        }
    }
    else
    {
#ifndef EDITOR
        throw HeartException({"Failed to find resource file data.heart at: ", std::filesystem::current_path().append("data.heart").u8string()});
#endif
    }
}

FileManager::~FileManager()
{
    if (packageFile)
        packageFile.close();
}

void FileManager::loadScript(std::string_view path, sol::state& lua, sol::environment* env)
{
#ifdef EDITOR
    if (env != nullptr)
        lua.script_file("assets/" + std::string(path), *env);
    else
        lua.script_file("assets/" + std::string(path));
#else
    if (env != nullptr)
        lua.script(getString(path), *env, sol::detail::default_chunk_name(), sol::load_mode::binary);
    else
        lua.script(getString(path), sol::detail::default_chunk_name(), sol::load_mode::binary);
#endif
}

std::vector<std::byte> FileManager::getBytes(std::string_view path)
{
    auto size = findResource(path);

    std::vector<std::byte> bytes;
    packageFile.read(reinterpret_cast<char*>(&bytes), size);

    return bytes;
}

std::string FileManager::getString(std::string_view path)
{
    auto size = findResource(path);
    std::string string;

    string.resize(size);
    packageFile.read(&string[0], size);

    return string;
}

std::tuple<std::vector<unsigned char>, std::uint32_t> FileManager::getCharData(std::string_view path)
{
    auto size = findResource(path);

    std::vector<unsigned char> data(size);
    packageFile.read(reinterpret_cast<char*>(data.data()), size);

    return std::make_tuple(data, size);
}

void FileManager::seekPath(std::string_view path)
{
    packageFile.seekg(fileDataStart);

    for (const auto& resourcePathPair : resourcePaths)
    {
        if (resourcePathPair.first.compare(path) == 0)
        {
            // Found path at g, now break out.
            return;
        }
        else
        {
            packageFile.seekg(packageFile.tellg() + std::int64_t(resourcePathPair.second));
        }
    }
}

std::uint32_t FileManager::findResource(std::string_view path)
{
    if (packageFile)
    {
        seekPath(path);

        if (auto search = resourcePaths.find(path); search != resourcePaths.end())
        {
            return search->second;
        }
        else
        {
            throw HeartException({"Invalid file path: ", path});
        }
    }

    throw HeartException("Unable to open binary data to access any resources.");
}
}