#pragma once

#include <functional>
#include <memory>
#include <map>
#include <variant>

#include <sol.hpp>

class EventBus;

struct EventManager
{
    void clearEvents()
    {
        events.clear();
    }

    void deleteEvent(std::string eventName)
    {
        events.erase(eventName);
    }

    std::map<std::string, EventBus> events;
};

class Event
{
public:
    Event() {}

    Event(const Event& t)
    {
        event = t.event;
    }

    std::variant<
        std::function<void()>,
        std::function<void(sol::object)>,
        std::function<void(sol::object, sol::object)>
    > event;
};

class EventHandle
{
    friend class EventBus;
public:
    bool isActive() const { return active; }

    inline static EventHandle Create()
    {
        EventHandle handle = EventHandle();

        handle.identifier = Identifier++;

        return handle;
    }

    EventHandle(const EventHandle& t)
    {
        identifier = t.identifier;
    }

    EventHandle(EventHandle& t)
    {
        identifier = t.identifier;
    }

    bool operator >(const EventHandle& handle) const
    {
        return identifier > handle.identifier;
    }

    bool operator <(const EventHandle& handle) const
    {
        return identifier < handle.identifier;
    }

private:
    EventHandle() { identifier = Identifier++; }

    bool active = true;

    inline static size_t Identifier = 0;
    size_t identifier;
};

class EventBus
{
    friend class EventHandle;
public:
    EventHandle* addListener(std::function<void()> function)
    {
        std::unique_ptr<EventHandle> handle = std::make_unique<EventHandle>(EventHandle::Create());

        auto ptr = handle.get();

        eventHandlers[std::move(handle)].event = function;

        return ptr;
    }

    EventHandle* addListener(std::function<void(sol::object)> function)
    {
        std::unique_ptr<EventHandle> handle = std::make_unique<EventHandle>(EventHandle::Create());

        auto ptr = handle.get();

        eventHandlers[std::move(handle)].event = function;

        return ptr;
    }

    EventHandle* addListener(std::function<void(sol::object, sol::object)> function)
    {
        std::unique_ptr<EventHandle> handle = std::make_unique<EventHandle>(EventHandle::Create());

        auto ptr = handle.get();

        eventHandlers[std::move(handle)].event = function;

        return ptr;
    }

    void removeListener(EventHandle& handle)
    {
        if (inside_run)
        {
            Debug::printerr("Cannot remove a listener while running an event.");
            return;
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

    void run()
    {
        run(sol::nil, sol::nil);
    }

    void run(sol::object obj1)
    {
        run(obj1, sol::nil);
    }

    void run(sol::object obj1, sol::object obj2)
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

private:
    std::map<std::unique_ptr<EventHandle>, Event> eventHandlers;

    bool inside_run = false;
};