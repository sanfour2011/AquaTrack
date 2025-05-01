
#include <gtest/gtest.h>
#include "EventDispatcher.hpp"
#include "TestClassEventListener.hpp"

constexpr const char* TEST_EVENT_1 = "TEST_EVENT_1";

enum class TestEvents : uint_fast8_t
{
    TEST_EVENT_1,
    TEST_EVENT_2
};

class EventDispatcherTest : public ::testing::Test
{
protected:
    EventDispatcher<float> floatEventManager;
    EventDispatcher<std::string> stringEventManager;

    TestClassEventListener<float> testFloatListener;
    TestClassEventListener<std::string> testStringListener;

    void SetUp() override
    {
        testFloatListener.listener1Called = 0;
        testFloatListener.listener2called = 0;
        testFloatListener.listener1Data = 0.0f;
        testFloatListener.listener2Data = 0.0f;
      
        testStringListener.listener1Called = 0;
        testStringListener.listener2called = 0;
        testStringListener.listener1Data = "";
        testStringListener.listener2Data = "";
    }
};


TEST_F(EventDispatcherTest, AddListener_Tests)
{
    EXPECT_NE(floatEventManager.addListener(TEST_EVENT_1, testFloatListener.getListener1()), 0);
    // Force creation of a new string object to check if the listener is stored correctly.
    EXPECT_NE(floatEventManager.addListener(std::string("TEST_EVENT") + "2", testFloatListener.getListener1()), 0);
    EXPECT_NE(floatEventManager.addListener("TEST_EVENT_3", testFloatListener.getListener2()), 0);
    EXPECT_EQ(floatEventManager.getTotalNumberOfListeners(), 3); // 2 listeners

    EXPECT_NE(stringEventManager.addListener(TEST_EVENT_1, testStringListener.getListener1()), 0);
    // Force creation of a new string object to check if the listener is stored correctly.
    EXPECT_NE(stringEventManager.addListener(std::string("TEST_EVENT") + "2", testStringListener.getListener1()), 0);
    EXPECT_NE(stringEventManager.addListener("TEST_EVENT_3", testStringListener.getListener2()), 0);
    EXPECT_EQ(stringEventManager.getTotalNumberOfListeners(), 3); // 2 listeners
}

TEST_F(EventDispatcherTest, Dispatching_Tests)
{

    float aTestValue = 1.2;
    EXPECT_NE(floatEventManager.addListener("TEST_EVENT_1", testFloatListener.getListener1()),0);
    floatEventManager.addListener(TEST_EVENT_1, testFloatListener.getListener2());
    floatEventManager.dispatch(TEST_EVENT_1, aTestValue);
    EXPECT_EQ(testFloatListener.listener1Called, 1);
    EXPECT_EQ(testFloatListener.listener1Data, aTestValue);
    EXPECT_EQ(testFloatListener.listener2called, 1);
    EXPECT_EQ(testFloatListener.listener2Data, aTestValue);

    std::string testStringValue = "TEST_STRING";
    EXPECT_NE(stringEventManager.addListener(TEST_EVENT_1, testStringListener.getListener1()),0);
    stringEventManager.dispatch("TEST_EVENT_1", testStringValue);
    EXPECT_EQ(testStringListener.listener1Called, 1);
    EXPECT_EQ(testStringListener.listener1Data, testStringValue);
}

TEST_F(EventDispatcherTest, RemoveListener_Tests)
{
    EventDispatcher<float>::ListenerId listenerId = floatEventManager.addListener(
        TEST_EVENT_1, 
        testFloatListener.getListener1()
    );  
    float aTestValue = 1.2;

    floatEventManager.dispatch(TEST_EVENT_1, aTestValue);
    EXPECT_EQ(testFloatListener.listener1Called, 1);
    EXPECT_EQ(testFloatListener.listener1Data, aTestValue);

    EXPECT_NE(listenerId, 0);
    EXPECT_EQ(floatEventManager.getTotalNumberOfListeners(), 1);

    EXPECT_TRUE(floatEventManager.removeListener(listenerId));
    EXPECT_EQ(floatEventManager.getTotalNumberOfListeners(), 0);
}


