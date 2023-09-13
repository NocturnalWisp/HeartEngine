#include "engine.h"

Engine::Engine()
{
    SetTraceLogLevel(4);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);

    return ;
}

int Engine::run()
{
    started = true;

    // Creation
    for (auto& node : nodes)
    {
        onCreate(*node.get());
    }

    if (checkResourceRelease)
        checkEarlyResourceRelease();

    while (!WindowShouldClose())
    {
        // Update
        //TODO: recursiveRun(root, [](const shared_node_ptr& node){ update(node); });
        updateEvent();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawEvent();
        //TODO: recursiveRun(root, [](const shared_node_ptr& node){ draw(node); });

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

Node* Engine::getNode(std::string_view name)
{
    Node* foundNode;

    for (const auto& node : nodes)
    {
        if (node->name.compare(name) == 0)
        {
            foundNode = node.get();
        }
    }

    return foundNode;
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

