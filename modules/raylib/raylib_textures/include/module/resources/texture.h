#pragma once

#include <raylib-cpp.hpp>

#include "heart/resource.h"

#include "module/raylib_textures.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Texture : public Resource
{
public:
    Texture(std::string name, std::string p_path) : Resource(name), path(p_path) {}

    std::string path;
    Texture2D texture;

    void _load() override
    {
        texture = RayLibTextures::loadImage(*engine, path).LoadTexture();
    }

    void _unload() override
    {
        UnloadTexture(texture);
    }
};
}