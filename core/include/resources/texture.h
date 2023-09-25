#include "resource.h"

#include <raylib-cpp.hpp>

namespace HeartEngine
{
class Texture : public Resource
{
public:
    Texture(std::string name, std::string p_path) : Resource(name), path(p_path) {}

    std::string path;
    Texture2D texture;

    void _load() override
    {
        texture = engine->fileManager.loadImage(path).LoadTexture();
    }

    void _unload() override
    {
        UnloadTexture(texture);
    }
};
}