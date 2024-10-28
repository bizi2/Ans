// Copyright 2024 Anvar

#include "../gtest/gtest.h"
#include "../lib_vector/vector.h" 

TEST(TVectorTest, DefaultConstructor) {
    TVector<double> vec;
    EXPECT_EQ(vec.size(), 0);
}

TEST(TVectorTest, SizeConstructor) {
    TVector<double> vec(5);
    EXPECT_EQ(vec.size(), 5);
}

TEST(TVectorTest, VectorInitialization) {
    std::vector<double> values = {1.0, 2.0, 3.0};
    TVector<double> vec(values);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1.0);
    EXPECT_EQ(vec[1], 2.0);
    EXPECT_EQ(vec[2], 3.0);
}

TEST(TVectorTest, AdditionOperator) {
    TVector<double> vec1({1.0, 2.0, 3.0});
    TVector<double> vec2({4.0, 5.0, 6.0});
    TVector<double> result = vec1 + vec2;

    EXPECT_EQ(result[0], 5.0);
    EXPECT_EQ(result[1], 7.0);
    EXPECT_EQ(result[2], 9.0);
}

TEST(TVectorTest, SubtractionOperator) {
    TVector<double> vec1({4.0, 5.0, 6.0});
    TVector<double> vec2({1.0, 2.0, 3.0});
    TVector<double> result = vec1 - vec2;

    EXPECT_EQ(result[0], 3.0);
    EXPECT_EQ(result[1], 3.0);
    EXPECT_EQ(result[2], 3.0);
}

TEST(TVectorTest, ScalarMultiplication) {
    TVector<double> vec({1.0, 2.0, 3.0});
    double scalar = 2.0;
    TVector<double> result = vec * scalar;

    EXPECT_EQ(result[0], 2.0);
    EXPECT_EQ(result[1], 4.0);
    EXPECT_EQ(result[2], 6.0);
}

TEST(TVectorTest, ScalarDivision) {
    TVector<double> vec({2.0, 4.0, 6.0});
    double scalar = 2.0;
    TVector<double> result = vec / scalar;

    EXPECT_EQ(result[0], 1.0);
    EXPECT_EQ(result[1], 2.0);
    EXPECT_EQ(result[2], 3.0);
}

TEST(TVectorTest, VectorDotProduct) {
    TVector<double> vec1({1.0, 2.0, 3.0});
    TVector<double> vec2({4.0, 5.0, 6.0});
    double result = vec1 * vec2;

    EXPECT_EQ(result, 32.0); // 1*4 + 2*5 + 3*6
}

TEST(TVectorTest, EqualityOperator) {
    TVector<double> vec1({1.0, 2.0, 3.0});
    TVector<double> vec2({1.0, 2.0, 3.0});
    EXPECT_TRUE(vec1 == vec2);
}

TEST(TVectorTest, InequalityOperator) {
    TVector<double> vec1({1.0, 2.0, 3.0});
    TVector<double> vec2({4.0, 5.0, 6.0});
    EXPECT_TRUE(vec1 != vec2);
}

TEST(TVectorTest, AccessOperator) {
    TVector<double> vec({1.0, 2.0, 3.0});
    EXPECT_EQ(vec[1], 2.0);
}

TEST(TVectorTest, ParenthesesOperator) {
    TVector<double> vec({1.0, 2.0, 3.0});
    EXPECT_EQ(vec(1), 2.0); // Проверка доступа через ()
}

TEST(TVectorTest, DivisionByZero) {
    TVector<double> vec({1.0, 2.0, 3.0});
    EXPECT_THROW(vec / 0.0, std::logic_error);
}
