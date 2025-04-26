#include <gtest/gtest.h>
// uncomment line below if you plan to use GMock
// #include <gmock/gmock.h>

// TEST(...)
// TEST_F(...)

#if defined(ARDUINO)
#include <Arduino.h>

TEST(Dummy_Sub_Folder, an_other_dummy__Test)
{
  Serial.println("Dummy_Sub_Folder: an_other_dummy__Test");
  EXPECT_EQ(1, 1);
}

#endif