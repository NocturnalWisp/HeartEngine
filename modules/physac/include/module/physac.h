#pragma once

#include "heart/module.h"

namespace HeartPhysac
{
class Physac : public HeartEngine::Module
{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;
};
}