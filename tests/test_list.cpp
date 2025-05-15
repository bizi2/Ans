// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include "../gtest/gtest.h"
#include "../lib_list/list.h"


TEST(TListTest, DefaultConstructorTNode) {
    TNode<int> node(5, nullptr);
    EXPECT_EQ(node.value, 5);
    EXPECT_EQ(node.pnext, nullptr);
}
TEST(TListTest, ParameterizedConstructorTNode) {
    TNode<int> node(5, nullptr);
    EXPECT_EQ(node.value, 5);
    EXPECT_EQ(node.pnext, nullptr);
}
TEST(TListTest, CopyConstructorTNode) {
    TNode<int> node1(5, nullptr);
    TNode<int> node2(node1);
    EXPECT_EQ(node2.value, 5);
    EXPECT_EQ(node2.pnext, nullptr);
}
TEST(TListTest, DistructorTNode) {
    TNode<int> node(5, nullptr);
}
TEST(TListTest, OperatorQuallyTNode) {
    TNode<int> node1(5, nullptr);
    TNode<int> node2;
    node2 = node1;
    EXPECT_EQ(node2.value, 5);
    EXPECT_EQ(node2.pnext, nullptr);
}
TEST(TListTest, SetNextTNode) {
    TNode<int> node1(5, nullptr);
    TNode<int> node2(10, nullptr);
    node1.next(&node2);
    EXPECT_EQ(node1.pnext, &node2);
}
TEST(TListTest, GetValueTNode) {
    TNode<int> node1(5, nullptr);
    EXPECT_EQ(node1.value, 5);
}
TEST(TListTest, SetValueTNode) {
    TNode<int> node1(5, nullptr);
    node1.value = 10;
    EXPECT_EQ(node1.value, 10);
}

TEST(TListTest, DefaultConstructor) {
    TList<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.head, nullptr);
    EXPECT_EQ(list.tail, nullptr);
}

TEST(TListTest, CopyConstructor) {
    TList<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    TList<int> list2(list1);
    EXPECT_FALSE(list2.isEmpty());
    EXPECT_EQ(list2.head->value, 1);
    EXPECT_EQ(list2.tail->value, 3);
}

TEST(TListTest, PushFront) {
    TList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_EQ(list.head->value, 3);
    EXPECT_EQ(list.tail->value, 1);
}

TEST(TListTest, PushBack) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.tail->value, 3);
}

TEST(TListTest, Insert) {
    TList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(1, 2);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.head->pnext->value, 2);
    EXPECT_EQ(list.tail->value, 3);
}

TEST(TListTest, InsertAfter) {
    TList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insertAfter(2, 1);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.head->pnext->value, 2);
    EXPECT_EQ(list.tail->value, 3);
}

TEST(TListTest, InsertAt) {
    TList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insertAt(2, 1);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.head->pnext->value, 2);
    EXPECT_EQ(list.tail->value, 3);
}

TEST(TListTest, Find) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    TNode<int>* node = list.find(2);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->value, 2);
}

TEST(TListTest, RemoveValue) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.removeValue(2);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.tail->value, 3);
}

TEST(TListTest, RemoveAt) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.removeAt(1);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.tail->value, 3);
}

TEST(TListTest, Erase) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    TNode<int>* node = list.head->pnext;
    list.erase(node);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.tail->value, 3);
}

TEST(TListTest, Replace) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.replace(1, 4);
    EXPECT_EQ(list.head->value, 1);
    EXPECT_EQ(list.head->pnext->value, 4);
    EXPECT_EQ(list.tail->value, 3);
}


