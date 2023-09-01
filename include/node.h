#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include <raylib.h>
#include <raymath.h>

#include "debug.h"

class Engine;
class Node;

typedef std::shared_ptr<Node> shared_node_ptr;
typedef std::weak_ptr<Node> node_ptr;

typedef struct RotationAxisAngle
{
    Vector3 axis;
    float   angle;
} RotationAxisAngle;

class Node
{
    friend class Engine;
public:
    node_ptr self;
    node_ptr root;

    node_ptr parent;
    std::vector<shared_node_ptr> children;

    std::string name;

    Node(const char* p_name) : name(p_name) {Debug::print("Created: ", name);}

    virtual void _ready() {}
    virtual void _update() {}
    virtual void _draw() {}
    virtual void _remove() {}

    node_ptr getNode(const char* path) const;

    void addChild(node_ptr child);

    void destroy();

    // Transform
    Vector3 getLocalPosition() const;
    void setLocalPosition(Vector3 localPosition);
    Vector3 getWorldPosition() const;

    RotationAxisAngle getLocalRotation() const;
    void setLocalRotation(RotationAxisAngle rotation);
    RotationAxisAngle getWorldRotation() const;

    Vector3 getLocalScale() const;
    void setLocalScale(Vector3 localScale);
    Vector3 getWorldScale() const;
protected:
    // Transform
    Vector3 position = {0, 0, 0};
    Quaternion rotation = {0, 0, 0, 1};
    Vector3 scale = {1, 1, 1};
    Vector3 origin = {0, 0, 0};

    Color modulate = WHITE;
private:
    // Engine callbacks
    void(*EarlyResourceReleaseCallback)();

    friend void runReady(const shared_node_ptr& node)
    {
        node->_ready();
    }
    friend void runUpdate(const shared_node_ptr& node)
    {
        node->_update();
    }
    friend void runDraw(const shared_node_ptr& node)
    {
        node->_draw();
    }
    friend void runRemove(const shared_node_ptr& node)
    {
        node->_remove();

        for (auto child : node->children)
        {
            runRemove(child);
        }

        node->children.clear();

        node->removeParent();
    }

    node_ptr getNodeByToken(node_ptr currentNode, std::string& token) const;

    void removeParent();

    // Borrowed liberally from https://github.com/juniper-dusk/raylib-transform
    // Awesome library thank you Juniper!
    class Extensions
    {
    public:
        static Matrix makeLocalToParent(node_ptr node);
        static Matrix makeParentToLocal(node_ptr node);

        static Matrix getLocalToWorldMatrix(node_ptr node);
        static Matrix getWorldToLocalMatrix(node_ptr node);

        static Vector3 extractTranslation(Matrix transform);
        static Matrix  extractRotation(Matrix transform);
        static Vector3 extractScale(Matrix transform);
    };
};