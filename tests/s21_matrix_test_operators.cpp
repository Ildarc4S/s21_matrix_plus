#include "./s21_tests.h"

// *********** Operator + *********** //

TEST(MatrixPlus, NormalAddition) {
    S21Matrix a = CreateTestMatrix({{1,2}, {3,4}});
    S21Matrix b = CreateTestMatrix({{5,6}, {7,8}});
    EXPECT_TRUE((a + b) == CreateTestMatrix({{6,8}, {10,12}}));
}

TEST(MatrixPlus, EmptyMatrices) {
    S21Matrix a(0,0), b(0,0);
    EXPECT_NO_THROW(a + b);
}

TEST(MatrixPlus, NegativeValues) {
    S21Matrix a = CreateTestMatrix({{-1,-2}});
    S21Matrix b = CreateTestMatrix({{3,4}});
    EXPECT_TRUE((a + b) == CreateTestMatrix({{2,2}}));
}

TEST(MatrixPlus, DecimalPrecision) {
    S21Matrix a = CreateTestMatrix({{0.1,0.2}});
    S21Matrix b = CreateTestMatrix({{0.3,0.4}});
    S21Matrix res = a + b;
    EXPECT_NEAR(res(0,0), 0.4, 1e-9);
}

TEST(MatrixPlus, SizeMismatch) {
    S21Matrix a(2,3), b(3,3);
    EXPECT_THROW(a + b, std::logic_error);
}

TEST(MatrixPlus, SelfAddition) {
    S21Matrix a = CreateTestMatrix({{5,5}});
    EXPECT_TRUE((a + a) == CreateTestMatrix({{10,10}}));
}

TEST(MatrixPlus, ZeroMatrix) {
    S21Matrix a(2,2), z(2,2);
    EXPECT_TRUE((a + z) == a);
}

TEST(MatrixPlus, LargeNumbers) {
    S21Matrix a = CreateTestMatrix({{1e18}});
    S21Matrix b = CreateTestMatrix({{2e18}});
    S21Matrix c = a + b;
    EXPECT_DOUBLE_EQ(c(0,0), 3e18);
}

TEST(MatrixPlus, ResultImmutability) {
    S21Matrix a = CreateTestMatrix({{1,1}});
    S21Matrix b = CreateTestMatrix({{2,2}});
    S21Matrix c = a + b;
    a(0,0) = 100;
    EXPECT_EQ(c(0,0), 3.0);
}

// *************** Operator - *************** //
TEST(MatrixMinus, NormalSubtraction) {
    S21Matrix a = CreateTestMatrix({{5,6}, {7,8}});
    S21Matrix b = CreateTestMatrix({{1,2}, {3,4}});
    EXPECT_TRUE((a - b) == CreateTestMatrix({{4,4}, {4,4}}));
}

TEST(MatrixMinus, NegativeResult) {
    S21Matrix a = CreateTestMatrix({{1,2}});
    S21Matrix b = CreateTestMatrix({{3,4}});
    EXPECT_TRUE((a - b) == CreateTestMatrix({{-2,-2}}));
}

TEST(MatrixMinus, EmptyMatrices) {
    S21Matrix a(0,0), b(0,0);
    EXPECT_NO_THROW(a - b);
}

TEST(MatrixMinus, DecimalPrecision) {
    S21Matrix a = CreateTestMatrix({{0.5,1.5}});
    S21Matrix b = CreateTestMatrix({{0.2,0.7}});
    S21Matrix res = a - b;
    EXPECT_NEAR(res(0,0), 0.3, 1e-9);
}

TEST(MatrixMinus, SizeMismatch) {
    S21Matrix a(3,2), b(2,2);
    EXPECT_THROW(a - b, std::logic_error);
}

TEST(MatrixMinus, ZeroMatrix) {
    S21Matrix a = CreateTestMatrix({{2,2}});
    S21Matrix z(1,2);
    EXPECT_TRUE((a - z) == a);
}

TEST(MatrixMinus, LargeNumbers) {
    S21Matrix a = CreateTestMatrix({{3e18}});
    S21Matrix b = CreateTestMatrix({{1e18}});
    S21Matrix c = a - b;
    EXPECT_DOUBLE_EQ(c(0, 0), 2e18);
}

TEST(MatrixMinus, ResultImmutability) {
    S21Matrix a = CreateTestMatrix({{5,5}});
    S21Matrix b = CreateTestMatrix({{2,2}});
    S21Matrix c = a - b;
    a(0,0) = 100;
    EXPECT_EQ(c(0,0), 3.0);
}

// *************** Operator * *************** //
TEST(MatrixMultiply, MatrixMultiplication) {
    S21Matrix a = CreateTestMatrix({{1,2}, {3,4}});
    S21Matrix b = CreateTestMatrix({{5,6}, {7,8}});
    EXPECT_TRUE((a * b) == CreateTestMatrix({{19,22}, {43,50}}));
}

TEST(MatrixMultiply, ByZero) {
    S21Matrix a = CreateTestMatrix({{1,2}, {3,4}});
    EXPECT_TRUE((a * 0) == S21Matrix(2,2));
}

TEST(MatrixMultiply, ByOne) {
    S21Matrix a = CreateTestMatrix({{1.5,2.5}});
    EXPECT_TRUE((a * 1) == a);
}

TEST(MatrixMultiply, DecimalMultiplier) {
    S21Matrix a = CreateTestMatrix({{2,4}});
    EXPECT_TRUE((a * 0.5) == CreateTestMatrix({{1,2}}));
}

TEST(MatrixMultiply, IncompatibleSizes) {
    S21Matrix a(2,3), b(2,3);
    EXPECT_THROW(a * b, std::logic_error);
}

TEST(MatrixMultiply, IdentityMatrix) {
    S21Matrix a = CreateTestMatrix({{1,2}, {3,4}});
    S21Matrix i = CreateIdentity(2);
    EXPECT_TRUE((a * i) == a);
}

TEST(MatrixMultiply, FriendOperator) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix res = 2.5 * a;
    EXPECT_TRUE(res == CreateTestMatrix({{2.5, 5.0}}));
}

TEST(MatrixMultiply, MoveSemantics) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix res = std::move(a) * 3;
    EXPECT_EQ(res(0, 0), 3.0);
}

TEST(MatrixMultiply, LargeValues) {
    S21Matrix a(1, 1), b(1, 1);
    a(0,0) = 1e100;
    b(0,0) = 2.0;
    S21Matrix res = a * b;
    EXPECT_DOUBLE_EQ(res(0,0), 2e100);
}

TEST(MatrixMultiply, ResultImmutability) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix b = CreateTestMatrix({{3}, {4}});
    S21Matrix c = a * b;
    a(0, 0) = 100;
    EXPECT_EQ(c(0, 0), 11.0);
}

// *************** Operator += *************** //

TEST(MatrixPlusAssign, NormalAddition) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    a += CreateTestMatrix({{5, 6}, {7, 8}});
    EXPECT_TRUE(a == CreateTestMatrix({{6, 8}, {10, 12}}));
}

TEST(MatrixPlusAssign, EmptyMatrices) {
    S21Matrix a(0, 0), b(0, 0);
    EXPECT_NO_THROW(a += b);
}

TEST(MatrixPlusAssign, NegativeValues) {
    S21Matrix a = CreateTestMatrix({{-1, -2}});
    a += CreateTestMatrix({{3, 4}});
    EXPECT_TRUE(a == CreateTestMatrix({{2, 2}}));
}

TEST(MatrixPlusAssign, DecimalPrecision) {
    S21Matrix a = CreateTestMatrix({{0.1, 0.2}});
    a += CreateTestMatrix({{0.3, 0.4}});
    EXPECT_NEAR(a(0, 0), 0.4, 1e-9);
}

TEST(MatrixPlusAssign, SizeMismatch) {
    S21Matrix a(2, 3), b(3, 2);
    EXPECT_THROW(a += b, std::logic_error);
}

TEST(MatrixPlusAssign, SelfAddition) {
    S21Matrix a = CreateTestMatrix({{5, 5}});
    a += a;
    EXPECT_TRUE(a == CreateTestMatrix({{10, 10}}));
}

TEST(MatrixPlusAssign, ChainOperation) {
    S21Matrix a = CreateTestMatrix({{1, 1}});
    (a += CreateTestMatrix({{2, 2}})) += CreateTestMatrix({{3, 3}});
    EXPECT_TRUE(a == CreateTestMatrix({{6, 6}}));
}

TEST(MatrixPlusAssign, MoveSemantics) {
    S21Matrix a = CreateTestMatrix({{1}});
    S21Matrix b(1, 1);
    b(0,0) = 3;
    S21Matrix&& moved = std::move(a);
    moved += b;
    EXPECT_EQ(moved(0, 0), 4);
}

TEST(MatrixPlusAssign, ZeroMatrix) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix z(1, 2);
    a += z;
    EXPECT_TRUE(a == CreateTestMatrix({{1, 2}}));
}

TEST(MatrixPlusAssign, LargeNumbers) {
    S21Matrix a = CreateTestMatrix({{1e18}});
    a += CreateTestMatrix({{2e18}});
    EXPECT_DOUBLE_EQ(a(0, 0), 3e18);
}
// *************** Operator -= *************** //
TEST(MatrixMinusAssign, NormalSubtraction) {
    S21Matrix a = CreateTestMatrix({{5, 6}, {7, 8}});
    a -= CreateTestMatrix({{1, 2}, {3, 4}});
    EXPECT_TRUE(a == CreateTestMatrix({{4, 4}, {4, 4}}));
}

TEST(MatrixMinusAssign, NegativeResult) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    a -= CreateTestMatrix({{3, 4}});
    EXPECT_TRUE(a == CreateTestMatrix({{-2, -2}}));
}

TEST(MatrixMinusAssign, EmptyMatrices) {
    S21Matrix a(0, 0), b(0, 0);
    EXPECT_NO_THROW(a -= b);
}

TEST(MatrixMinusAssign, DecimalPrecision) {
    S21Matrix a = CreateTestMatrix({{0.5, 1.5}});
    a -= CreateTestMatrix({{0.2, 0.7}});
    EXPECT_NEAR(a(0, 0), 0.3, 1e-9);
}

TEST(MatrixMinusAssign, SizeMismatch) {
    S21Matrix a(3, 2), b(2, 2);
    EXPECT_THROW(a -= b, std::logic_error);
}

TEST(MatrixMinus, SelfSubtraction) {
    S21Matrix a = CreateTestMatrix({{5, 6}, {7, 8}});
    S21Matrix result = a - a;
    S21Matrix expected(2, 2);
    EXPECT_TRUE(result == expected);
}


TEST(MatrixMinusAssign, ChainOperation) {
    S21Matrix a = CreateTestMatrix({{10, 10}});
    (a -= CreateTestMatrix({{3, 3}})) -= CreateTestMatrix({{2, 2}});
    EXPECT_TRUE(a == CreateTestMatrix({{5, 5}}));
}


TEST(MatrixMinusAssign, ZeroMatrix) {
    S21Matrix a = CreateTestMatrix({{2, 2}});
    S21Matrix z(1, 2);
    a -= z;
    EXPECT_TRUE(a == CreateTestMatrix({{2, 2}}));
}

TEST(MatrixMinusAssign, LargeNumbers) {
    S21Matrix a = CreateTestMatrix({{3e18}});
    a -= CreateTestMatrix({{1e18}});
    EXPECT_DOUBLE_EQ(a(0, 0), 2e18);
}

// *************** Operator *= *************** //

TEST(MatrixMultiplyAssign, MatrixMultiplication) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    a *= CreateTestMatrix({{5, 6}, {7, 8}});
    EXPECT_TRUE(a == CreateTestMatrix({{19, 22}, {43, 50}}));
}

TEST(MatrixMultiplyAssign, IdentityMatrix) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix i = CreateIdentity(2);
    a *= i;
    EXPECT_TRUE(a == CreateTestMatrix({{1, 2}, {3, 4}}));
}

TEST(MatrixMultiplyAssign, EmptyMatrices) {
    S21Matrix a(0, 0), b(0, 0);
    EXPECT_NO_THROW(a *= b);
}

TEST(MatrixMultiplyAssign, IncompatibleSizes) {
    S21Matrix a(2, 3), b(2, 3);
    EXPECT_THROW(a *= b, std::logic_error);
}

TEST(MatrixMultiplyAssign, ResultToZero) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    a *= S21Matrix(2, 2);
    EXPECT_TRUE(a == S21Matrix(1, 2));
}

TEST(MatrixMultiplyAssign, ChainOperation) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    a *= CreateTestMatrix({{3}, {4}});  // 1x2 * 2x1 = 1x1
    a *= CreateTestMatrix({{5}});       // 1x1 * 1x1 = 1x1
    EXPECT_DOUBLE_EQ(a(0, 0), 55.0);   // (1*3 + 2*4) * 5 = 11 * 5 = 55
}


TEST(MatrixMultiplyAssign, LargeMatrixes) {
    S21Matrix a(100, 100), b(100, 100);
    a.MulNumber(1.0);
    b.MulNumber(2.0);
    a *= b;
    EXPECT_DOUBLE_EQ(a(99, 99), 0.0);  
}

TEST(MatrixMultiplyAssign, PrecisionLoss) {
    S21Matrix a = CreateTestMatrix({{0.1}});
    a *= CreateTestMatrix({{0.2}});
    EXPECT_NEAR(a(0, 0), 0.02, 1e-9);
}

// *************** Operator *= with number *************** //

TEST(MatrixMultiplyAssign, ScalarMultiplication) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    a *= 2.5;
    EXPECT_TRUE(a == CreateTestMatrix({{2.5, 5.0}, {7.5, 10.0}}));
}

TEST(MatrixMultiplyAssign, MultiplyByZero) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    a *= 0;
    EXPECT_TRUE(a == S21Matrix(2, 2));
}

TEST(MatrixMultiplyAssign, NegativeScalar) {
    S21Matrix a = CreateTestMatrix({{1.5, -2.5}});
    a *= -2.0;
    EXPECT_TRUE(a == CreateTestMatrix({{-3.0, 5.0}}));
}

TEST(MatrixMultiplyAssign, ChainScalar) {
    S21Matrix a = CreateTestMatrix({{2, 4}});
    (a *= 0.5) *= 3;
    EXPECT_TRUE(a == CreateTestMatrix({{3, 6}}));
}

TEST(MatrixMultiplyAssign, EmptyMatrix) {
    S21Matrix a(0, 0);
    EXPECT_NO_THROW(a *= 5.0);
}

TEST(MatrixMultiplyAssign, LargeScalar) {
    S21Matrix a = CreateTestMatrix({{1e100}});
    a *= 2.0;
    EXPECT_DOUBLE_EQ(a(0, 0), 2e100);
}

TEST(MatrixMultiplyAssign, MoveSemanticsScalar) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    a = std::move(a) * 3;
    EXPECT_DOUBLE_EQ(a(0, 0), 3.0);
}

TEST(MatrixMultiplyAssign, PrecisionScalar) {
    S21Matrix a = CreateTestMatrix({{0.1}});
    a *= 3.0;
    EXPECT_NEAR(a(0, 0), 0.3, 1e-9);
}

TEST(MatrixMultiplyAssign, DecimalScalar) {
    S21Matrix a = CreateTestMatrix({{2, 4}});
    a *= 0.25;
    EXPECT_TRUE(a == CreateTestMatrix({{0.5, 1.0}}));
}

TEST(MatrixMultiplyAssign, CombinedOperations) {
    S21Matrix a = CreateTestMatrix({{5, 5}});
    ((a *= 2) += CreateTestMatrix({{5, 5}})) *= 0.5;
    EXPECT_TRUE(a == CreateTestMatrix({{7.5, 7.5}}));
}

TEST(MatrixAccess, ConstOperator) {
    const S21Matrix m = CreateTestMatrix({{1, 2}, {3, 4}});
    EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

