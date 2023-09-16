#include "resource.h"

#include <raylib.h>

class EngineTexture : public Resource
{
public:
    EngineTexture(std::string name, std::string p_path) : Resource(name), path(p_path) {}

    std::string path;
    Texture2D texture;

    void _load() override
    {
        texture = LoadTexture(path.c_str());
    }

    void _unload() override
    {
        UnloadTexture(texture);
    }
};