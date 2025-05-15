// Copyright 2024 Anvar
#include "../lib_dsu/dsu.h"
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include "../gtest/gtest.h"
#include <stdexcept>
#include <iostream>

TEST(DSU, TestMakeSet) {
    DSU<int> dsu(10);
    dsu.make_set(5);
    EXPECT_EQ(dsu.find(5), 5);
}

TEST(DSU, TestFind) {
    DSU<int> dsu(10);
    dsu.make_set(5);
    dsu.make_set(6);
    dsu.union_sets(5, 6);
    EXPECT_EQ(dsu.find(5), dsu.find(6));
}

TEST(DSU, TestUnionSets) {
    DSU<int> dsu(10);
    dsu.make_set(1);
    dsu.make_set(2);
    dsu.make_set(3);
    dsu.union_sets(1, 2);
    dsu.union_sets(2, 3);
    EXPECT_EQ(dsu.find(1), dsu.find(2));
    EXPECT_EQ(dsu.find(2), dsu.find(3));
}

TEST(DSU, TestClear) {
    DSU<int> dsu(10);
    dsu.make_set(1);
    dsu.make_set(2);
    dsu.union_sets(1, 2);
    dsu.clear();
    EXPECT_THROW(dsu.find(1), std::logic_error);
}

TEST(DSU, TestOutOfRange) {
    DSU<int> dsu(10);
    EXPECT_THROW(dsu.find(10), std::logic_error);
}
