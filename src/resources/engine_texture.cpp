#include "../include/resource.h"

class EngineTexture : public Resource
{
public:
    EngineTexture(const char* name, const char* p_path) : Resource(name), path(p_path) {}

    const char* path;
    Texture2D texture;

    void _load() override
    {
        texture = LoadTexture(path);
    }

    void _unload() override
    {
        UnloadTexture(texture);
    }
};