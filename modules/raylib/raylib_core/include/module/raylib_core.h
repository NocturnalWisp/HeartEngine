#pragma once

#include "heart/module.h"

namespace HeartRayLib
{
constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class RayLibCore : public HeartEngine::Module
{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;

    void initialize(HeartEngine::Engine& engine) override;
    void close(HeartEngine::Engine& engine) override;

    void startDraw(HeartEngine::Engine& engine) override;
    void endDraw(HeartEngine::Engine& engine);
};
}