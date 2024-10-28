// Copyright 2024 Anvar
#include <../gtest/gtest.h>
#include "../lib_queue/queue.h"

// Тесты для класса очереди
TEST(TQueueTest, QueueInitialization) {
    TQueue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(TQueueTest, EnqueueAndFront) {
    TQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
}


TEST(TQueueTest, Overflow) {
    TQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(1);
    queue.enqueue(2);
    EXPECT_FALSE(queue.empty());
}






