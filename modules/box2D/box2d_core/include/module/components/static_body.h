#pragma once

#include <vector>

#include "box2D/b2_body.h"
#include "box2D/b2_fixture.h"
#include "box2D/b2_shape.h"
#include "box2D/b2_math.h"

#include "heart/engine.h"
#include "heart/node.h"
#include "heart/component.h"

#include "module/utils.h"

#include "module/box2d_global_data.h"

using namespace HeartEngine;

namespace HeartBox2D
{
class StaticBody : public Component
{
    SETUP_COMPONENT()
    EVENT_CALLABLE(fixedUpdate, _on_fixed_update());
public:
    StaticBody(std::string name,
        b2Vec2 pos,
        float rotation,
        std::vector<b2Vec2> vertices)
        : Component(name),
          pos(pos),
          rotation(rotation),
          vertices(vertices){}
    
    StaticBody(std::string name, sol::variadic_args args)
        : Component(name)
    {
        // Pos
        CHECK_ARG_VECTOR2(0, pos);
        // Rotation
        CHECK_ARG_FLOAT(1, rotation);
        // Vertices
        CHECK_ARG_FALSE(2, std::vector<b2Vec2>, vertices = *result);
        CHECK_ARG(2, std::vector<std::vector<float>>, 
        {
            for (auto vec : *result)
            {
                vertices.push_back(HeartBox2D::tableToVector2(vec));
            }
        });
    }

    b2Body* body;

    void _on_create() override
    {
        setfixedUpdateCall(fixedUpdateCall);

        box2d = node->engine->getGlobalDataT<Box2D>("Box2D");

        b2BodyDef groundBodyDef;
        groundBodyDef.position = pos;

        body = box2d->world.CreateBody(&groundBodyDef);

        b2PolygonShape shape;
        shape.Set(vertices.data(), vertices.size());

        body->CreateFixture(&shape, 0.0f);
    }

    void _on_fixed_update()
    {
       
    }
private:
    Box2D* box2d;

    b2Vec2 pos = {0, 1};
    float rotation = 0;
    std::vector<b2Vec2> vertices = {};
};
}