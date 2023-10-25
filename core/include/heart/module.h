#pragma once

#include <string>

#include <sol/sol.hpp>

namespace HeartEngine
{
class Engine;

class Module
{
public:
    virtual void registerTypes(Engine& engine, sol::state& lua) {}

    virtual void duringUpdate(Engine& engine) {}
    virtual void closeApplication(Engine& engine) {}

    virtual void startDraw(Engine& engine) {}
    virtual void endDraw(Engine& engine) {}
};
}