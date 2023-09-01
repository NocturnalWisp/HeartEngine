#pragma once

#include "../src/resource_base.h"

template <class T>
class Resource : public ResourceBase
{
public:
    Resource(const char* p_name) : ResourceBase(p_name) {}
};