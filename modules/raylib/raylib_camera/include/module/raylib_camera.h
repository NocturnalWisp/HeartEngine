#pragma once

#include "heart/module.h"

namespace HeartRayLib
{
class RayLibCamera : public HeartEngine::Module
{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;
};
}