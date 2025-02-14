#include "./s21_tests.h"
//  ******** SUB MATRIX ******** //

TEST(MatrixSub, ValidSubtraction) {
    S21Matrix a = CreateTestMatrix({{5, 6}, {7, 8}});
    S21Matrix b = CreateTestMatrix({{1, 2}, {3, 4}});
    a.SubMatrix(b);
    S21Matrix expected = CreateTestMatrix({{4, 4}, {4, 4}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixSub, NegativeResult) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix b = CreateTestMatrix({{3, 4}});
    a.SubMatrix(b);
    EXPECT_DOUBLE_EQ(a(0, 0), -2.0);
}

TEST(MatrixSub, EmptyMatrices) {
    S21Matrix a(0, 0), b(0, 0);
    EXPECT_NO_THROW(a.SubMatrix(b));
}

TEST(MatrixSub, SizeMismatch) {
    S21Matrix a(2, 3), b(3, 2);
    EXPECT_THROW(a.SubMatrix(b), std::logic_error);
}

TEST(MatrixSub, SubtractFromSelf) {
    S21Matrix a = CreateTestMatrix({{1.5, 2.5}, {3.5, 4.5}});
    a.SubMatrix(a);
    S21Matrix expected(2, 2);
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixSub, LargeNumbers) {
    S21Matrix a = CreateTestMatrix({{1e18, 2e18}});
    S21Matrix b = CreateTestMatrix({{0.5e18, 1e18}});
    a.SubMatrix(b);
    EXPECT_DOUBLE_EQ(a(0, 0), 0.5e18);
}

TEST(MatrixSub, AfterResize) {
    S21Matrix a(3, 3), b(2, 2);
    a.SetRows(2);
    a.SetCols(2);
    EXPECT_NO_THROW(a.SubMatrix(b));
}

TEST(MatrixSub, MoveSemantics) {
    S21Matrix a = CreateTestMatrix({{5, 5}});
    S21Matrix b = std::move(a);
    S21Matrix c = CreateTestMatrix({{2, 2}});
    EXPECT_NO_THROW(b.SubMatrix(c));
}

TEST(MatrixSub, MixedValues) {
    S21Matrix a = CreateTestMatrix({{5.5, 6.5}});
    S21Matrix b = CreateTestMatrix({{2.2, 3.3}});
    a.SubMatrix(b);
    EXPECT_NEAR(a(0, 0), 3.3, 1e-9);
    EXPECT_NEAR(a(0, 1), 3.2, 1e-9);
}

TEST(MatrixSub, DecimalPrecision) {
    S21Matrix a = CreateTestMatrix({{0.1, 0.2}});
    S21Matrix b = CreateTestMatrix({{0.05, 0.1}});
    a.SubMatrix(b);
    EXPECT_NEAR(a(0, 0), 0.05, 1e-9);
}

// ************ MUL NUMBER  *************** //

TEST(MatrixMulNumber, MultiplyByZero) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    a.MulNumber(0);
    S21Matrix expected(2, 2);
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixMulNumber, NegativeMultiplier) {
    S21Matrix a = CreateTestMatrix({{1.5, -2.0}});
    a.MulNumber(-2.0);
    S21Matrix expected = CreateTestMatrix({{-3.0, 4.0}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixMulNumber, IdentityMultiplication) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix b = a;
    a.MulNumber(1.0);
    EXPECT_TRUE(a.EqMatrix(b));
}

TEST(MatrixMulNumber, FractionalMultiplier) {
    S21Matrix a = CreateTestMatrix({{2, 4}, {6, 8}});
    a.MulNumber(0.5);
    S21Matrix expected = CreateTestMatrix({{1, 2}, {3, 4}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixMulNumber, AfterResize) {
    S21Matrix a(3, 3);
    a.SetRows(2);
    a.MulNumber(5.0);
    EXPECT_EQ(a.GetRows(), 2);
}

TEST(MatrixMulNumber, MoveSemantics) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix b = std::move(a);
    b.MulNumber(3.0);
    EXPECT_DOUBLE_EQ(b(0, 0), 3.0);
}

TEST(MatrixMulNumber, MultiplyEmptyMatrix) {
    S21Matrix a(0, 0);
    EXPECT_NO_THROW(a.MulNumber(5.0));
}

TEST(MatrixMulNumber, PrecisionTest) {
    S21Matrix a = CreateTestMatrix({{0.1}});
    a.MulNumber(3.0);
    EXPECT_NEAR(a(0, 0), 0.3, 1e-9);
}

TEST(MatrixMulNumber, LargeMultiplier) {
    S21Matrix a = CreateTestMatrix({{1e100}});
    a.MulNumber(2.0);
    EXPECT_DOUBLE_EQ(a(0, 0), 2e100);
}

TEST(MatrixMulNumber, NegativeDecimal) {
    S21Matrix a = CreateTestMatrix({{-1.5, 2.5}});
    a.MulNumber(-0.4);
    EXPECT_NEAR(a(0, 0), 0.6, 1e-9);
    EXPECT_NEAR(a(0, 1), -1.0, 1e-9);
}

// ************** MUL MATRIX  *****************//
TEST(MatrixMul, ValidMultiplication) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix b = CreateTestMatrix({{5, 6}, {7, 8}});
    a.MulMatrix(b);
    S21Matrix expected = CreateTestMatrix({{19, 22}, {43, 50}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixMul, IdentityMatrix) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix i = CreateIdentity(2);
    a.MulMatrix(i);
    EXPECT_TRUE(a.EqMatrix(CreateTestMatrix({{1, 2}, {3, 4}})));
}

TEST(MatrixMul, ZeroMatrix) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix z(2, 2);
    a.MulMatrix(z);
    S21Matrix expected(2, 2);
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixMul, IncompatibleSizes) {
    S21Matrix a(3, 2), b(3, 2);
    EXPECT_THROW(a.MulMatrix(b), std::logic_error);
}

TEST(MatrixMul, AssociativityCheck) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix b = CreateTestMatrix({{5, 6}, {7, 8}});
    S21Matrix c = CreateTestMatrix({{9, 10}, {11, 12}});

    S21Matrix res1 = (a * b) * c;
    S21Matrix res2 = a * (b * c);
    EXPECT_TRUE(res1.EqMatrix(res2));
}

TEST(MatrixMul, MinMatrixes) {
    S21Matrix a(100, 100), b(100, 100);

    a.MulNumber(1.0);
    b.MulNumber(1.0);

    a.MulMatrix(b);

    EXPECT_DOUBLE_EQ(a(99, 99), 0.0);
}

TEST(MatrixMul, AfterResize) {
    S21Matrix a(3, 2), b(2, 4);
    a.SetCols(2);

    EXPECT_NO_THROW(a.MulMatrix(b));
}

TEST(MatrixMul, MoveSemantics) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix b = CreateTestMatrix({{3}, {4}});
    S21Matrix c = std::move(a);
    c.MulMatrix(std::move(b));
    EXPECT_DOUBLE_EQ(c(0, 0), 11.0);
}

TEST(MatrixMul, PrecisionTest) {
    S21Matrix a = CreateTestMatrix({{0.1, 0.2}});
    S21Matrix b = CreateTestMatrix({{0.3}, {0.4}});
    a.MulMatrix(b);
    EXPECT_NEAR(a(0, 0), 0.11, 1e-9);
}

TEST(MatrixMul, NonSquareMatrices) {
    S21Matrix a = CreateTestMatrix({{1, 2, 3}, {4, 5, 6}});
    S21Matrix b = CreateTestMatrix({{7, 8}, {9, 10}, {11, 12}});
    a.MulMatrix(b);
    S21Matrix expected = CreateTestMatrix({{58, 64}, {139, 154}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

// ************** EQ MATRIX *****************//
TEST(MatrixEq, EqualMatrices) {
    S21Matrix a = CreateTestMatrix({{1.5, 2.3}, {3.0, 4.0}});
    S21Matrix b = a;
    EXPECT_TRUE(a.EqMatrix(b));
}

TEST(MatrixEq, DifferentSizes) {
    S21Matrix a(2, 2), b(3, 3);
    EXPECT_FALSE(a.EqMatrix(b));
}

TEST(MatrixEq, NearThreshold) {
    S21Matrix a = CreateTestMatrix({{1.0, 2.0}});
    S21Matrix b = CreateTestMatrix({{1.0, 2.00000005}}); // Разница < 1e-7
    EXPECT_TRUE(a.EqMatrix(b));
}

TEST(MatrixEq, OverThreshold) {
    S21Matrix a = CreateTestMatrix({{1.0, 2.0}});
    S21Matrix b = CreateTestMatrix({{1.0, 2.0002}}); // Разница > 1e-7
    EXPECT_FALSE(a.EqMatrix(b));
}

TEST(MatrixEq, EmptyMatrices) {
    S21Matrix a(0, 0), b(0, 0);
    EXPECT_TRUE(a.EqMatrix(b));
}

TEST(MatrixEq, AfterModification) {
    S21Matrix a = CreateTestMatrix({{5, 5}});
    S21Matrix b = a;
    a(0, 0) = 10;
    EXPECT_FALSE(a.EqMatrix(b));
}

TEST(MatrixEq, LargeNumbers) {
    S21Matrix a = CreateTestMatrix({{1e15, 2e15}});
    S21Matrix b = CreateTestMatrix({{1e15, 2e15}});
    EXPECT_TRUE(a.EqMatrix(b));
}

TEST(MatrixEq, NegativeValues) {
    S21Matrix a = CreateTestMatrix({{-1.5, -2.5}, {-3.5, -4.5}});
    S21Matrix b = a;
    EXPECT_TRUE(a.EqMatrix(b));
}

TEST(MatrixEq, DifferentOrder) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix b = CreateTestMatrix({{3, 4}, {1, 2}});
    EXPECT_FALSE(a.EqMatrix(b));
}

TEST(MatrixEq, AfterMove) {
    S21Matrix a = CreateTestMatrix({{1.1, 2.2}});
    S21Matrix b = std::move(a);
    S21Matrix c = CreateTestMatrix({{1.1, 2.2}});
    EXPECT_TRUE(b.EqMatrix(c));
}

// ************** SUM MATRIX  *****************//
TEST(MatrixSum, ValidAddition) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix b = CreateTestMatrix({{5, 6}, {7, 8}});
    a.SumMatrix(b);
    S21Matrix expected = CreateTestMatrix({{6, 8}, {10, 12}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixSum, SizeMismatch) {
    S21Matrix a(2, 3), b(3, 2);
    EXPECT_THROW(a.SumMatrix(b), std::logic_error);
}

TEST(MatrixSum, EmptyMatrices) {
    S21Matrix a(0, 0), b(0, 0);
    EXPECT_NO_THROW(a.SumMatrix(b));
}

TEST(MatrixSum, AddToSelf) {
    S21Matrix a = CreateTestMatrix({{1.5, 2.5}, {3.5, 4.5}});
    a.SumMatrix(a);
    S21Matrix expected = CreateTestMatrix({{3.0, 5.0}, {7.0, 9.0}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixSum, AfterResize) {
    S21Matrix a(3, 3), b(3, 3);
    a.SetRows(2);
    b.SetRows(2);
    EXPECT_NO_THROW(a.SumMatrix(b));
}

TEST(MatrixSum, NegativeValues) {
    S21Matrix a = CreateTestMatrix({{5.5, -2.5}});
    S21Matrix b = CreateTestMatrix({{-3.3, 1.5}});
    a.SumMatrix(b);
    S21Matrix expected = CreateTestMatrix({{2.2, -1.0}});
    EXPECT_TRUE(a.EqMatrix(expected));
}

TEST(MatrixSum, DecimalPrecision) {
    S21Matrix a = CreateTestMatrix({{0.1, 0.2}});
    S21Matrix b = CreateTestMatrix({{0.3, 0.4}});
    a.SumMatrix(b);
    EXPECT_NEAR(a(0, 0), 0.4, 1e-9);
    EXPECT_NEAR(a(0, 1), 0.6, 1e-9);
}

TEST(MatrixSum, MoveSemantics) {
    S21Matrix a = CreateTestMatrix({{1, 2}});
    S21Matrix b = CreateTestMatrix({{3, 4}});
    S21Matrix c = std::move(a);
    EXPECT_NO_THROW(c.SumMatrix(b));
}

TEST(MatrixSum, ZeroMatrix) {
    S21Matrix a = CreateTestMatrix({{1, 2}, {3, 4}});
    S21Matrix z(2, 2);
    a.SumMatrix(z);
    EXPECT_TRUE(a.EqMatrix(CreateTestMatrix({{1, 2}, {3, 4}})));
}

TEST(MatrixSum, LargeNumbers) {
    S21Matrix a = CreateTestMatrix({{1e18, 2e18}});
    S21Matrix b = CreateTestMatrix({{3e18, 4e18}});
    a.SumMatrix(b);
    EXPECT_DOUBLE_EQ(a(0, 0), 4e18);
    EXPECT_DOUBLE_EQ(a(0, 1), 6e18);
}

// ************** *****************//
