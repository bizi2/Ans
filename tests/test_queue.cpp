// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <../gtest/gtest.h>
#include "../lib_queue/queue.h"

TEST(TQueueTests, DefaultConstructor) {
    TQueue<int> que;
    EXPECT_TRUE(que.empty());
    EXPECT_EQ(que.size(), 0);
}
TEST(TQueueTests, CopyConstructor) {
    TQueue<int> que;
    que.push_back(1);
    TQueue<int> que2(que);
    EXPECT_FALSE(que2.empty());
    EXPECT_EQ(que2.size(), 1);
}
TEST(TQueueTests,OperatorQually) {
    TQueue<int> que;
    que.push_back(1);
    que.push_back(2);
    TQueue<int> que2; ;
    que2 = que;
    EXPECT_EQ(que2.front(),que.front());
    EXPECT_FALSE(que2.empty());
    EXPECT_EQ(que2.size(), 2);

}
TEST(TQueueTests, Distructor) {
    TQueue<int> que;

}
TEST(TQueueTests, PushBack) {
    TQueue<int> que;
    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    EXPECT_FALSE(que.empty());
    EXPECT_EQ(que.size(), 3);
}
TEST(TQueueTests, PopFront) {
    TQueue<int> que;
    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    que.pop_front();
    EXPECT_EQ(que.front(), 2);
    EXPECT_FALSE(que.empty());
    EXPECT_EQ(que.size(), 2);
}
TEST(TQueueTests, Front) {
    TQueue<int> que;
    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    EXPECT_EQ(que.front(), 1);
    EXPECT_FALSE(que.empty());
    EXPECT_EQ(que.size(), 3);
}
TEST(TQueueTests, Empty) {
    TQueue<int> que;
    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    EXPECT_FALSE(que.empty());
    que.pop_front();
    que.pop_front();
    que.pop_front();
    EXPECT_TRUE(que.empty());
}
TEST(TQueueTests, Size) {
    TQueue<int> que;
    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    EXPECT_FALSE(que.empty());
    EXPECT_EQ(que.size(), 3);
    que.pop_front();
    EXPECT_EQ(que.size(), 2);
}
TEST(TQueueTests, Print) {
    TQueue<int> que;
    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    que.print();
}







