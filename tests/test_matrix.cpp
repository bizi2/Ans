// Copyright 2024 Anvar
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define FRIEND_TEST_CASES

#include "../gtest/gtest.h"

#include "../lib_matrix/matrix.h"

/* TEST(TUpperTriangularMatrixTest, DefaultConstructor) {
    TUpperTriangularMatrix<int> m(3);
    EXPECT_EQ(m.size(), 3);
    EXPECT_EQ(m[0][0], 0);
    EXPECT_EQ(m[1][1], 0);
    EXPECT_EQ(m[2][2], 0);
}

TEST(TUpperTriangularMatrixTest, ConstructorFromArray) {
    int arr[6] = {1, 2, 3, 4, 5, 6};
    TUpperTriangularMatrix<int> m(arr, 3);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][1], 4);
    EXPECT_EQ(m[2][2], 6);
}

TEST(TUpperTriangularMatrixTest, CopyConstructor) {
    TUpperTriangularMatrix<int> m1(3);
    m1[0][0] = 1;
    TUpperTriangularMatrix<int> m2 = m1;
    EXPECT_EQ(m1[0][0], m2[0][0]);
    EXPECT_EQ(m1[1][1], m2[1][1]);
    EXPECT_EQ(m1[2][2], m2[2][2]);
}

TEST(TUpperTriangularMatrixTest, AdditionOperator) {
    TUpperTriangularMatrix<int> m1(3);
    TUpperTriangularMatrix<int> m2(3);
    m1[0][0] = 1;
    m2[0][0] = 2;
    TUpperTriangularMatrix<int> m3 = m1 + m2;
    EXPECT_EQ(m3[0][0], 3);
    EXPECT_EQ(m3[1][1], 0);
    EXPECT_EQ(m3[2][2], 0);
}

TEST(TUpperTriangularMatrixTest, AdditionAssignmentOperator) {
    TUpperTriangularMatrix<int> m1(3);
    TUpperTriangularMatrix<int> m2(3);
    m1[0][0] = 1;
    m2[0][0] = 2;
    m1 += m2;
    EXPECT_EQ(m1[0][0], 3);
    EXPECT_EQ(m1[1][1], 0);
    EXPECT_EQ(m1[2][2], 0);
}

TEST(TUpperTriangularMatrixTest, MultiplicationOperator) {
    TUpperTriangularMatrix<int> m1(3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][1] = 3;
    TUpperTriangularMatrix<int> m2(3);
    m2[0][0] = 4;
    m2[1][1] = 5;
    TUpperTriangularMatrix<int> m3 = m1 * m2;
    EXPECT_EQ(m3[0][0], 4);
    EXPECT_EQ(m3[0][1], 10);
    EXPECT_EQ(m3[1][1], 15);
}

TEST(TUpperTriangularMatrixTest, MultiplicationByScalar) {
    TUpperTriangularMatrix<int> m(3);
    m[0][0] = 1;
    TUpperTriangularMatrix<int> result = m * 2;
    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[1][1], 0);
    EXPECT_EQ(result[2][2], 0);
}

TEST(TUpperTriangularMatrixTest, DivisionByScalar) {
    TUpperTriangularMatrix<int> m(3);
    m[0][0] = 4;
    TUpperTriangularMatrix<int> result = m / 2;
    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[1][1], 0);
    EXPECT_EQ(result[2][2], 0);
}
TEST(TUpperTriangularMatrixTest, DivisionByZeroThrowsException) {
    TUpperTriangularMatrix<int> m(3);
    m[0][0] = 4;
    EXPECT_THROW(m / 0, std::invalid_argument);
}



TEST(TUpperTriangularMatrixTest, ToUpperTriangular) {
    TDMassive<int> matrix(3);
    matrix[0][0] = -1;
    matrix[0][1] = 1;
    matrix[0][2] = 3;
    matrix[1][1] = 4;
    matrix[0][1] = 4;


    TDMassive<int> upperTriangular = to_upper_triangular(matrix, 3);

    EXPECT_EQ(upperTriangular[0][0], 1);
    EXPECT_EQ(upperTriangular[1][1], 2);
    EXPECT_EQ(upperTriangular[2][2], 3);
}
 
// Тест вывода в поток
TEST(TUpperTriangularMatrixTest, OutputStream) {
    TUpperTriangularMatrix<int> m(3);
    std::ostringstream oss;
    oss << m;
    EXPECT_EQ(oss.str(), "0 0 0 \n0 0 0 \n0 0 0 \n");
} */