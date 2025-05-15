// Copyright 2024 Anvar

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES
#include "../gtest/gtest.h"
#include "../lib_avl/avl.h"



TEST(AVLTreeTest, LeftLeftRotation) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);  // Должен вызвать правый поворот
    
    auto root = tree.getRoot();
    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->left->key, 10);
    EXPECT_EQ(root->right->key, 30);
}

TEST(AVLTreeTest, RightRightRotation) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // Должен вызвать левый поворот
    
    auto root = tree.getRoot();
    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->left->key, 10);
    EXPECT_EQ(root->right->key, 30);
}

TEST(AVLTreeTest, LeftRightRotation) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);  // Должен вызвать лево-правый поворот
    
    auto root = tree.getRoot();
    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->left->key, 10);
    EXPECT_EQ(root->right->key, 30);
}

TEST(AVLTreeTest, RightLeftRotation) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);  // Должен вызвать право-левый поворот
    
    auto root = tree.getRoot();
    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->left->key, 10);
    EXPECT_EQ(root->right->key, 30);
}

TEST(AVLTreeTest, ComplexOperations) {
    AVLTree<int> tree;
    // Вставка целых чисел от 0 до 99
    for (int i = 0; i < 100; ++i) {
        tree.insert(i);
    }
    // Удаление четных чисел
    for (int i = 0; i < 100; i += 2) {
        tree.remove(i);
    }
    // Проверка, остались ли нечетные числа
    for (int i = 1; i < 100; i += 2) {
        EXPECT_TRUE(tree.search(i));
    }
}