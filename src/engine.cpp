#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <tuple>
#include <functional>

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

class ResourceBase
{
    friend class Engine;
public:
    ResourceBase(const char* p_name) : name(p_name) {} 

    virtual void _load() {}
    virtual void _unload() {}

    std::string name;
private:
    friend void load(const std::shared_ptr<ResourceBase>& res)
    {
        if (res->loaded)
            return;

        res->_load();
        res->loaded = true;
    }

    friend void unload(const std::shared_ptr<ResourceBase>& res)
    {
        if (!res->loaded)
            return;

        res->_unload();
        res->loaded = false;
    }

    bool loaded = false;
};

template <class T>
class Resource : public ResourceBase
{
public:
    Resource(const char* p_name) : ResourceBase(p_name) {}
};

class Engine
{
    friend class Node;
    friend class ResourceBase;
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
        root->root = root;
        root->self = root;

        return *singleton;
    }

    static int run()
    {
        started = true;

        // Ready
        recursiveRun(root, [](const shared_node_ptr& node){ runReady(node); });

        if (checkResourceRelease)
            checkEarlyResourceRelease();

        while (!WindowShouldClose())
        {
            // Update
            recursiveRun(root, [](const shared_node_ptr& node){ runUpdate(node); });

            BeginDrawing();

            ClearBackground(RAYWHITE);

            recursiveRun(root, [](const shared_node_ptr& node){ runDraw(node); });

            EndDrawing();

            if (checkResourceRelease)
                checkEarlyResourceRelease();
        }

        for (auto& res : resources)
        {
            unload(res);
        }

        CloseWindow();

        return 0;
    }

    static node_ptr getRoot()
    {
        return root;
    }

    template <typename T>
    Engine& loadResource(T resource)
    {
        static_assert(std::is_base_of<ResourceBase, T>::value, "T must derive from Resource.");

        auto res = std::make_shared<T>(resource);

        resources.push_back(res);

        load(res);

        return *this;
    }

    template <typename T>
    static std::shared_ptr<T> getResource(const char* name)
    {
        static_assert(std::is_base_of<ResourceBase, T>::value, "T must derive from Resource.");

        std::shared_ptr<T> found = nullptr;

        for (auto res : resources)
        {
            if (strcmp(res->name.c_str(), name) == 0)
            {
                found = std::dynamic_pointer_cast<T>(res);

                if (!found->loaded)
                {
                    load(found);
                }

                break;
            }
        }

        return found;
    }

    template <typename T>
    Engine& addNode(T node, node_ptr parent = root)
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        if (auto parent_ptr = parent.lock())
        {
            parent_ptr->addChild(std::make_shared<T>(node));

            auto& childPtr = parent_ptr->children.back();

            childPtr->root = root;
            childPtr->self = childPtr;

            childPtr->EarlyResourceReleaseCallback = checkEarlyResourceRelease;

            if (started)
            {
                runReady(childPtr);
            }
        }

        return *this;
    }

    // Always relative to root!
    template <typename T>
    Engine& addNode(T node, const char* path)
    {
        addNode(node, root->getNode(path));

        return *this;
    }

    Engine& inlineDoSomething(void(*something)())
    {
        something();

        return *this;
    }
private:
    inline static bool started = false;
    inline static bool checkResourceRelease = false;

    inline static std::vector<std::shared_ptr<ResourceBase>> resources;
    inline static std::shared_ptr<Node> root;

    static void recursiveRun(const shared_node_ptr& node, void (function)(const shared_node_ptr&))
    {
        std::invoke(function, node);
        for (auto i = node->children.rbegin(); i != node->children.rend(); ++i)
        {
            if ((*i) != nullptr)
            {
                recursiveRun((*i), function);
            }
        }
    }

    static void checkEarlyResourceRelease()
    {
        for (auto it = resources.begin(); it != resources.end();)
        {
            if ((*it)->loaded && it->use_count() <= 1)
            {
                unload(*it);
            }
            else
            {
                ++it;
            }
        }
    }
};

class EngineTexture : public Resource<Texture2D>
{
public:
    EngineTexture(const char* name, const char* p_path) : Resource(name), path(p_path) {}

    const char* path;
    Texture2D texture;

    void _load() override
    {
        texture = LoadTexture(path);

        Debug::print("Loaded!");
    }

    void _unload() override
    {
        UnloadTexture(texture);

        Debug::print("Unloaded!");
    }
};

class EngineTextureRect : public Node, public ColorModulator
{
public:
    EngineTextureRect(const char* name, const char* p_texture)
        : Node(name), textureName(p_texture)
    {

    }
    EngineTextureRect(const char* name) : Node(name) {}

    const char* textureName;
    std::shared_ptr<EngineTexture> texture;

    void _ready() override
    {
        texture = Engine::getResource<EngineTexture>(textureName);
    }

    void _draw() override
    {
        auto position = getWorldPosition();

        DrawTexturePro(texture->texture,
        {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
        {position.x, position.y, texture->texture.width * scale.x, texture->texture.height * scale.y},
        {0, 0},
        QuaternionToEuler(rotation).z,
        modulate);
    }

    void _remove() override
    {
        texture.reset();
    }
};