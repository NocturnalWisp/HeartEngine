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

// A collection of listeners.
class EventBus
{
    friend class EventHandle;
public:
    const EventHandle* addListener(std::function<void()> function);
    const EventHandle* addListener(std::function<void(sol::object)> function);
    const EventHandle* addListener(std::function<void(sol::object, sol::object)> function);
    const EventHandle* addListener(sol::function function);

    void removeListener(const EventHandle& handle);

    void run(sol::object obj1 = sol::nil, sol::object obj2 = sol::nil) const;
    void runAll(sol::object obj1 = sol::nil, sol::object obj2 = sol::nil) const;

    void addSubEvent(std::string name);
    void deleteSubEvent(std::string eventName);

    // Access sub busses.
    EventBus& operator [](std::string name);

    EventBus& recursiveGetSubBus(const std::vector<std::string>&, int);

private:
    std::map<std::string, EventBus> subBuses;

    std::map<EventHandle, EventListener> eventHandlers;

    //TODO: Replace inside run logic with a way to do any delete/other operations after the run is complete.
    mutable bool inside_run = false;
};

// Collection of event bus's by name.
struct EventManager
{
    void clearEvents() { events.clear(); }

    void addEvent(std::string name) { events.emplace(name, EventBus()); }
    void deleteEvent(std::string eventName) { events.erase(eventName); }

    // Function to call a recursive function to go down a list of sub buses.
    EventBus& getSubBus(const std::vector<std::string>& list)
    {
        return events[list[0]].recursiveGetSubBus(list, 1);
    }

    EventBus& operator[](std::string index)
    {
        return events[index];
    }

private:
    std::map<std::string, EventBus> events;
};

// A single function listener.
class EventListener
{
public:
typedef 
    std::variant<
        std::function<void()>,
        std::function<void(sol::object)>,
        std::function<void(sol::object, sol::object)>,
        sol::function
    > EventFunction;

    EventListener() {}
    EventListener(EventFunction event) : event(event) {}
    ~EventListener()
    {
        // VERY IMPORTANT. Need to abandon the reference to any lua functions;
        // otherwise causes segfault during the dereference process.
        if (event.index() == 3)
        {
            std::get<3>(event).abandon();
        }
    }

    EventListener(const EventListener& t) { event = t.event; }

    EventFunction event;
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