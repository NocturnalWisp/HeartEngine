#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <tuple>

#include <raylib.h>
#include <raymath.h>

#include "../include/debug.h"
#include "../include/node.h"

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class Engine;
class Node;

struct ColorModulator
{
public:
    Color modulate = WHITE;
};

class Resource
{
public:
    Resource(const char* p_name) : name(p_name) {} 

    virtual void _load() {}
    virtual void _unload() {}

    std::string name;
};

class Engine
{
    friend class Node;
private:
    inline static std::unique_ptr<Engine> singleton;
public:
    static Engine& create()
    {
        if (singleton != nullptr)
            return *singleton;

        singleton = std::make_unique<Engine>();

        SetTraceLogLevel(4);
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);

        root = std::make_shared<Node>("root");

        return *singleton;
    }

    static int run()
    {
        started = true;

        // Ready
        recursiveRun(root, [](shared_node_ptr node){ runReady(node); });

        while (!WindowShouldClose())
        {
            // Update
            recursiveRun(root, [](shared_node_ptr node){ runUpdate(node); });

            BeginDrawing();

            ClearBackground(RAYWHITE);

            recursiveRun(root, [](shared_node_ptr node){ runDraw(node); });

            EndDrawing();
        }

        for (auto& res : resources)
        {
            res->_unload();
        }

        CloseWindow();

        return 0;
    }

    template <typename T>
    Engine& loadResource(T resource)
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        LoadResource(std::make_shared<T>());

        return *this;
    }

    template <typename T>
    Engine& loadResource(std::shared_ptr<T> resource)
    {
        static_assert(std::is_base_of<Resource, T>::value, "T must derive from Resource.");

        resources.push_back(resource);

        resources[resources.size()-1]->_load();

        return *this;
    }

    template <typename T>
    Engine& addNodeRoot(T node)
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        root->addChild(std::make_shared<T>(node));

        auto& childPtr = root->children.back();

        childPtr->root = root;
        childPtr->self = childPtr;

        if (started)
        {
            runReady(childPtr);
        }

        return *this;
    }
private:
    inline static bool started = false;

    inline static std::vector<std::shared_ptr<Resource>> resources;
    inline static std::shared_ptr<Node> root;

    static void recursiveRun(shared_node_ptr node, void (*function)(shared_node_ptr))
    {
        function(node);
        for (auto child : node->children)
        {
            recursiveRun(child, function);
        }
    }
};

class EngineTexture : public Resource
{
public:
    EngineTexture(const char* name, const char* p_path) : Resource(name), path(p_path) {}

    const char* path;
    Texture2D texture;

    void _load() override
    {
        texture = LoadTexture(path);
    }

    void _unload() override
    {
        UnloadTexture(texture);
    }
};

class EngineTextureRect : public Node, public ColorModulator
{
public:
    EngineTextureRect(const char* name, std::weak_ptr<EngineTexture> p_texture) : Node(name), texture(p_texture) {}
    EngineTextureRect(const char* name) : Node(name) {}

    std::weak_ptr<EngineTexture> texture;

    void _ready() override
    {
        if (auto texture = this->texture.lock())
        {
            setLocalPosition({
                (SCREEN_WIDTH / 2.0f - texture->texture.width / 2.0f) / 2,
                (SCREEN_HEIGHT / 2.0f - texture->texture.height / 2.0f) / 2,
                0.0
            });
        }
    }

    void _draw() override
    {
        if (auto texture = this->texture.lock())
        {
            // Debug::print(position.x);
            auto position = getWorldPosition();
            DrawTexturePro(texture->texture,
            {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
            {position.x, position.y, texture->texture.width * scale.x, texture->texture.height * scale.y},
            {0, 0},
            QuaternionToEuler(rotation).z,
            modulate);
        }
    }
};