#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <memory>
#include <type_traits>
#include <tuple>

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class Engine;

class Node
{
public:
    Node(const char* p_name) : name(p_name) {}

    virtual void _ready() {}
    virtual void _update() {}
    virtual void _draw() {}

    std::shared_ptr<Node> parent;

    std::string name;
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
private:
    inline static std::unique_ptr<Engine> singleton;
public:
    static Engine& create()
    {
        if (singleton != nullptr)
            return *singleton;

        singleton = std::make_unique<Engine>();

        SetTraceLogLevel(3);
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
        SetTargetFPS(60);

        return *singleton;
    }

    static int run()
    {
        started = true;

        for (auto& node : nodes)
        {
            node->_ready();
        }

        while (!WindowShouldClose())
        {
            // Updating
            for (auto& node : nodes)
            {
                node->_update();
            }

            BeginDrawing();

            ClearBackground(RAYWHITE);

            for (auto& node : nodes)
            {
                node->_draw();
            }

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

        resources.push_back(std::make_shared<T>(resource));

        resources[resources.size()-1]->_load();

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
    Engine& addNode(T node)
    {
        static_assert(std::is_base_of<Node, T>::value, "T must derive from Node.");

        nodes.push_back(std::make_shared<T>(node));

        if (started)
        {
            nodes[nodes.size()-1]->_ready();
        }

        return *this;
    }

    static void ParentNode(Node* child, const char* parentName)
    {
        child->parent = FindNode(parentName);
    }

    static std::shared_ptr<Node> FindNode(const char* name)
    {
        for (auto node : nodes)
        {
            if (strcmp(node->name.c_str(), name) == 0)
            {
                return node;
            }
        }

        return nullptr;
    }

    template <typename T, class... Args>
    static void println(T t, Args... args)
    {
        std::cout << t << std::endl;
    }

    template <typename T, class... Args>
    static void print(T t, Args... args)
    {
        std::cout << t;
    }
private:
    inline static bool started = false;

    inline static std::vector<std::shared_ptr<Resource>> resources;
    inline static std::vector<std::shared_ptr<Node>> nodes;
};

class EngineTransform
{
public:
    Vector3 position;
    Quaternion rotation = QuaternionFromEuler(0, 0, 0.01f);
    Vector3 scale = {1, 1, 1};
};

class ColorModulator
{
public:
    Color modulate = WHITE;
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

class EngineTextureRect : public Node, public EngineTransform, public ColorModulator
{
public:
    EngineTextureRect(const char* name, std::shared_ptr<EngineTexture> p_texture) : Node(name), texture(p_texture) {}
    EngineTextureRect(const char* name) : Node(name) {}

    std::shared_ptr<EngineTexture> texture;

    void _ready() override
    {
        position = {
            SCREEN_WIDTH / 2.0f - texture->texture.width / 2.0f,
            SCREEN_HEIGHT / 2.0f - texture->texture.height / 2.0f,
            0.0
        };
    }

    void _draw() override
    {
        DrawTexturePro(texture->texture,
        {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
        {position.x, position.y, texture->texture.width * scale.x, texture->texture.height * scale.y},
        {0, 0},
        QuaternionToEuler(rotation).z,
        modulate);
    }
};