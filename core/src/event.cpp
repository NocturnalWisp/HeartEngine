#include "event.h"

#include "debug.h"

namespace HeartEngine
{
// EventBus
EventHandle* EventBus::addListener(std::function<void()> function)
{
    std::unique_ptr<EventHandle> handle = std::make_unique<EventHandle>(EventHandle::Create());

    auto ptr = handle.get();

    eventHandlers[std::move(handle)].event = function;

    return ptr;
}

EventHandle* EventBus::addListener(std::function<void(sol::object)> function)
{
    std::unique_ptr<EventHandle> handle = std::make_unique<EventHandle>(EventHandle::Create());

    auto ptr = handle.get();

    eventHandlers[std::move(handle)].event = function;

    return ptr;
}

EventHandle* EventBus::addListener(std::function<void(sol::object, sol::object)> function)
{
    std::unique_ptr<EventHandle> handle = std::make_unique<EventHandle>(EventHandle::Create());

    auto ptr = handle.get();

    eventHandlers[std::move(handle)].event = function;

    return ptr;
}

void EventBus::removeListener(EventHandle& handle)
{
    if (inside_run)
    {
        throw HeartException("Attempting to remove an event listener while inside a run call.");
    }

    for (auto iter = eventHandlers.cbegin();
        iter != eventHandlers.cend();)
    {
        if (iter->first->identifier == handle.identifier)
        {
            eventHandlers.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
}

void EventBus::run(sol::object obj1, sol::object obj2) const
{
    inside_run = true;
    for (const auto& pair : eventHandlers)
    {
        switch (pair.second.event.index())
        {
            case 0:
                std::get<0>(pair.second.event)();
                break;
            case 1:
                std::get<1>(pair.second.event)(obj1);
                break;
            case 2:
                std::get<2>(pair.second.event)(obj1, obj2);
                break;
        }
    }

    inside_run = false;
}

//Event Handle
EventHandle EventHandle::Create()
{
    EventHandle handle = EventHandle();

    handle.identifier = Identifier++;

    return handle;
}
}