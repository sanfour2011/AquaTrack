
#include <gtest/gtest.h>
#include "EventDispatcher.hpp"
#include "TestClassEventListener.hpp"

enum class TestEvents : uint_fast8_t
{
    TEST_EVENT_1,
    TEST_EVENT_2
};

class EventDispatcherTest : public ::testing::Test
{
protected:
    EventDispatcher dispatcher;
    TestClassEventListener testListerner;

    void SetUp() override
    {
        testListerner.listener1Called = 0;
        testListerner.listener2called = 0;
        testListerner.listener1Data = 0.0f;
        testListerner.listener2Data = 0.0f;
    }
};

TEST_F(EventDispatcherTest, AddListener_Tests)
{
    EXPECT_TRUE(dispatcher.addListener("TEST_EVENT_1", testListerner.getListener1()));
    EXPECT_EQ(dispatcher.getTotalNumberOfListeners(), 1);
    EXPECT_TRUE(dispatcher.addListener("TEST_EVENT_2", testListerner.getListener2()));
    EXPECT_EQ(dispatcher.getTotalNumberOfListeners(), 2);

    EXPECT_FALSE(dispatcher.addListener("TEST_EVENT_1", testListerner.getListener2())); // add same listener a secound time, should do nothing
    EXPECT_EQ(dispatcher.getTotalNumberOfListeners(), 2);
}

// TEST_F(EventDispatcherTest, Add_tow_times_same_listener)
// {
//     EXPECT_TRUE(dispatcher.addListener("TEST_EVENT_1", listener1));
//     EXPECT_EQ(dispatcher.getTotalNumberOfListeners(), 1);
//     EXPECT_FALSE(dispatcher.addListener("TEST_EVENT_1", listener1));
//     EXPECT_EQ(dispatcher.getTotalNumberOfListeners(), 1);
// }

// TEST_F(EventDispatcherTest, Dispatching_Tests)
// {
//     float aTestValue = 1.2;
//     EXPECT_TRUE(dispatcher.addListener("TEST_EVENT_1", listener1));
//     dispatcher.dispatch("TEST_EVENT_1", aTestValue);

//     EXPECT_EQ(listener1Called, 1);
//     EXPECT_EQ(listener1Data, aTestValue);
// }

// TEST_F(EventDispatcherTest, Dispatching_Same_Event_Multi_Listeners)
// {
//     float aTestValue = 1.2f;
//     EXPECT_TRUE(dispatcher.addListener("TEST_EVENT_1", listener1));
//     EXPECT_TRUE(dispatcher.addListener("TEST_EVENT_1", listener2));
//     dispatcher.dispatch("TEST_EVENT_1", aTestValue);

//     EXPECT_EQ(listener1Called, 1);
//     EXPECT_EQ(listener1Data, aTestValue);

//     EXPECT_EQ(listener2called, 1);
//     EXPECT_EQ(listener2Data, aTestValue);
// }

// TEST_F(EventDispatcherTest, Dispatch_No_Registered_Event)
// {
//     EXPECT_NO_THROW(dispatcher.dispatch("TEST_EVENT_1", 1.2f));
// }

// TEST_F(EventDispatcherTest, HasEvent_test)
// {
//     EXPECT_TRUE(dispatcher.addListener("TEST_EVENT_1", listener1));
//     EXPECT_TRUE(dispatcher.hasEvent("TEST_EVENT_1"));
//     EXPECT_FALSE(dispatcher.hasEvent("TEST_EVENT_2"));
// }

// TEST_F(EventDispatcherTest, Compare_Listeners)
// {
//     EXPECT_TRUE(EventDispatcher::isSameFunctionListener(listener1, listener1));
//     EXPECT_FALSE(EventDispatcher::isSameFunctionListener(listener1, listener2));
// }
