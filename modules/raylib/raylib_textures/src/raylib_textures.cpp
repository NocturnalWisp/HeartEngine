#include "module/raylib_textures.h"

#include "heart/engine.h"

using namespace HeartEngine;

namespace HeartRayLib
{
void RayLibTextures::Setup(HeartEngine::Engine& engine, sol::state& lua)
{
    
}

raylib::Image RayLibTextures::loadImage(HeartEngine::Engine& engine, std::string_view path)
{
#ifdef EDITOR
    return raylib::LoadImage("assets/" + std::string(path));
#else
    auto imageData = engine.fileManager.getCharData(path);

    size_t dotPos = path.find_last_of('.');
    if (dotPos == std::string::npos || dotPos >= path.length() - 1)
        throw HeartEngine::HeartException({"Path does not have a proper extension. Please add a valid extension (.png, .jpeg, etc...) for file: ", path});

    auto extension = std::string(path.substr(dotPos+1)).insert(0, ".");

    return raylib::LoadImageFromMemory(extension, std::get<0>(imageData).data(), std::get<1>(imageData));
#endif
}
}