#include "module/transforms.h"

#include "module/transform_3d.h"

#include "heart/engine.h"

#include "heart/debug.h"

using namespace HeartEngine;

namespace HeartModules
{
void Transforms::SetupTransform2D(Engine& engine, sol::state& lua)
{
    //TODO: Implement transform2d.

}
void Transforms::SetupTransform3D(Engine& engine, sol::state& lua)
{
    engine.registerComponent("Transform3D", &Engine::componentBuilder<Transform3D>);

    auto rotationAxisType = lua.new_usertype<RotationAxisAngle>("RotationAxisAngle");

    rotationAxisType[sol::call_constructor] =
        [](float x, float y, float z, float angle) -> RotationAxisAngle { return {{x, y, z}, angle}; };
    ADD_LUA_FUNCTION_W_TYPE(rotationAxisType, RotationAxisAngle, axis);
    ADD_LUA_FUNCTION_W_TYPE(rotationAxisType, RotationAxisAngle, angle);

    rotationAxisType[sol::meta_function::to_string] =
        [](RotationAxisAngle& self) -> std::string
        { return std::string("((" + std::to_string(self.axis.x) + ", " + std::to_string(self.axis.y) + ", " + std::to_string(self.axis.z) + "), " + std::to_string(self.angle) + ")" ); };

}
}