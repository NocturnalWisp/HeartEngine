#pragma once

#include <string>
#include <memory>

#include "lua_environment.h"

namespace sol { class state; }

namespace HeartEngine { class Engine; }

namespace HeartEngine
{
class Resource : public LuaEnvironment
{
    friend class Engine;
public:
    Resource(std::string p_name) : name(p_name) {} 

    virtual void _on_load();
    virtual void _on_unload();

    Engine* engine;

    std::string name;
protected:
    virtual void setEnvironment() = 0;
private:
    void setupLuaState(sol::state& state, std::string scriptName = "") override;

    friend void load(const std::shared_ptr<Resource>& res)
    {
        if (res->loaded)
            return;

        res->_on_load();
        res->loaded = true;
    }

    friend void unload(const std::shared_ptr<Resource>& res)
    {
        if (!res->loaded)
            return;

        res->_on_unload();
        res->loaded = false;
    }

    bool loaded = false;

    bool isLuaScript = false;
};

class LuaResource : public Resource
{
    SETUP_RESOURCE();
public:
    LuaResource(std::string name ) : Resource(name) {}
};
}