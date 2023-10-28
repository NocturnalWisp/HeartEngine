#pragma once

#include <string>

#include "heart/utils.h"

namespace sol { class state; }
namespace HeartEngine { class Engine; }

namespace HeartEngine
{
class Module
{
public:
    virtual void registerTypes(Engine& engine, sol::state& lua) {}

    virtual void initialize(Engine& engine) {}

    virtual void duringUpdate(Engine& engine) {}

    virtual void startDraw(Engine& engine) {}
    virtual void endDraw(Engine& engine) {}

    virtual void close(Engine& engine) {}
};
}