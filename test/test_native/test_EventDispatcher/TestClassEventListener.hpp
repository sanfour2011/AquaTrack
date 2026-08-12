// Helper for EventDispatcher tests: verifies that member functions
// (not just free functions) work as listeners.

 #pragma once
 #include <EventDispatcher.hpp>

template <typename T>
class TestClassEventListener
{
public:
    int listener1Called = 0;
    int listener2called = 0;
    // do not intilize with 0, otherwise "basic_string::_M_construct null not valid" error will be thrown when using std::string during testing:
    T listener1Data ; 
    T listener2Data ;

    void listener1(T data)
    {
        listener1Data = data;
        listener1Called++;
    }

    void listener2(T data)
    {
        listener2Data = data;
        listener2called++;
    }

    typename EventDispatcher<T>::EventCallback getListener1()
    {
        return [this](T data) { listener1(data); };
    }

    typename EventDispatcher<T>::EventCallback getListener2()
    {
        return [this](T data) { listener2(data); };
    }
};