#include "module/raylib_textures.h"

#include "heart/file_manager.h"

#include "heart/engine.h"

#include "heart/module.h"

#include "module/components/texture_rect.h"

namespace HeartRayLib
{
void RayLibTextures::registerTypes(HeartEngine::Engine& engine, sol::state& lua)
{
    // Texture Rect.
    auto textureRectType = REGISTER_COMPONENT(TextureRect);

    ADD_LUA_FUNCTION_W_TYPE(textureRectType, TextureRect, texture);
    ADD_LUA_FUNCTION_W_TYPE(textureRectType, TextureRect, rect);
    ADD_LUA_FUNCTION_W_TYPE(textureRectType, TextureRect, rotation);
    ADD_LUA_FUNCTION_W_TYPE(textureRectType, TextureRect, origin);
    ADD_LUA_FUNCTION_W_TYPE(textureRectType, TextureRect, color);

    // Texture resource.
    auto textureType = lua.new_usertype<Texture>("Texture");

    ADD_LUA_FUNCTION_W_TYPE(textureType, Texture, path);
    ADD_LUA_FUNCTION_W_TYPE(textureType, Texture, texture);

    // RayLib Texture2D.
    auto texture2dType = lua.new_usertype<raylib::Texture2D>("Texture2D");
    ADD_LUA_FUNCTION_W_TYPE(texture2dType, raylib::Texture2D, id);
    ADD_LUA_FUNCTION_W_TYPE(texture2dType, raylib::Texture2D, width);
    ADD_LUA_FUNCTION_W_TYPE(texture2dType, raylib::Texture2D, height);
    ADD_LUA_FUNCTION_W_TYPE(texture2dType, raylib::Texture2D, mipmaps);
    ADD_LUA_FUNCTION_W_TYPE(texture2dType, raylib::Texture2D, format);
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