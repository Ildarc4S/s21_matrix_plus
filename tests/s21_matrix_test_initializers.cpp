#include "./tests.h"

TEST(MatrixInitialization, DefaultConstructor) {
    S21Matrix m;
    EXPECT_EQ(m.GetRows(), 0);
    EXPECT_EQ(m.GetCols(), 0);
}

TEST(MatrixInitialization, ParameterizedConstructor) {
    S21Matrix m(3, 4);
    EXPECT_EQ(m.GetRows(), 3);
    EXPECT_EQ(m.GetCols(), 4);
}

TEST(MatrixInitialization, InvalidParameters) {
    EXPECT_THROW(S21Matrix(-1, 2), std::logic_error);
    EXPECT_THROW(S21Matrix(2, -3), std::logic_error);
}

TEST(MatrixInitialization, CopyConstructor) {
    S21Matrix original(2, 2);
    original(1,1) = 5.5;
    
    S21Matrix copy(original);
    EXPECT_DOUBLE_EQ(copy(1,1), 5.5);
}

TEST(MatrixInitialization, MoveConstructor) {
    S21Matrix original(3, 3);
    original(2,2) = 10.0;
    
    S21Matrix moved(std::move(original));
    EXPECT_DOUBLE_EQ(moved(2,2), 10.0);
    EXPECT_EQ(original.GetRows(), 0);
}

TEST(MatrixInitialization, ZeroInitialization) {
    S21Matrix m(2, 2);
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            EXPECT_DOUBLE_EQ(m(i,j), 0.0);
        }
    }
}

TEST(MatrixInitialization, MoveAssignment) {
    S21Matrix m1(2,2);
    S21Matrix m2 = std::move(m1);
    EXPECT_EQ(m1.GetRows(), 0);
    EXPECT_EQ(m2.GetRows(), 2);
}

TEST(MatrixInitialization, CopyAssignment) {
    S21Matrix original(1,1);
    original(0,0) = 7.7;
    
    S21Matrix copy;
    copy = original;
    EXPECT_DOUBLE_EQ(copy(0,0), 7.7);
}

TEST(MatrixInitialization, SelfAssignment) {
    S21Matrix m(2,2);
    m(0,0) = 1.1;
    m = m;
    EXPECT_DOUBLE_EQ(m(0,0), 1.1);
}
