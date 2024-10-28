// Copyright 2024 Anvar
#include "../gtest/gtest.h"
#include "../lib_stack/stack.h"
TEST(Test_Stack, _data_fun){
    TStack <int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
}
TEST(TStackTests, DefaultConstructor) {
    TStack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(TStackTests, AssignmentOperator) {
    TStack<int> stack;
    stack.push(1);
    stack.push(2);

    TStack<int> anotherStack;
    anotherStack = stack;

    EXPECT_FALSE(anotherStack.empty());
    EXPECT_EQ(anotherStack.size(), 2);
    EXPECT_EQ(anotherStack.top(), 2);
}

TEST(TStackTests, Push) {
    TStack<int> stack;
    stack.push(1);
    stack.push(2);
    
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);
}

TEST(TStackTests, Pop) {
    TStack<int> stack;
    stack.push(1);
    stack.push(2);
    
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 1);

    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST(TStackTests, Top) {
    TStack<int> stack;
    stack.push(1);
    stack.push(2);
    
    EXPECT_EQ(stack.top(), 2);

    stack.pop();
    EXPECT_EQ(stack.top(), 1);
}

TEST(TStackTests, Empty) {
    TStack<int> stack;
    EXPECT_TRUE(stack.empty());
    
    stack.push(1);
    EXPECT_FALSE(stack.empty());
}

TEST(TStackTests, Size) {
    TStack<int> stack;
    EXPECT_EQ(stack.size(), 0);
    
    stack.push(1);
    EXPECT_EQ(stack.size(), 1);

    stack.push(2);
    EXPECT_EQ(stack.size(), 2);

    stack.pop();
    EXPECT_EQ(stack.size(), 1);
}

TEST(TStackTests, PopThrowsWhenEmpty) {
    TStack<int> stack;
    EXPECT_THROW(stack.pop(), std::logic_error);
}

TEST(TStackTests, TopThrowsWhenEmpty) {
    TStack<int> stack;
    EXPECT_THROW(stack.top(), std::logic_error);
}
