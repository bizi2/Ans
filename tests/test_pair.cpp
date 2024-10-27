//Copyright 2024 Anvar
#include "../gtest/gtest.h"
#include "../lib_pair/pair.h"

TEST(TPairTest, SetMethods) {
    TPair<int, int> pair1(1, 2);
    pair1.set_first(3);
    pair1.set_second(4);
    EXPECT_EQ(pair1.first(), 3);
    EXPECT_EQ(pair1.second(), 4);
}

TEST(TPairTest, AssignmentOperator) {
    TPair<int, int> pair1(1, 2);
    TPair<int, int> pair2 = pair1;
    EXPECT_EQ(pair2.first(), 1);
    EXPECT_EQ(pair2.second(), 2);
}

TEST(TPairTest, AdditionOperator) {
    TPair<int, int> pair1(1, 2);
    TPair<int, int> pair2(3, 4);
    TPair<int, int> result = pair1 + pair2;
    EXPECT_EQ(result.first(), 4);
    EXPECT_EQ(result.second(), 6);
}

TEST(TPairTest, EqualityOperator) {
    TPair<int, int> pair1(5, 6);
    TPair<int, int> pair2(5, 6);
    TPair<int, int> pair3(7, 8);
    EXPECT_TRUE(pair1 == pair2);
    EXPECT_FALSE(pair1 == pair3);
}
