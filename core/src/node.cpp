#include "node.h"
#include "engine.h"

#include <algorithm>

namespace HeartEngine
{
template <> Component* Node::addComponent(Component, std::string);
template <> Component& Node::getComponentT(std::string_view) const;

Component& Node::getComponent(std::string_view name) const
{
    for (const auto &component : components)
    {
        if (component->name.compare(name) == 0)
        {
            return *component.get();
        }
    }

    throw HeartException({"No component found with name: ", name, " on node: ", this->name});
}

void Node::removeComponent(std::string_view name)
{
    //TODO
}

void Node::destroy()
{
    engine->removeNode(name);

    engine->checkEarlyResourceRelease();
}

Component& Node::addComponent(std::string_view typeName, std::string name, sol::variadic_args va)
{
    auto component = engine->getComponentFromRegistry(typeName, name, va);

    if (component == nullptr)
    {
        throw HeartException({"Could not find component: ", typeName, " in the registry. Make sure to register both the module AND the component with the engine."});
    }

    Component* componentPtr = component.get();

    components.push_back(std::move(component));

    componentPtr->node = this;
    componentPtr->setupLuaState(*luaState, "");

    return *componentPtr;
}

void Node::onCreate()
{
    for (auto &component : components)
    {
        if (component->checkHasRequired())
        {
            component->_on_create();
        }
        else
        {
            throw HeartException({"Failed to initialize _on_create. Component requirement has not been satisfied."});
        }
    }
}
void Node::onDestroy()
{
    for (auto& component : components)
    {
        component->_on_destroy();
    }

    components.clear();
}

void Node::setupLuaState(sol::state& p_luaState, std::string scriptName)
{
    luaState = &p_luaState;

    // Create lua environment.
    if (scriptName.compare("") != 0)
    {
        luaEnv = sol::environment(*luaState, sol::create, luaState->globals());

        populateEnvironment();

        engine->fileManager.loadScript(scriptName, *luaState, &luaEnv);
    }

    if (engine->started)
    {
        onCreate();
    }
}

void Node::populateEnvironment()
{
    luaEnv.set("name", &name);
    luaEnv["engine"] = engine;

    luaEnv["addComponent"] =
        [this](std::string_view typeName, std::string name, sol::variadic_args va) -> sol::table
        {
            //TODO: Breaks with error expected table recieved nil if populateLuaData is not setup.
            // Uses a named table in luaEnv for accessing the cool features of sol usertype.
            // Does not work with directly returning the luaEnv table.
            return addComponent(typeName, name, va).luaEnv[name];
        };
    luaEnv["addLuaComponent"] =
        [this](std::string scriptName, std::string name) -> sol::table&
        {
            return addComponent(LuaComponent(name), scriptName)->luaEnv;
        };
    
    luaEnv["getComponent"] =
        [this](std::string_view component) -> sol::table
        {
            auto foundComponent = &getComponent(component);
            if (foundComponent->isLuaScript)
            {
                return foundComponent->luaEnv;
            }
            else
            {
                return foundComponent->luaEnv[component];
            }
        };
    
    luaEnv["events"] = &events;
}
}