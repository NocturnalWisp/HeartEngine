#include "module/drawables.h"

#include "heart/engine.h"

#include "module/texture_rect.h"

using namespace HeartEngine;

namespace HeartModules
{
void Drawables::Setup(HeartEngine::Engine& engine, sol::state& lua)
{
    engine.registerComponent("TextureRect", &Engine::componentBuilder<TextureRect>);
}
}