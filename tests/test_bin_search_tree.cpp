// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES
#include "../gtest/gtest.h"
#include "../lib_bin_search_tree/bin_search_tree.h"

TEST(Test_BinSearchTree , FunctionSearch) {
    TBinSearchTree<int> tree;
    
    // Вставляем тестовые данные
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    
    // Проверяем поиск существующих значений
    ASSERT_NE(tree.search(5), nullptr);
    ASSERT_NE(tree.search(3), nullptr);
    ASSERT_NE(tree.search(7), nullptr);
    
    // Проверяем поиск несуществующих значений
    ASSERT_EQ(tree.search(1), nullptr);
    ASSERT_EQ(tree.search(8), nullptr);
}