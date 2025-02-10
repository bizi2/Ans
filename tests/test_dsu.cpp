#include "DSU.h"
#include <cassert>
#include <iostream>

void test_make_set() {
    DSU<int> dsu(10);
    dsu.make_set(5);
    assert(dsu.find(5) == 5);
    std::cout << "test_make_set passed" << std::endl;
}

void test_find() {
    DSU<int> dsu(10);
    dsu.make_set(5);
    dsu.make_set(6);
    dsu.union_sets(5, 6);
    assert(dsu.find(5) == dsu.find(6));
    std::cout << "test_find passed" << std::endl;
}

void test_union_sets() {
    DSU<int> dsu(10);
    dsu.make_set(1);
    dsu.make_set(2);
    dsu.make_set(3);
    dsu.union_sets(1, 2);
    dsu.union_sets(2, 3);
    assert(dsu.find(1) == dsu.find(2));
    assert(dsu.find(2) == dsu.find(3));
    std::cout << "test_union_sets passed" << std::endl;
}

void test_clear() {
    DSU<int> dsu(10);
    dsu.make_set(1);
    dsu.make_set(2);
    dsu.union_sets(1, 2);
    dsu.clear();
    try {
        dsu.find(1);
        assert(false); // Should not reach here
    } catch (const std::logic_error& e) {
        assert(true);
    }
    std::cout << "test_clear passed" << std::endl;
}

void test_out_of_range() {
    DSU<int> dsu(10);
    try {
        dsu.find(10);
        assert(false); // Should not reach here
    } catch (const std::logic_error& e) {
        assert(true);
    }
    std::cout << "test_out_of_range passed" << std::endl;
}

int main() {
    test_make_set();
    test_find();
    test_union_sets();
    test_clear();
    test_out_of_range();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}