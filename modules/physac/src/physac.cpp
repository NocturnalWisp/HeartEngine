#include "module/physac.h"

#include "heart/engine.h"

#include "raylib.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

using namespace HeartEngine;

namespace HeartPhysac
{
void Physac::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    //TODO: Register components/other lua types.
}
}