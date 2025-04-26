#pragma once
#include <EventDispatcher.hpp>

class TestClassEventListener
{
public:
    int listener1Called = 0;
    int listener2called = 0;
    float listener1Data = 0;
    float listener2Data = 0;

    void listener1(float data)
    {
        listener1Data = data;
        listener1Called++;
    }

    void listener2(float data)
    {
        listener2Data = data;
        listener2called++;
    }

    EventDispatcher::EventCallback getListener1()
    {
        return [this](float data) { listener1(data); };
    }

    EventDispatcher::EventCallback getListener2()
    {
        return [this](float data) { listener2(data); };
    }
};