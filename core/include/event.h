#pragma once

#include <functional>
#include <memory>
#include <map>
#include <variant>

#include <sol/sol.hpp>

namespace HeartEngine
{
class EventManager;
class EventBus;
class EventListener;
class EventHandle;

// Collection of event bus's by name.
struct EventManager
{
    void clearEvents() { events.clear(); }

    void deleteEvent(std::string eventName) { events.erase(eventName); }

    std::map<std::string, EventBus> events;
};

// A collection of listeners.
class EventBus
{
    friend class EventHandle;
public:
    EventHandle* addListener(std::function<void()> function);
    EventHandle* addListener(std::function<void(sol::object)> function);
    EventHandle* addListener(std::function<void(sol::object, sol::object)> function);

    void removeListener(EventHandle& handle);

    void run(sol::object obj1 = sol::nil, sol::object obj2 = sol::nil);

private:
    std::map<std::unique_ptr<EventHandle>, EventListener> eventHandlers;

    bool inside_run = false;
};

// A single function listener.
class EventListener
{
public:
    EventListener() {}

    EventListener(const EventListener& t) { event = t.event; }

    std::variant<
        std::function<void()>,
        std::function<void(sol::object)>,
        std::function<void(sol::object, sol::object)>
    > event;
};

// Allows for deleting the event listener referencing this handler.
class EventHandle
{
    friend class EventBus;
public:
    inline static EventHandle Create();

    EventHandle(const EventHandle& t) { identifier = t.identifier; }
    EventHandle(EventHandle& t) { identifier = t.identifier; }

    bool operator >(const EventHandle& handle) const { return identifier > handle.identifier; }
    bool operator <(const EventHandle& handle) const { return identifier < handle.identifier; }

    bool isActive() const { return active; }
private:
    EventHandle() {}

    bool active = true;

    inline static size_t Identifier = 0;
    size_t identifier;
};
}