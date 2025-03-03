// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES
#include "../gtest/gtest.h"
#include "../lib_merge_sorted_lists/merge_sorted_lists.h"

TEST(MergeSortedListsTest, BothListsEmpty) {
    std::list<int> list1;
    std::list<int> list2;
    std::list<int> result = mergeSortedLists(list1, list2);
    EXPECT_TRUE(result.empty());
}

TEST(MergeSortedListsTest, FirstListEmpty) {
    std::list<int> list1;
    std::list<int> list2 = {1, 3, 5};
    std::list<int> result = mergeSortedLists(list1, list2);
    std::list<int> expected = {1, 3, 5};
    EXPECT_EQ(result, expected);
}

TEST(MergeSortedListsTest, SecondListEmpty) {
    std::list<int> list1 = {2, 4, 6};
    std::list<int> list2;
    std::list<int> result = mergeSortedLists(list1, list2);
    std::list<int> expected = {2, 4, 6};
    EXPECT_EQ(result, expected);
}

TEST(MergeSortedListsTest, BothListsNonEmpty) {
    std::list<int> list1 = {1, 3, 5};
    std::list<int> list2 = {2, 4, 6};
    std::list<int> result = mergeSortedLists(list1, list2);
    std::list<int> expected = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(result, expected);
}

TEST(MergeSortedListsTest, ListsWithDuplicates) {
    std::list<int> list1 = {1, 3, 5, 7};
    std::list<int> list2 = {2, 3, 4, 6};
    std::list<int> result = mergeSortedLists(list1, list2);
    std::list<int> expected = {1, 2, 3, 3, 4, 5, 6, 7};
    EXPECT_EQ(result, expected);
}