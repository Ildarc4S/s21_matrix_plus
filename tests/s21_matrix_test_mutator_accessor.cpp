#include "./s21_tests.h"

TEST(MatrixGetters, GetRowsDefaultConstructor) {
    S21Matrix m;
    EXPECT_EQ(m.GetRows(), 0);
}

TEST(MatrixGetters, GetRowsAfterResizeUp) {
    S21Matrix m(2, 3);
    m.SetRows(5);
    EXPECT_EQ(m.GetRows(), 5);
}

TEST(MatrixGetters, GetRowsAfterResizeDown) {
    S21Matrix m(5, 5);
    m.SetRows(3);
    EXPECT_EQ(m.GetRows(), 3);
}

TEST(MatrixGetters, GetRowsZeroSize) {
    S21Matrix m(0, 0);
    EXPECT_EQ(m.GetRows(), 0);
}

TEST(MatrixGetters, GetRowsAfterMove) {
    S21Matrix m1(4, 4);
    S21Matrix m2 = std::move(m1);
    EXPECT_EQ(m2.GetRows(), 4);
}

TEST(MatrixGetters, GetRowsAfterCopy) {
    S21Matrix m1(3, 3);
    S21Matrix m2(m1);
    EXPECT_EQ(m2.GetRows(), 3);
}

TEST(MatrixGetters, GetRowsAfterAssignment) {
    S21Matrix m1(2, 2);
    S21Matrix m2;
    m2 = m1;
    EXPECT_EQ(m2.GetRows(), 2);
}

TEST(MatrixGetters, GetRowsAfterMulMatrix) {
    S21Matrix a(2, 3), b(3, 4);
    a.MulMatrix(b);
    EXPECT_EQ(a.GetRows(), 2);
}

TEST(MatrixGetters, GetRowsInvalidAfterMove) {
    S21Matrix m1(3, 3);
    S21Matrix m2 = std::move(m1);
    EXPECT_EQ(m1.GetRows(), 0);
}

TEST(MatrixGetters, GetRowsLargeMatrix) {
    S21Matrix m(1000, 1000);
    EXPECT_EQ(m.GetRows(), 1000);
}

// ****************** GET COLS *************** //
TEST(MatrixGetters, GetColsDefaultConstructor) {
    S21Matrix m;
    EXPECT_EQ(m.GetCols(), 0);
}

TEST(MatrixGetters, GetColsAfterResizeUp) {
    S21Matrix m(3, 2);
    m.SetCols(5);
    EXPECT_EQ(m.GetCols(), 5);
}

TEST(MatrixGetters, GetColsAfterResizeDown) {
    S21Matrix m(5, 5);
    m.SetCols(3);
    EXPECT_EQ(m.GetCols(), 3);
}

TEST(MatrixGetters, GetColsZeroSize) {
    S21Matrix m(0, 0);
    EXPECT_EQ(m.GetCols(), 0);
}

TEST(MatrixGetters, GetColsAfterMove) {
    S21Matrix m1(4, 4);
    S21Matrix m2 = std::move(m1);
    EXPECT_EQ(m2.GetCols(), 4);
}

TEST(MatrixGetters, GetColsAfterCopy) {
    S21Matrix m1(3, 3);
    S21Matrix m2(m1);
    EXPECT_EQ(m2.GetCols(), 3);
}

TEST(MatrixGetters, GetColsAfterAssignment) {
    S21Matrix m1(2, 2);
    S21Matrix m2;
    m2 = m1;
    EXPECT_EQ(m2.GetCols(), 2);
}

TEST(MatrixGetters, GetColsAfterMulMatrix) {
    S21Matrix a(2, 3), b(3, 4);
    a.MulMatrix(b);
    EXPECT_EQ(a.GetCols(), 4);
}

TEST(MatrixGetters, GetColsInvalidAfterMove) {
    S21Matrix m1(3, 3);
    S21Matrix m2 = std::move(m1);
    EXPECT_EQ(m1.GetCols(), 0);
}

TEST(MatrixGetters, GetColsLargeMatrix) {
    S21Matrix m(1000, 1000);
    EXPECT_EQ(m.GetCols(), 1000);
}

//  ***************SET ROWS ********************  //

TEST(MatrixSetters, SetRowsIncrease) {
    S21Matrix m(2, 2);
    m.SetRows(5);
    EXPECT_EQ(m.GetRows(), 5);
    EXPECT_DOUBLE_EQ(m(4, 0), 0.0);
}

TEST(MatrixAccess, SetRowsOutOfRangeAccess) {
    S21Matrix m(3, 3);

    EXPECT_THROW(m(-1, 0), std::out_of_range);
    EXPECT_THROW(m(3, 0), std::out_of_range);

    const S21Matrix& cm = m;
    EXPECT_THROW(cm(0, -1), std::out_of_range);
    EXPECT_THROW(cm(0, 3), std::out_of_range);
}

TEST(MatrixSetters, SetRowsToZero) {
    S21Matrix m(3, 3);
    m.SetRows(0);
    EXPECT_EQ(m.GetRows(), 0);
}

TEST(MatrixSetters, SetRowsSameSize) {
    S21Matrix m(4, 4);
    m.SetRows(4);
    EXPECT_EQ(m.GetRows(), 4);
}

TEST(MatrixSetters, SetRowsInvalidNegative) {
    S21Matrix m;
    EXPECT_THROW(m.SetRows(-5), std::logic_error);
}

TEST(MatrixSetters, SetRowsEmptyMatrix) {
    S21Matrix m(0, 0);
    m.SetRows(5);
    EXPECT_EQ(m.GetRows(), 5);
}

TEST(MatrixSetters, SetRowsPreserveData) {
    S21Matrix m(3, 3);
    m(2, 2) = 15.0;
    m.SetRows(4);
    EXPECT_DOUBLE_EQ(m(2, 2), 15.0);
}

TEST(MatrixSetters, SetRowsLargeValue) {
    S21Matrix m;
    m.SetRows(10000);
    EXPECT_EQ(m.GetRows(), 10000);
}

TEST(MatrixSetters, SetRowsAfterMove) {
    S21Matrix m1(3, 3);
    S21Matrix m2 = std::move(m1);
    m2.SetRows(5);
    EXPECT_EQ(m2.GetRows(), 5);
}

// **********************SET COLS******************  //
TEST(MatrixSetters, SetColsIncrease) {
    S21Matrix m(2, 2);
    m.SetCols(5);
    EXPECT_EQ(m.GetCols(), 5);
    EXPECT_DOUBLE_EQ(m(0, 4), 0.0);
}

TEST(MatrixSetters, SetColsDecrease) {
    S21Matrix m(5, 5);
    m(4, 4) = 10.0;
    m.SetCols(3);
    EXPECT_THROW(m(4, 4), std::out_of_range);
}

TEST(MatrixSetters, SetColsToZero) {
    S21Matrix m(3, 3);
    m.SetCols(0);
    EXPECT_EQ(m.GetCols(), 0);
}

TEST(MatrixSetters, SetColsSameSize) {
    S21Matrix m(4, 4);
    m.SetCols(4);
    EXPECT_EQ(m.GetCols(), 4);
}

TEST(MatrixSetters, SetColsInvalidNegative) {
    S21Matrix m;
    EXPECT_THROW(m.SetCols(-5), std::logic_error);
}

TEST(MatrixSetters, SetColsEmptyMatrix) {
    S21Matrix m(0, 0);
    m.SetCols(5);
    EXPECT_EQ(m.GetCols(), 5);
}

TEST(MatrixSetters, SetColsPreserveData) {
    S21Matrix m(3, 3);
    m(2, 2) = 15.0;
    m.SetCols(4);
    EXPECT_DOUBLE_EQ(m(2, 2), 15.0);
}

TEST(MatrixSetters, SetColsLargeValue) {
    S21Matrix m;
    m.SetCols(10000);
    EXPECT_EQ(m.GetCols(), 10000);
}

TEST(MatrixSetters, SetColsAfterMove) {
    S21Matrix m1(3, 3);
    S21Matrix m2 = std::move(m1);
    m2.SetCols(5);
    EXPECT_EQ(m2.GetCols(), 5);
}


