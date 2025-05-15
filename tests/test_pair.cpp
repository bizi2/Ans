// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include "../gtest/gtest.h"
#include "../lib_pair/pair.h"

TEST(TPairTest, First) {
    TPair<int, std::string> pair(42, "hello");
    EXPECT_EQ(42, pair.first());
}
TEST(TPairTest, Second) {
    TPair<int , int> pair(42, 43);
    EXPECT_EQ(43, pair.second());
}
TEST(TPairTest, SetFirst) {
    int value = 42;
    TPair<int, int> pair(43, 44);
    pair.set_first(value);
    EXPECT_EQ(42, pair.first());
}
TEST(TPairTest, SetSecond) {
    int value = 42;
    TPair<int, int> pair(43, 44);
    pair.set_second(value);
    EXPECT_EQ(42, pair.second());
}

TEST(TPairTest, Swap) {
  TPair<int, int> pair1(10, 20);
  TPair<int, int> pair2(30, 40);
  pair1.swap(pair2);
  EXPECT_EQ(pair1.first(), 30);
  EXPECT_EQ(pair1.second(), 40);
  EXPECT_EQ(pair2.first(), 10);
  EXPECT_EQ(pair2.second(), 20);
}