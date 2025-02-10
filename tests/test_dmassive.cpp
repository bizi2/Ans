// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES
#include "../gtest/gtest.h"
#include "../lib_dmassive/archive.h"
#include <../main/utilites.h>



TEST(Test_TDMassive, DefaultConstructor) {
    TDMassive<int> mas;
    EXPECT_EQ(mas.size(), 0);
    EXPECT_EQ(mas.capacity(), STEP_CAPACITY);
    EXPECT_TRUE(mas.empty());
    EXPECT_FALSE(mas.full());
    EXPECT_NE(mas.data(), nullptr);
    for (size_t i = 0; i < mas.capacity(); i++) {
        EXPECT_EQ(mas.getState(i), State::empty);
    }
}

TEST(Test_TDMassive, CopyConstructor) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    TDMassive<int> mas1(mas);
    EXPECT_EQ(mas.size(), mas1.size());
    EXPECT_EQ(mas.capacity(), mas1.capacity());
    for (size_t i = 0; i < mas.size(); i++) {
        EXPECT_EQ(mas.data()[i], mas1.data()[i]);
        EXPECT_EQ(mas.getState(i), mas1.getState(i));
    }
}

TEST(Test_TDMassive, InitializationConstructorFromArray) {
    int arr[] = {1, 2, 3};
    size_t n = 3;
    TDMassive<int> mas(arr, n);
    EXPECT_NE(mas.data(), nullptr);
    EXPECT_FALSE(mas.empty());
    for (size_t i = 0; i < mas.size(); i++) {
        EXPECT_EQ(mas.data()[i], arr[i]);
        EXPECT_EQ(mas.getState(i), State::busy);
    }
    for (size_t i = mas.size(); i < mas.capacity(); i++) {
        EXPECT_EQ(mas.getState(i), State::empty);
    }
}

TEST(Test_TDMassive, InitializationConstructorWithGivenSizeAndValue) {
    int value = 42;
    size_t n = 10;
    TDMassive<int> mas(n, value);
    EXPECT_NE(mas.data(), nullptr);
    EXPECT_FALSE(mas.empty());
    EXPECT_EQ(mas.size(), n);
    EXPECT_EQ(mas.capacity(), (n > STEP_CAPACITY) ? n : STEP_CAPACITY);
    for (size_t i = 0; i < mas.size(); i++) {
        EXPECT_EQ(mas.data()[i], value);
        EXPECT_EQ(mas.getState(i), State::busy);
    }
    for (size_t i = mas.size(); i < mas.capacity(); i++) {
        EXPECT_EQ(mas.getState(i), State::empty);
    }
}

TEST(Test_TDMassive, RangeCopyConstructor) {
    TDMassive<int> mass;
    mass.assign({1, 2});
    TDMassive<int> copy(mass, 0, 1);
    EXPECT_EQ(copy.size(), 1);
    EXPECT_EQ(copy.capacity(), STEP_CAPACITY);
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(copy.data()[i], mass.data()[i]);
        EXPECT_EQ(copy.getState(i), mass.getState(i));
    }
    for (size_t i = 2; i < copy.capacity(); ++i) {
        EXPECT_EQ(copy.getState(i), State::empty);
    }
}

TEST(Test_TDMassive, Destructor) {
    TDMassive<int> mass;
    {
        TDMassive<int> mass1;
    }
}

TEST(Test_TDMassive, empty_function) {
    TDMassive<int> mas;
    EXPECT_TRUE(mas.empty());
    mas.push_back(1);
    EXPECT_FALSE(mas.empty());
}

TEST(Test_TDMassive, full_function) {
    TDMassive<int> mas;
    EXPECT_FALSE(mas.full());
    mas.resize(STEP_CAPACITY, 1);
    EXPECT_TRUE(mas.full());
}

TEST(Test_TDMassive, get_size_function) {
    TDMassive<int> mas;
    EXPECT_EQ(mas.size(), 0);
    mas.push_back(1);
    EXPECT_EQ(mas.size(), 1);
    mas.push_back(2);
    EXPECT_EQ(mas.size(), 2);
}

TEST(Test_TDMassive, get_capacity_function) {
    TDMassive<int> mas;
    EXPECT_EQ(mas.capacity(), STEP_CAPACITY);
    mas.resize(STEP_CAPACITY + 1, 1);
    EXPECT_GT(mas.capacity(), STEP_CAPACITY);
}

TEST(Test_TDMassive, get_data_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    const int* data = mas.data();
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
}

TEST(Test_TDMassive, swap_function) {
    TDMassive<int> mass1;
    mass1.push_back(1);
    mass1.push_back(2);
    mass1.push_back(3);

    TDMassive<int> mass2;
    mass2.push_back(4);
    mass2.push_back(5);

    mass1.swap(mass2);

    EXPECT_EQ(mass1.size(), 2);
    EXPECT_EQ(mass1.data()[0], 4);
    EXPECT_EQ(mass1.data()[1], 5);

    EXPECT_EQ(mass2.size(), 3);
    EXPECT_EQ(mass2.data()[0], 1);
    EXPECT_EQ(mass2.data()[1], 2);
    EXPECT_EQ(mass2.data()[2], 3);
}

TEST(Test_TDMassive, assign_function) {
    TDMassive<int> mass1;
    TDMassive<int> mass2;
    mass1.push_back(1);
    mass1.push_back(2);
    mass1.push_back(3);
    mass1.push_back(4);
    mass2.push_back(5);
    mass2.push_back(6);
    mass2.push_back(7);
    mass2.push_back(8);
    mass1.assign(mass2);
    EXPECT_EQ(mass1.size(), mass2.size());
    EXPECT_EQ(mass1.capacity(), mass2.capacity());
    for (size_t i = 0; i < mass1.size(); ++i) {
        EXPECT_EQ(mass1.data()[i], mass2.data()[i]);
        EXPECT_EQ(mass1.getState(i), mass2.getState(i));
    }
}

TEST(Test_TDMassive, clear_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.clear();
    EXPECT_TRUE(mas.empty());
    EXPECT_EQ(mas.capacity(), STEP_CAPACITY);
}

TEST(Test_TDMassive, reserve_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);

    size_t new_capacity = 10;
    mas.reserve(new_capacity);

    EXPECT_GE(mas.capacity(), new_capacity);
    EXPECT_EQ(mas.size(), 3);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 2);
    EXPECT_EQ(mas.data()[2], 3);

    for (size_t i = 0; i < mas.size(); i++) {
        EXPECT_EQ(mas.getState(i), State::busy);
    }
}

TEST(Test_TDMassive, resize_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    size_t newSize = 5;
    int value = 42;
    mas.resize(newSize, value);
    EXPECT_EQ(mas.size(), newSize);
    EXPECT_GE(mas.capacity(), newSize);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 2);
    EXPECT_EQ(mas.data()[2], 3);
    for (size_t i = 3; i < newSize; ++i) {
        EXPECT_EQ(mas.data()[i], value);
        EXPECT_EQ(mas.getState(i), State::busy);
    }
    mas.resize(2);
    EXPECT_EQ(mas.size(), 2);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 2);
}

TEST(Test_TDMassive, push_back_function) {
    TDMassive<int> mas;
    if (mas.size() == mas.capacity()) {
        mas.reserve(mas.capacity() + STEP_CAPACITY);
    }
    int value = 42;
    mas.push_back(value);
    EXPECT_EQ(mas.size(), 1);
    EXPECT_EQ(mas.data()[0], value);
    EXPECT_EQ(mas.getState(0), State::busy);
}

TEST(Test_TDMassive, push_front_function) {
    TDMassive<int> mass(10);
    mass.push_front(1);
    mass.push_front(2);
    mass.push_front(3);

    EXPECT_EQ(mass.data()[0], 3);
    EXPECT_EQ(mass.data()[1], 2);
    EXPECT_EQ(mass.data()[2], 1);
    EXPECT_EQ(mass.size(), 3);
}

TEST(Test_TDMassive, pop_front_function) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    mass.pop_front();
    EXPECT_EQ(mass.size(), 2);
    EXPECT_EQ(mass.getState(0), State::deleted);


    mass.pop_front();
    EXPECT_EQ(mass.size(), 1);
    EXPECT_EQ(mass.getState(1), State::deleted);


}

TEST(Test_TDMassive, pop_back_function) {
    TDMassive<int> mass;
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    mass.pop_back();
    EXPECT_EQ(mass.size(), 2);
    EXPECT_EQ(mass[0], 1);
    EXPECT_EQ(mass[1], 2);

    mass.pop_back();
    EXPECT_EQ(mass.size(), 1);
    EXPECT_EQ(mass[0], 1);

    mass.pop_back();
    EXPECT_EQ(mass.size(), 0);
}

TEST(Test_TDMassive, insert_array_function) {
    int arr[] = {1, 2, 3, 4, 5};
    TDMassive<int> mas;
    mas.insert(arr, 5, 0);
    EXPECT_EQ(mas.size(), 5);
    for (size_t i = 0; i < mas.size(); ++i) {
        EXPECT_EQ(mas.data()[i], arr[i]);
    }
}

TEST(Test_TDMassive, insert_at_position_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    mas.insert(4, 2);
    EXPECT_EQ(mas.size(), 4);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 2);
    EXPECT_EQ(mas.data()[2], 4);
    EXPECT_EQ(mas.data()[3], 3);
    EXPECT_EQ(mas.getState(2), State::busy);
}

TEST(Test_TDMassive, replace_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    mas.replace(2, 4);
    EXPECT_EQ(mas.size(), 3);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 2);
    EXPECT_EQ(mas.data()[2], 4);
    EXPECT_EQ(mas.getState(2), State::busy);
}

TEST(Test_TDMassive, erase_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    mas.erase(0, 1);
    EXPECT_EQ(mas.size(), 2);
    EXPECT_EQ(mas.data()[0], 2);
    EXPECT_EQ(mas.data()[1], 3);
    EXPECT_EQ(mas.getState(1), State::busy);
}

TEST(Test_TDMassive, remove_all_function) {
    int value = 2;
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    mas.remove_all(value);
    EXPECT_EQ(mas.size(), 2);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 3);
    EXPECT_EQ(mas.getState(1), State::busy);
}

TEST(Test_TDMassive, remove_first_function) {
    int value = 2;
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    mas.push_back(2);
    mas.remove_first(value);
    EXPECT_EQ(mas.size(), 3);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 3);
    EXPECT_EQ(mas.data()[2], 2);
    EXPECT_EQ(mas.getState(1), State::busy);
}

TEST(Test_TDMassive, remove_last_function) {
    int value = 2;
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    mas.remove_last(value);
    EXPECT_EQ(mas.size(), 2);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 3);
    EXPECT_EQ(mas.getState(1), State::busy);
}

TEST(Test_TDMassive, remove_by_index_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    mas.remove_by_index(1);
    EXPECT_EQ(mas.size(), 2);
    EXPECT_EQ(mas.data()[0], 1);
    EXPECT_EQ(mas.data()[1], 3);
    EXPECT_EQ(mas.getState(1), State::busy);
}

TEST(Test_TDMassive, find_all_function) {
TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(1);
    mass.push_back(3);

    size_t* result = mass.find_all(1);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 2);
    delete[] result;

    result = mass.find_all(2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 1);
    delete[] result;

    result = mass.find_all(3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 3);
    delete[] result;
}

TEST(Test_TDMassive, find_first_function) {
    int value = 2;
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    size_t pos = mas.find_first(value);
    EXPECT_EQ(mas.getState(pos), State::busy);
}

TEST(Test_TDMassive, find_last_function) {
    int value = 2;
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);
    size_t pos = mas.find_last(value);
    EXPECT_EQ(mas.getState(pos), State::busy);
}

TEST(Test_TDMassive, get_state_function) {
    TDMassive<int> mas;
    mas.push_back(1);
    mas.push_back(2);
    mas.push_back(3);

    EXPECT_EQ(mas.getState(0), State::busy);
    EXPECT_EQ(mas.getState(1), State::busy);
    EXPECT_EQ(mas.getState(2), State::busy);
}
