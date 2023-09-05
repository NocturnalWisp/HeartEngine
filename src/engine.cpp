#include "../include/engine.h"

Engine& Engine::create()
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

int Engine::run()
{
    started = true;

    // Ready
    recursiveRun(root, [](const shared_node_ptr& node){ ready(node); });

    if (checkResourceRelease)
        checkEarlyResourceRelease();

    while (!WindowShouldClose())
    {
        // Update
        recursiveRun(root, [](const shared_node_ptr& node){ update(node); });

        BeginDrawing();

        ClearBackground(RAYWHITE);

        recursiveRun(root, [](const shared_node_ptr& node){ draw(node); });

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

node_ptr Engine::getRoot()
{
    return root;
}

Engine& Engine::inlineDoSomething(void(*something)())
{
    something();

    return *this;
}

void Engine::recursiveRun(const shared_node_ptr& node, void (function)(const shared_node_ptr&))
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

void Engine::checkEarlyResourceRelease()
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

