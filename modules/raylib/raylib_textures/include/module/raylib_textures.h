#pragma once

#include "heart/module.h"

namespace raylib { class Image; }

namespace HeartRayLib
{
class RayLibTextures : public HeartEngine::Module
{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;

    static raylib::Image loadImage(HeartEngine::Engine& engine, std::string_view path);
};
}