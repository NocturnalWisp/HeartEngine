#pragma once

#include <string>
#include <memory>

namespace sol { class state; }

namespace HeartEngine
{
class Resource
{
    friend class Engine;
public:
    Resource(std::string p_name) : name(p_name) {} 

    virtual void _load() {}
    virtual void _unload() {}

    Engine* engine;

    std::string name;
private:
    friend void load(const std::shared_ptr<Resource>& res)
    {
        if (res->loaded)
            return;

        res->_load();
        res->loaded = true;
    }

    friend void unload(const std::shared_ptr<Resource>& res)
    {
        if (!res->loaded)
            return;

        res->_unload();
        res->loaded = false;
    }

    bool loaded = false;
};
}