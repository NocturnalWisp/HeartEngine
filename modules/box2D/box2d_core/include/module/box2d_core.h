#pragma once

#include "heart/module.h"

class b2World;
class b2Vec2;

namespace HeartBox2D { class Box2D; }

namespace HeartBox2D
{
class Box2DCore : public HeartEngine::Module
{
public:
    void registerTypes(HeartEngine::Engine& engine, sol::state& lua) override;

    void initialize(HeartEngine::Engine& engine) override;

    void beforeFixedUpdate(HeartEngine::Engine& engine) override;
private:
    Box2D* box2d;
};
}