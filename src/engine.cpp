#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <tuple>

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

class Engine;
class Node;

typedef std::shared_ptr<Node> shared_node_ptr;
typedef std::weak_ptr<Node> node_ptr;

class Node
{
public:
    node_ptr self;

    node_ptr root;

    node_ptr parent;
    std::vector<shared_node_ptr> children;

    std::string name;

    Node(const char* p_name) : name(p_name) {}

    virtual void _ready() {}
    virtual void _update() {}
    virtual void _draw() {}

    Node& getNode(const char* path)
    {
        std::vector<std::string> tokens = std::vector<std::string>();

        std::string current {""};

        const char* c = &path[0];
        while (*c != '\0')
        {
            bool nextIsEnd = *(c+1) == '\0';
            if (*c == '/' || nextIsEnd)
            {
                if (nextIsEnd)
                    current.push_back(*c);
                if (current != "")
                {
                    tokens.push_back(current);
                    current = {""};
                }
            }
            else
            {
                current.push_back(*c);
            }

            ++c;
        }

        node_ptr currentNode;
        // Determine starting node.
        if (tokens[0] == "root")
        {
            currentNode = root;
            tokens.erase(tokens.begin());
        }
        else
        {
            currentNode = shared_node_ptr(this);
        }

        // Follow token path.
        for (std::string& token : tokens)
        {
            currentNode = getNodeByToken(currentNode, token);

            if (currentNode.expired())
            {
                // Break early and the function will return the expired pointer.
                std::cerr << "Invalid token in getNode, fix path. (" + token + ")";
                break;
            }
        }

        return *currentNode.lock();
    }

    void addChild(node_ptr child)
    {
        if (auto child_ptr = child.lock())
        {
            // Remove this child from current parent.
            child_ptr->removeParent();

            // Add as child to this.
            children.push_back(child_ptr);

            // Set parent to new parent.
            child_ptr->parent = self;
        }
        else
        {
            std::cerr << "Couldn't add invalid child." << std::endl;
        }
    }
private:
    node_ptr getNodeByToken(node_ptr currentNode, std::string& token)
    {
        if (auto currentNode_ptr = currentNode.lock())
        {
            if (token == "..")
            {
                return currentNode_ptr->parent;
            }
            else
            {
                // Loop through children to find by name.
                for (auto child : currentNode_ptr->children)
                {
                    if (child->name == token)
                    {
                        return child;
                    }
                }
            }
        }

        return node_ptr();
    }

    void removeParent()
    {
        if (auto parent_ptr = parent.lock())
        {
            auto captureName = name;
            auto at = std::remove_if(parent_ptr->children.begin(),
                                            parent_ptr->children.end(),
                                            [captureName](shared_node_ptr& node) {
                                                return node->name == captureName;
                                            });

            parent_ptr->children.erase(at);
        }
    }
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
        recursiveRun(root, [](shared_node_ptr node){ node->_ready(); });

        while (!WindowShouldClose())
        {
            // Update
            recursiveRun(root, [](shared_node_ptr node){ node->_update(); });

            BeginDrawing();

            ClearBackground(RAYWHITE);

            recursiveRun(root, [](shared_node_ptr node){ node->_draw(); });

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
            childPtr->_ready();
        }

        return *this;
    }

    template <typename T, class... Args>
    static void print(T t, Args... args)
    {
        std::cout << t << std::endl;
    }

    template <typename T, class... Args>
    static void printerr(T t, Args... args)
    {
        std::cerr << t << std::endl;
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
    EngineTextureRect(const char* name, std::weak_ptr<EngineTexture> p_texture) : Node(name), texture(p_texture) {}
    EngineTextureRect(const char* name) : Node(name) {}

    std::weak_ptr<EngineTexture> texture;

    void _ready() override
    {
        if (auto texture = this->texture.lock())
        {
            position = {
                SCREEN_WIDTH / 2.0f - texture->texture.width / 2.0f,
                SCREEN_HEIGHT / 2.0f - texture->texture.height / 2.0f,
                0.0
            };
        }
    }

    void _draw() override
    {
        if (auto texture = this->texture.lock())
        {
            DrawTexturePro(texture->texture,
            {0, 0, texture->texture.width * 1.0f, texture->texture.height * 1.0f},
            {position.x, position.y, texture->texture.width * scale.x, texture->texture.height * scale.y},
            {0, 0},
            QuaternionToEuler(rotation).z,
            modulate);
        }
    }
};