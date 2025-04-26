#pragma once
#include <functional>
// #include <map>
#include <unordered_map> // is more effizient and can be used when key order is irrelevant (found by chance)
#include <vector>
#include <algorithm>

#ifndef MAX_LISTENERS
#define MAX_LISTENERS 10
#endif
#ifndef MAX_EVENTS
#define MAX_EVENTS 10
#endif

#include <iostream>
// class String; // Forward-Deklaration of String so its not needed to include Arduino.h!

class EventDispatcher
{

public:
    using EventCallback = std::function<void(float)>;

    static bool isSameFunctionListener(const EventCallback& a, const EventCallback& b)
    {
        //ToDo: Geht irgendwie nicht unter Arduino!
        // if (auto aTarget = a.target<void(*)(float)>()) {
        //     if (auto bTarget = b.target<void(*)(float)>()) {
        //         return *aTarget == *bTarget;
        //     }
        // }
        // return false;
        return false;
    }

    // bool addListener2(const std::string& eventId, const EventCallback& listener) {
    //     auto& listeners = m_eventListeners[eventId];

    //     // Überprüfen, ob der Listener bereits registriert ist
    //     if (std::find_if(listeners.begin(), listeners.end(),
    //                      [&listener](const EventCallback& existingListener) {
    //                          return listener.target<void()>() == existingListener.target<void()>();
    //                      }) != listeners.end()) {
    //         return false; // Listener ist bereits registriert
    //     }

    //     if (listeners.size() >= MAX_LISTENERS) {
    //         return false; // Maximale Anzahl von Listenern erreicht
    //     }

    //     listeners.push_back(listener);
    //     return true;
    // }

    // bool removeListener(const std::string eventId, EventCallback listner)
    bool addListener(const std::string eventId, EventCallback listner)
    {
        //return addListener2(eventId, listner);
        auto &listeners = m_eventListeners[eventId];
        // ToDo: check weather the listner is registred with another eventId
        for (const auto &l : listeners)
        {
            if (isSameFunctionListener(l, listner))
                return false; // warning lister already exists.
        }

        if (listeners.size() >= MAX_LISTENERS)
        {
            return false;
        } // error max listeners of MAX_LISTENERS reached

        listeners.push_back(listner);
        return true;
        // return NO_ERROR
    }

    void dispatch(const std::string eventId, const float data)
    {
        if (!hasEvent(eventId))
            return; // Warning no event found with id=> nothing to do:
        for (auto &alistner : m_eventListeners[eventId])
            alistner(data);
    }

    size_t getTotalNumberOfListeners() const
    {
        size_t total = 0;
        for (const auto &pair : m_eventListeners)
            total += pair.second.size();
        return total;
    }

    bool hasEvent(std::string eventId) const
    {
        return m_eventListeners.find(eventId) != m_eventListeners.end();
    }

    EventDispatcher() = default;
    ~EventDispatcher() = default;

private:
    // std::map<std::string, std::vector<EventCallback>> _eventListeners; //in my case unordered_map is more effizient
    std::unordered_map<std::string, std::vector<EventCallback>> m_eventListeners;
};