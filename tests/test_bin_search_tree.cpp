// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES
#include "../gtest/gtest.h"
#include "../lib_bin_search_tree/bin_search_tree.h"

TEST(TBinSearchTreeTest, InsertAndSearch) {
    TBinSearchTree<int, int> tree;
    
    // Check empty tree
    int key = 10;
    EXPECT_EQ(tree.search(key), nullptr);
    
    // Insert elements
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(12, 12);
    tree.insert(20, 20);
    
    // Check elements through search()
    key = 10; EXPECT_NE(tree.search(key), nullptr);
    key = 5;  EXPECT_NE(tree.search(key), nullptr);
    key = 15; EXPECT_NE(tree.search(key), nullptr);
    key = 3;  EXPECT_NE(tree.search(key), nullptr);
    key = 7;  EXPECT_NE(tree.search(key), nullptr);
    key = 12; EXPECT_NE(tree.search(key), nullptr);
    key = 20; EXPECT_NE(tree.search(key), nullptr);
    key = 99; EXPECT_EQ(tree.search(key), nullptr); // Non-existent element
}

TEST(TBinSearchTreeTest, RemoveLeaf) {
    TBinSearchTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    
    int key = 5;
    tree.remove(key);
    EXPECT_EQ(tree.search(key), nullptr);
    key = 10; EXPECT_NE(tree.search(key), nullptr);
    key = 15; EXPECT_NE(tree.search(key), nullptr);
}

TEST(TBinSearchTreeTest, RemoveNodeWithOneChild) {
    TBinSearchTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(3, 3);
    
    int key = 5;
    tree.remove(key);
    EXPECT_EQ(tree.search(key), nullptr);
    key = 3;  EXPECT_NE(tree.search(key), nullptr);
    key = 10; EXPECT_NE(tree.search(key), nullptr);
}

TEST(TBinSearchTreeTest, RemoveNodeWithTwoChildren) {
    TBinSearchTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(12, 12);
    tree.insert(20, 20);
    
    int key = 15;
    tree.remove(key);
    EXPECT_EQ(tree.search(key), nullptr);
    key = 12; EXPECT_NE(tree.search(key), nullptr);
    key = 20; EXPECT_NE(tree.search(key), nullptr);
    key = 10; EXPECT_NE(tree.search(key), nullptr);
}

TEST(TBinSearchTreeTest, RemoveRoot) {
    TBinSearchTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    
    int key = 10;
    tree.remove(key);
    EXPECT_EQ(tree.search(key), nullptr);
    key = 5;  EXPECT_NE(tree.search(key), nullptr);
    key = 15; EXPECT_NE(tree.search(key), nullptr);
}

TEST(TBinSearchTreeTest, DuplicateInsert) {
    TBinSearchTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(10, 10); // Duplicate
    
    // Tree should contain only one element 10
    int key = 10;
    tree.remove(key);
    EXPECT_EQ(tree.search(key), nullptr);
}

TEST(TBinSearchTreeTest, Minimum) {
    TBinSearchTree<int, int> tree;
    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(3, 3);
    tree.insert(7, 7);
    
    // Find minimum through minimum()
    auto* minNode = tree.minimum();
    EXPECT_NE(minNode, nullptr);
    if (minNode) {
        EXPECT_EQ(minNode->key, 3);
    }
}

TEST(TBinSearchTreeTest, CopyConstructor) {
    TBinSearchTree<int, int> tree;
    // Вставляем пары (ключ, значение)
    tree.insert(1, 10);
    tree.insert(2, 5);
    tree.insert(3, 15);
    
    TBinSearchTree<int, int> treeCopy(tree);
    
    // Проверяем оригинальное дерево (ищем по ключам)
    EXPECT_NE(tree.search(1), nullptr);
    EXPECT_NE(tree.search(2), nullptr);
    EXPECT_NE(tree.search(3), nullptr);
    
    // Проверяем значения в оригинальном дереве
    EXPECT_EQ(tree.search(1)->value, 10);
    EXPECT_EQ(tree.search(2)->value, 5);
    EXPECT_EQ(tree.search(3)->value, 15);
    
    // Проверяем скопированное дерево (ищем по ключам)
    EXPECT_NE(treeCopy.search(1), nullptr);
    EXPECT_NE(treeCopy.search(2), nullptr);
    EXPECT_NE(treeCopy.search(3), nullptr);
    
    // Проверяем значения в скопированном дереве
    EXPECT_EQ(treeCopy.search(1)->value, 10);
    EXPECT_EQ(treeCopy.search(2)->value, 5);
    EXPECT_EQ(treeCopy.search(3)->value, 15);
    
    // Модифицируем копию и проверяем, что оригинал не изменился
    treeCopy.remove(2);
    EXPECT_EQ(treeCopy.search(2), nullptr);  // В копии удалено
    EXPECT_NE(tree.search(2), nullptr);     // Оригинал не изменился
    EXPECT_EQ(tree.search(2)->value, 5);    // Значение в оригинале осталось
}