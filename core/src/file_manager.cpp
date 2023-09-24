#include "file_manager.h"

#include <string.h>

namespace HeartEngine
{
FileManager::FileManager()
{
    packageFile = std::ifstream("data.heart", std::ios::binary);

    if (packageFile)
    {
        packageFile.seekg(0);
        std::uint16_t fileCount;
        if (packageFile.read(reinterpret_cast<char*>(&fileCount), 2))
        {
            Debug::print(fileCount);
            for (int i = 0; i < fileCount; i++)
            {
                std::uint8_t pathSize;
                packageFile.read(reinterpret_cast<char*>(&pathSize), 1);

                std::string pathName;
                pathName.resize(pathSize);
                packageFile.read(&pathName[0], pathSize);
                Debug::print(pathName);

                std::uint32_t fileByteCount;
                packageFile.read(reinterpret_cast<char*>(&fileByteCount), 4);

                resourcePaths[pathName] = fileByteCount;
            }
            fileDataStart = packageFile.tellg();
            Debug::print("File data start is: ", fileDataStart);
        }
    }
}

FileManager::~FileManager()
{
    if (packageFile)
        packageFile.close();
}

std::vector<std::byte> FileManager::getBytes(std::string_view path)
{
    std::vector<std::byte> bytes;
    if (auto size = findResource(path))
    {
        packageFile.read(reinterpret_cast<char*>(&bytes), *size);
    }

    return bytes;
}

std::string FileManager::getString(std::string_view path)
{
    std::string string;

    if (auto size = findResource(path))
    {
        string.resize(*size);
        packageFile.read(&string[0], *size);
    }

    return string;
}

unsigned char* FileManager::getCharData(std::string_view path)
{
    std::string string;

    if (auto size = findResource(path))
    {
        string.resize(*size);
        packageFile.read(&string[0], *size);
    }

    auto result = (unsigned char*)string.c_str();
    Debug::print("Test: ", sizeof(result));
    return result;
}

void FileManager::seekPath(std::string_view path)
{
    packageFile.seekg(fileDataStart);

    for (const auto& resourcePathPair : resourcePaths)
    {
        if (resourcePathPair.first.compare(path) == 0)
        {
            // Found path, now break out.
            return;
        }
        else
        {
            packageFile.seekg(packageFile.tellg() + std::int64_t(resourcePathPair.second));
        }
    }
}

std::uint32_t* FileManager::findResource(std::string_view path)
{
    if (packageFile)
    {
        seekPath(path);

        if (auto search = resourcePaths.find(path); search != resourcePaths.end())
        {
            return &search->second;
        }
    }

    return nullptr;
}
}