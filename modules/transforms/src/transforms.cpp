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
    auto transform2DType = lua.new_usertype<void>("Transform2D");

}
void Transforms::SetupTransform3D(Engine& engine, sol::state& lua)
{
    engine.registerComponent("Transform3D", &Engine::componentBuilder<Transform3D>);
    Debug::print("sehiofhsadf");

    auto transform3DType = lua.new_usertype<Transform3D>("Transform3D");

    transform3DType["getLocalPosition"] = &Transform3D::GetLocalPosition;
    transform3DType["setLocalPosition"] = &Transform3D::SetLocalPosition;
}
}