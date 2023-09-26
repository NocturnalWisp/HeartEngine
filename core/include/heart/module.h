#pragma once

namespace HeartEngine
{
class Engine;

class Module
{
public:
    Engine* engine;

    virtual void registerTypes() = 0;
};
}