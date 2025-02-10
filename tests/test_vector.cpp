// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <gtest.h>
#include "../lib_vector/vector.h"

TEST(TVectorTest, DefaultConstructor) {
     TVector<int> vec;
     EXPECT_EQ(vec.size(), 0);
}
TEST(TVectorTest, FillConstructor) {
    TVector<int> vec(8, 4);
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
}
TEST(TVectorTest, ConstructorWithTwoArguments) {
  TVector<int> vec(5, 2);
  EXPECT_NE(vec.size(), 2);
  EXPECT_EQ(vec.start_index(), 2);

}
TEST(TVectorTest, Destryctor) {
    TVector<int> vec;
}
TEST(TVectorTest, PrintVector) {
    TVector<int> vec(5, 3);
    vec.print();
}
TEST(TVectorTest, algorithmEmpty) {
    TVector<int> vec;
    EXPECT_TRUE(vec.empty());
}
TEST(TVectorTest, algorithmFull) {
    TVector<int> vec(5, 0);
    EXPECT_FALSE(vec.full());

    vec.resize(5); 
    EXPECT_TRUE(vec.full());
}
TEST(TVectorTest, algorithmSize) {
    TVector<int> vec(5, 0);
    EXPECT_EQ(vec.size(), 0);
    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);
    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
}
TEST(TVectorTest, algorithmStart_index) {
    TVector<int> vec(5, 0);
    EXPECT_EQ(vec.start_index(), 0);
    vec.push_back(1);
    EXPECT_EQ(vec.start_index(), 0);
    vec.push_back(2);
    EXPECT_EQ(vec.start_index(), 0);
}
TEST(TVectorTest, algorithmData) {
    TVector<int> vec(5, 0);
    EXPECT_NE(vec.data(), nullptr);
    vec.push_back(1);
    EXPECT_NE(vec.data(), nullptr);
    vec.push_back(2);
    EXPECT_NE(vec.data(), nullptr);
}
TEST(TVectorTest, algorithmSwap) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);

    TVector<int> vec2(4, 0);
    vec2.push_back(3);
    vec2.push_back(4);
    EXPECT_EQ(vec2.size(), 2);

    vec.swap(vec2);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 3);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
}
TEST(TVectorTest, algorithmAssign) {
    TVector<int> vec(5, 1);
    EXPECT_EQ(vec.start_index(), 1);
    TVector<int> vec2(4, 0);
    EXPECT_EQ(vec2.start_index(), 0);
    vec.assign(vec2);
    EXPECT_EQ(vec.start_index(), 0);

}
TEST(TVectorTest, algorithmClear) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    EXPECT_EQ(vec.size(), 5);
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}
TEST(TVectorTest, algorithmResize) {
    TVector<int> vec(5, 0);
    EXPECT_EQ(vec.size(), 0);
    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
}
TEST(TVectorTest, algorithmPushBack) {
    TVector<int> vec(5, 0);
    vec.push_back(2);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec.size(), 1);
}
TEST(TVectorTest, algorithmPopBack) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 2);
}
TEST(TVectorTest, algorithmPushFront) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.push_front(0);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 0);
}
TEST(TVectorTest, algorithmPopFront) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.pop_front();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 2);
}
TEST(TVectorTest, algorithmInsert1) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.insert(4, 3);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[3], 4);
}
TEST(TVectorTest, algorithmReplace) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.replace(2, 5);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[2], 5);
}
TEST(TVectorTest, algorithmErase) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.erase(2, 1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 2);
}
TEST(TVectorTest, algorithmRemoveAll) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.remove_all(2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 3);
}
TEST(TVectorTest, algorithmRemoveFirst) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.remove_first(1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 2);
}
TEST(TVectorTest, algorithmRemoveLast) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.remove_last(3);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 2);
}
TEST(TVectorTest, algorithmRemoveByIndex) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    vec.remove_by_index(1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 3);
}
TEST(TVectorTest, algorithmFindAll) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 4);

    size_t* vec2 = vec.find_all(2);
    EXPECT_NE(vec2, nullptr);

    EXPECT_EQ(vec2[0], 2);
    EXPECT_EQ(vec2[1], 1);
    EXPECT_EQ(vec2[2], 2);
}
TEST(TVectorTest, algorithmFindFirst) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 4);
    vec.find_first(2);
    EXPECT_EQ(vec[0], 1);
}
TEST(TVectorTest, algorithmFindLast) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 4);
    size_t vec2 = vec.find_last(2);
    EXPECT_EQ(vec[vec2], 2);
}
TEST(TVectorTest, operatorIndexNonConst) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);

    vec[1] = 4;
    EXPECT_EQ(vec[1], 4);
}

TEST(TVectorTest, operatorIndexConst) {
    
    TVector<int> vec(3, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    const TVector<int> const_vec = vec;
    EXPECT_EQ(const_vec[0], 1);
    EXPECT_EQ(const_vec[1], 2);
    EXPECT_EQ(const_vec[2], 3);
}
TEST(TVectorTest, operatorEqually) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    TVector<int> vec2(5, 0);
    vec = vec2;
    EXPECT_EQ(vec, vec2);
}
TEST(TVectorTest, operatorPlus) {
     TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    TVector<int> vec2(5, 0);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    TVector<int> vec3 = vec + vec2;
    EXPECT_EQ(vec3.size(), 3);
    EXPECT_EQ(vec3[0], 5);
    EXPECT_EQ(vec3[1], 7);
    EXPECT_EQ(vec3[2], 9);
}
TEST(TVectorTest, operatorMinus) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    TVector<int> vec2(5, 0);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    TVector<int> vec3 = vec2 - vec;
    EXPECT_EQ(vec3.size(), 3);
    EXPECT_EQ(vec3[0], 3);
    EXPECT_EQ(vec3[1], 3);
    EXPECT_EQ(vec3[2], 3);
}
TEST(TVectorTest, operatorMinusQually) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    TVector<int> vec2(5, 0);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
 
    vec2 -= vec;
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec2[0], 3);
    EXPECT_EQ(vec2[1], 3);
    EXPECT_EQ(vec2[2], 3);
}
TEST(TVectorTest, OperatorPlusQually) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    TVector<int> vec2(5, 0);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    vec += vec2;
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 7);
    EXPECT_EQ(vec[2], 9);
}
TEST(TVectorTest, OperatorMultiplicationQually) {
    TVector<int> vec(5, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec *= 3;
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 3);
    EXPECT_EQ(vec[1], 6);
    EXPECT_EQ(vec[2], 9);


}
TEST(TVectorTest, OperatorMultiplicationQually1) {
    TVector<int> vec(10);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    TVector<int> vec2(10);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);
    vec *= vec2;
    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
    EXPECT_EQ(vec[5], 6);

}

TEST(TVectorTest, OperatorEquality) {
    TVector<int> vec1(3, 0);
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    TVector<int> vec2(3, 0);
    vec2.push_back(1);
    vec2.push_back(2);
    vec2.push_back(3);

    EXPECT_TRUE(vec1 == vec2);

    TVector<int> vec3(3, 0);
    vec3.push_back(1);
    vec3.push_back(2);
    vec3.push_back(4);

    EXPECT_FALSE(vec1 == vec3);
}

TEST(TVectorTest, OperatorInequality) {
    TVector<int> vec1(3, 0);
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    TVector<int> vec2(3, 0);
    vec2.push_back(1);
    vec2.push_back(2);
    vec2.push_back(3);

    EXPECT_FALSE(vec1 != vec2);

    TVector<int> vec3(3, 0);
    vec3.push_back(1);
    vec3.push_back(2);
    vec3.push_back(4);

    EXPECT_TRUE(vec1 != vec3);
}

TEST(TVectorTest, OperatorMultiplicationScalar) {
    TVector<int> vec(3, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    TVector<int> result = vec * 2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);
}

TEST(TVectorTest, OperatorMultiplicationScalarReverse) {
    TVector<int> vec(3, 0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    TVector<int> result = 2 * vec;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);
}
