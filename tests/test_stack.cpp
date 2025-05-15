// Copyright 2024 Anvar

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "../gtest/gtest.h"
#include "../lib_stack/stack.h"

TEST(TStackTests, DefaultConstructor) {
    TStack<int> sta;
    EXPECT_TRUE(sta.empty());
    EXPECT_EQ(sta.size(), 0);
}
TEST(TStackTests, CopyConstructor) {
    TStack<int> sta;
    sta.push(1);
    TStack<int> sta2(sta);
    EXPECT_FALSE(sta2.empty());
    EXPECT_EQ(sta2.size(), 1);
}
TEST(TStackTests,OperatorQually) {
    TStack<int> sta;
    sta.push(1);
    sta.push(2);
    TStack<int> sta2 ;
    sta2 = sta;
    EXPECT_EQ(sta2.top(),sta.top());
    EXPECT_FALSE(sta2.empty());
    EXPECT_EQ(sta2.size(), 2);

}
TEST(TStackTests, Distructor) {
    TStack<int> sta;

}
TEST(TStackTests, Push) {
    TStack<int> sta;
    sta.push(1);
    sta.push(2);
    EXPECT_EQ(sta.size(), 2);
    EXPECT_EQ(sta.top(), 2);
}
TEST(TStackTests, Pop) {
    TStack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    sta.pop();
    EXPECT_EQ(sta.size(), 2);
    EXPECT_EQ(sta.top(), 2);
    sta.pop();
    EXPECT_EQ(sta.size(), 1);
    EXPECT_EQ(sta.top(), 1);
    sta.pop();
    EXPECT_TRUE(sta.empty());
}
TEST(TStackTests, Top) {
    TStack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    EXPECT_EQ(sta.top(), 3);
}
TEST(TStackTests, Empty) {
    TStack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    EXPECT_FALSE(sta.empty());
    sta.pop();
    sta.pop();
    sta.pop();
    EXPECT_TRUE(sta.empty());

}
TEST(TStackTests, Size) {
    TStack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    EXPECT_EQ(sta.size(), 3);
}
TEST(TStackTests, Print) {
    TStack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    sta.print();
}
