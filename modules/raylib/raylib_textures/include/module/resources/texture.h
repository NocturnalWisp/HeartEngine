#pragma once

#include <sol/sol.hpp>
#include <raylib-cpp.hpp>

#include "heart/resource.h"

#include "heart/utils.h"

#include "module/raylib_textures.h"

using namespace HeartEngine;

namespace HeartRayLib
{
class Texture : public Resource
{
    SETUP_RESOURCE()
public:
    Texture(std::string name, std::string p_path) : Resource(name), path(p_path) {}

    Texture(std::string name, sol::variadic_args args)
        : Resource(name)
    {
        CHECK_ARG_STRING(0, path);
    }

    std::string path;
    Texture2D texture;

    void _on_load() override
    {
        texture = RayLibTextures::loadImage(*engine, path).LoadTexture();
    }

    void _on_unload() override
    {
        UnloadTexture(texture);
    }
};
}