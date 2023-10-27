#include "module/raylib_drawables.h"

#include "heart/utils.h"
#include "heart/engine.h"

#include "module/texture_rect.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void Drawables::SetupTextures(HeartEngine::Engine& engine, sol::state& lua)
{
    REGISTER_COMPONENT(TextureRect);
    //TODO: Setup Texture2D lua type.
}
void Drawables::SetupShapes(HeartEngine::Engine& engine, sol::state& lua)
{

}
void Drawables::SetupLines(HeartEngine::Engine& engine, sol::state& lua)
{

}
void Drawables::SetupCollisionChecking(HeartEngine::Engine& engine, sol::state& lua)
{

}
}