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

    virtual void beforeUpdate(Engine& engine) {}
    virtual void afterUpdate(Engine& engine) {}

    virtual void beforeFixedUpdate(Engine& engine) {}
    virtual void afterFixedUpdate(Engine& engine) {}

    virtual void startDraw(Engine& engine) {}
    virtual void endDraw(Engine& engine) {}

    virtual void close(Engine& engine) {}
};
}