#pragma once

#include <string>
#include <memory>

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