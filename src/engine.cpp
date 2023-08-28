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
class Resource;

typedef std::shared_ptr<Resource> shared_resource_ptr;
typedef std::weak_ptr<Resource> resource_ptr;

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
        root->root = root;
        root->self = root;

        return *singleton;
    }

    static int run()
    {
        started = true;

        // Ready
        recursiveRun(root, [](shared_node_ptr node){ runReady(node); });

        if (checkResourceRelease)
            handleCheckResourceRelease();

        while (!WindowShouldClose())
        {
            // Update
            recursiveRun(root, [](shared_node_ptr node){ runUpdate(node); });

            BeginDrawing();

            ClearBackground(RAYWHITE);

            recursiveRun(root, [](shared_node_ptr node){ runDraw(node); });

            EndDrawing();

            if (checkResourceRelease)
                handleCheckResourceRelease();
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

        resources.push_back(std::make_shared<T>(resource));

        resources[resources.size()-1]->_load();

        return *this;
    }

    template <typename T>
    static std::weak_ptr<T> getResource(const char* name)
    {
        for (auto res : resources)
        {
            if (strcmp(res->name.c_str(), name) == 0)
            {
                return std::dynamic_pointer_cast<T>(res);
            }
        }

        return std::weak_ptr<T>();
    }

    template <typename T>
    static std::shared_ptr<T> getResourceShared(const char* name)
    {
        for (auto res : resources)
        {
            if (strcmp(res->name.c_str(), name) == 0)
            {
                return std::dynamic_pointer_cast<T>(res);
            }
        }

        return nullptr;
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
private:
    inline static bool started = false;
    inline static bool checkResourceRelease = false;

    inline static std::vector<std::shared_ptr<Resource>> resources;
    inline static std::shared_ptr<Node> root;

    static void recursiveRun(shared_node_ptr node, void (*function)(shared_node_ptr))
    {
        function(node);
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
        checkResourceRelease = true;
    }

    static void handleCheckResourceRelease()
    {
        for (auto it = resources.begin(); it != resources.end();)
        {
            Debug::print("Use: ", (*it).use_count());
            if ((*it).use_count() <= 1)
            {
                (*it)->_unload();
                *it = nullptr;
                it = resources.erase(it);
            }
            else
            {
                ++it;
            }
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
    EngineTextureRect(const char* name, const char* p_texture)
        : Node(name)
    {
        texture = Engine::getResourceShared<EngineTexture>(p_texture);
    }
    EngineTextureRect(const char* name) : Node(name) {}

    std::shared_ptr<EngineTexture> texture;

    void _ready() override
    {
        setLocalPosition({
            (SCREEN_WIDTH / 2.0f - texture->texture.width / 2.0f) / 2,
            (SCREEN_HEIGHT / 2.0f - texture->texture.height / 2.0f) / 2,
            0.0
        });
    }

    void _draw() override
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

    void _remove() override
    {
        Debug::print(texture.use_count());
        texture = nullptr;
    }
};