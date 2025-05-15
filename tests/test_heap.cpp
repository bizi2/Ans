// Copyright 2024 Anvar

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES
#include "../gtest/gtest.h"
#include "../lib_heap/heap.h"

TEST(Heap_Test, Parent_func_test){
    Heap<int> heap(10);
    heap.push_heap(1);

    EXPECT_EQ(heap.parent(1), 0);
    EXPECT_EQ(heap.parent(2), 0);
    EXPECT_EQ(heap.parent(3), 1);
    EXPECT_EQ(heap.parent(4), 1);
    EXPECT_EQ(heap.parent(0), 0);
}
TEST(Heap_Test, Left_Child_func_test){
    Heap<int> heap(10);
    heap.push_heap(1);

    EXPECT_EQ(heap.left_child(1), 3);
    EXPECT_EQ(heap.left_child(2), 5);
    EXPECT_EQ(heap.left_child(3), 7);
    EXPECT_EQ(heap.left_child(4), 9);
    EXPECT_EQ(heap.left_child(0), 1);
}
TEST(Heap_Test, Right_Child_func_test){
    Heap<int> heap(10);
    heap.push_heap(1);

    EXPECT_EQ(heap.right_child(1), 4);
    EXPECT_EQ(heap.right_child(2), 6);
    EXPECT_EQ(heap.right_child(3), 8);
    EXPECT_EQ(heap.right_child(4), 10);
    EXPECT_EQ(heap.right_child(0), 2);
}
TEST(HeapTest, ResizeFunctionalTest) {
    Heap<int> heap(2);
    
    // Проверяем начальное состояние
    ASSERT_TRUE(heap.is_empty());
    
    // Добавляем элементы
    heap.push_heap(1);
    ASSERT_EQ(heap.top(), 1);  // После первого элемента top() должен вернуть 1
    
    heap.push_heap(2);
    ASSERT_EQ(heap.top(), 2);  // В max-heap новый максимальный элемент 2
    
    heap.push_heap(3);
    ASSERT_EQ(heap.top(), 3);  // Теперь максимальный элемент 3
    
    // Извлекаем элементы и проверяем порядок
    EXPECT_EQ(heap.top(), 3);
    heap.pop_heap();
    
    EXPECT_EQ(heap.top(), 2);
    heap.pop_heap();
    
    EXPECT_EQ(heap.top(), 1);
    heap.pop_heap();
    
    ASSERT_TRUE(heap.is_empty());  // Куча должна быть пуста

}

TEST(HeapTest, DefaultConstructor) {
    Heap<int> heap(0);
    EXPECT_TRUE(heap.is_empty());

}

TEST(HeapTest, CapacityConstructor) {
    Heap<int> heap(5);
    EXPECT_TRUE(heap.is_empty());
    EXPECT_NO_THROW(heap.push_heap(10));
}
TEST(HeapTest, CopyConstructor) {
    Heap<int> heap1(2);
    heap1.push_heap(10);
    heap1.push_heap(20);
    
    Heap<int> heap2(heap1);
    EXPECT_EQ(heap2.top(), 20);
    heap2.pop_heap();
    EXPECT_EQ(heap2.top(), 10);
}
TEST(HeapTest, MoveConstructor) {
    Heap<int> heap1(2);
    heap1.push_heap(10);
    heap1.push_heap(20);
    
    Heap<int> heap2(std::move(heap1));
    EXPECT_EQ(heap2.top(), 20);
    heap2.pop_heap();
    EXPECT_EQ(heap2.top(), 10);

}

TEST(HeapTest, PushHeap) {
    Heap<int> heap(2);
    heap.push_heap(10);
    EXPECT_EQ(heap.top(), 10);
    heap.push_heap(20);
    EXPECT_EQ(heap.top(), 20);
    heap.push_heap(5);
    EXPECT_EQ(heap.top(), 20); // 20 остается наверху в max-heap
    
}

TEST(HeapTest, PopHeap) {
    Heap<int> heap(3);
    heap.push_heap(10);
    heap.push_heap(20);
    heap.push_heap(5);
    
    EXPECT_EQ(heap.top(), 20);
    heap.pop_heap();
    EXPECT_EQ(heap.top(), 10);
    heap.pop_heap();
    EXPECT_EQ(heap.top(), 5);
    heap.pop_heap();
    EXPECT_TRUE(heap.is_empty());
    EXPECT_THROW(heap.pop_heap(), std::out_of_range); // Попытка извлечь из пустой кучи
}

TEST(HeapTest, Emplace) {
    Heap<int> heap(10);
    heap.push_heap(10);
    heap.push_heap(20);
    heap.push_heap(30);
    
    // Заменяем элемент с индексом 1 (значение 20) на 40
    heap.emplace(1, 40);
    EXPECT_EQ(heap.top(), 40); // Теперь 40 должно быть наверху
    

    heap.emplace(0, 5);
    EXPECT_EQ(heap.top(), 30); // Теперь 30 должно всплыть наверх
    
    // Попытка заменить несуществующий индекс
    EXPECT_THROW(heap.emplace(10, 100), std::out_of_range);
}

TEST(HeapTest, Top) {
    Heap<int> heap(10);
    EXPECT_THROW(heap.top(), std::out_of_range); // Пустая куча
    
    heap.push_heap(10);
    EXPECT_EQ(heap.top(), 10);
    
    heap.push_heap(20);
    EXPECT_EQ(heap.top(), 20);
    
    heap.pop_heap();
    EXPECT_EQ(heap.top(), 10);
}

TEST(HeapTest, IsEmpty) {
    Heap<int> heap(10);
    EXPECT_TRUE(heap.is_empty());
    
    heap.push_heap(10);
    EXPECT_FALSE(heap.is_empty());
    
    heap.pop_heap();
    EXPECT_TRUE(heap.is_empty());
}

TEST(HeapTest, MinHeap) {
    Heap<int, true> minHeap(10);
    
    minHeap.push_heap(10);
    minHeap.push_heap(20);
    minHeap.push_heap(5);
    
    EXPECT_EQ(minHeap.top(), 5); // В min-heap минимальный элемент наверху
    minHeap.pop_heap();
    EXPECT_EQ(minHeap.top(), 10);
    minHeap.pop_heap();
    EXPECT_EQ(minHeap.top(), 20);
    minHeap.pop_heap();
    EXPECT_TRUE(minHeap.is_empty());
}

TEST(HeapTest, HeapifyUp) {
    Heap<int> heap(10);
    heap.emplace(0, 10);
    heap.emplace(1, 20); // Этот элемент должен всплыть наверх
    heap.emplace(2, 15);
    
    // Проверяем, что heapify_up корректно работает
    EXPECT_EQ(heap.top(), 20);
}

TEST(HeapTest, HeapifyDown) {
    Heap<int> heap(10);
    // Вручную создаем ситуацию, когда корень не максимальный
    heap.emplace(0, 10);
    heap.emplace(1, 5);
    heap.emplace(2, 15);
    
    // Проверяем, что heapify_down корректно работает
    EXPECT_EQ(heap.top(), 15); // 15 должно всплыть наверх
}