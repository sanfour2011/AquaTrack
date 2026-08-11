#pragma once

#include <functional>
// #include <map>
#include <unordered_map> // is more effizient and can be used when key order is irrelevant (found by chance)
#include <vector>
#include <algorithm>

#ifndef MAX_LISTENERS
#define MAX_LISTENERS 255 // Maximum number of listeners allowed per event (maximum possible is 65535)
#endif

// class String; // Forward-Deklaration of String so its not needed to include Arduino.h!

template <typename T>
class EventDispatcher
{

public:
    using EventCallback = std::function<void(const T &)>;
    using ListenerId = uint_fast16_t; // just for better readability

    EventDispatcher() = default; // =default tells the compiler to generate these automatically. This is efficient, clear, and makes the class trivially constructible/destructible.
    ~EventDispatcher() = default;

    // just to skip the std::string constructor when char* is passed (when no std::string is wanted it is needed to ommit addListener with std::string! hashing is then required to store it in the map)
    ListenerId addListener(const char *eventId, EventCallback &listner) //&&-> Rvalue-Referenz not working using Lvalue-Referenz instead
    {
        return addListener(std::string(eventId), listner);
    }

    void dispatch(const char *eventId, const T &data)
    {
        dispatch(std::string(eventId), data);
    }

    ListenerId addListener(const std::string &eventId, EventCallback &&listner)
    {
        auto &listeners = m_eventListeners[eventId];

        if (listeners.size() >= MAX_LISTENERS)
            return 0;

        listeners.emplace_back(getNextListenerId(), std::move(listner));

        return listeners.back().getId();
    }

    void dispatch(const std::string &eventId, const T &data)
    {
        auto it = m_eventListeners.find(eventId);
        if (it != m_eventListeners.end())
        {
            for (const auto &listener : it->second)
                listener.getCallback()(data);
        }
    }

    size_t getTotalNumberOfListeners() const
    {
        size_t total = 0;
        for (const auto &pair : m_eventListeners)
            total += pair.second.size();
        return total;
    }

    bool removeListener(ListenerId targetId)
    {
        bool removed = false;

        auto it = m_eventListeners.begin();
        while (it != m_eventListeners.end())
        {
            auto &listeners = it->second; // use & to avoid copying the vector otherwise it would change nocthing when removing the listener

            for (auto listenerIt = listeners.begin(); listenerIt != listeners.end(); ++listenerIt)
            {
                if (listenerIt->getId() == targetId)
                {
                    listeners.erase(listenerIt);
                    removed = true;
                    break;
                }
            }

            if (listeners.empty())
               it = m_eventListeners.erase(it); // erasing the iterator and getting a new one
            else
                ++it; // increment iterator to the next eventId only if not erased 
        }
        return removed;
    }

    bool hasEvent(std::string &eventId) const
    {
        return m_eventListeners.find(eventId) != m_eventListeners.end();
    }

private:
    struct ListenerEntry
    {
        ListenerEntry(ListenerId id, EventCallback callback) : m_id(id), m_callback(callback) {}
        ListenerId getId() const { return m_id; }
        EventCallback getCallback() const { return m_callback; }

    private:
        ListenerId m_id;
        EventCallback m_callback;
    };

    ListenerId m_nextId = 1; // 0 is reserved for error cases
    ListenerId getNextListenerId()
    {
        if (m_nextId == 0)
            m_nextId = 1; // 0 is reserved for error cases
        return m_nextId++;
    }
    // std::map<std::string, std::vector<EventCallback>> _eventListeners; //in my case unordered_map is more effizient
    std::unordered_map<std::string, std::vector<ListenerEntry>> m_eventListeners;
};