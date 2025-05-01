/**
 * @class TestClassEventListener
 * @brief A helper class designed for testing the functionality of the EventDispatcher class.
 * 
 * This class is used to verify that methods from class instances can be invoked correctly 
 * as event listeners, not just static methods or standalone functions. It provides two 
 * listener methods (`listener1` and `listener2`) that can be registered as callbacks 
 * with the EventDispatcher. The class also tracks how many times each listener is called 
 * and stores the last data received by each listener.
 * 
 * @tparam T The type of data that the listeners will handle.
 * 
 * @details
 * - `listener1` and `listener2` are member functions that process incoming data and 
 *   increment their respective counters (`listener1Called` and `listener2called`).
 * - `getListener1` and `getListener2` return lambda functions that bind the respective 
 *   listener methods, allowing them to be used as callbacks in the EventDispatcher.
 * - The class ensures that instance methods can be used seamlessly as event listeners, 
 *   making it suitable for testing scenarios involving non-static methods.
 */

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