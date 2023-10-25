#pragma once

#include <sol/sol.hpp>

#include <raylib-cpp.hpp>

#include "heart/module.h"

#include "heart/file_manager.h"

namespace HeartEngine { class Engine; }

namespace HeartRayLib
{
class RayLibTextures : public HeartEngine::Module
{
public:
    RayLibTextures(bool includeSetting = true)
        : includeSetting(includeSetting) {}

    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override
    {
        if (includeSetting)
            Setup(engine, lua);
    }

    void Setup(HeartEngine::Engine& engine, sol::state& lua);

    static raylib::Image loadImage(HeartEngine::Engine& engine, std::string_view path);
private:
    bool includeSetting;
};
}