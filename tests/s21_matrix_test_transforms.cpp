#include "./s21_tests.h"

// *************** Transpose  *************** //

TEST(TransposeTest, SingleElement) {
    S21Matrix m(1, 1);
    m(0, 0) = 5.5;
    S21Matrix res = m.Transpose();
    EXPECT_DOUBLE_EQ(res(0,0), 5.5);
}

TEST(TransposeTest, Rectangular2x3) {
    S21Matrix m(2, 3);
    m(0,0)=1; m(0,1)=2; m(0,2)=3;
    m(1,0)=4; m(1,1)=5; m(1,2)=6;
    
    S21Matrix res = m.Transpose();
    ASSERT_EQ(res.GetRows(), 3);
    ASSERT_EQ(res.GetCols(), 2);
    EXPECT_EQ(res(0,0), 1); EXPECT_EQ(res(0,1), 4);
    EXPECT_EQ(res(1,0), 2); EXPECT_EQ(res(1,1), 5);
    EXPECT_EQ(res(2,0), 3); EXPECT_EQ(res(2,1), 6);
}

TEST(TransposeTest, ZeroMatrix5x5) {
    S21Matrix m(5, 5);
    S21Matrix res = m.Transpose();
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            EXPECT_DOUBLE_EQ(res(i,j), 0.0);
}

TEST(TransposeTest, Diagonal4x4) {
    S21Matrix m = Identity(4);
    S21Matrix res = m.Transpose();
    EXPECT_TRUE(res == m);
}

TEST(TransposeTest, Pattern10x10) {
    S21Matrix m(10, 10);
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            m(i,j) = i + j;
    
    S21Matrix res = m.Transpose();
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            EXPECT_DOUBLE_EQ(res(i,j), j + i);
}

TEST(TransposeTest, Large19x19) {
    S21Matrix m(19, 19);
    for (int i = 0; i < 19; ++i)
        for (int j = 0; j < 19; ++j)
            m(i,j) = i * 19 + j;
    
    S21Matrix res = m.Transpose();
    for (int i = 0; i < 19; ++i)
        for (int j = 0; j < 19; ++j)
            EXPECT_DOUBLE_EQ(res(i,j), j * 19 + i);
}

TEST(TransposeTest, Rectangular7x3) {
    S21Matrix m(7, 3);
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 3; ++j)
            m(i, j) = i * 3 + j;

    S21Matrix res = m.Transpose();
    ASSERT_EQ(res.GetRows(), 3);
    ASSERT_EQ(res.GetCols(), 7);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 7; ++j)
            EXPECT_DOUBLE_EQ(res(i, j), j * 3 + i);
}

TEST(TransposeTest, NegativeValues) {
    S21Matrix m(2, 2);
    m(0,0) = -1; m(0,1) = -2;
    m(1,0) = -3; m(1,1) = -4;
    
    S21Matrix res = m.Transpose();
    EXPECT_EQ(res(0,0), -1); EXPECT_EQ(res(0,1), -3);
    EXPECT_EQ(res(1,0), -2); EXPECT_EQ(res(1,1), -4);
}

TEST(TransposeTest, Identity8x8) {
    S21Matrix m = Identity(8);
    S21Matrix res = m.Transpose();
    EXPECT_TRUE(res == m);
}

TEST(TransposeTest, EmptyMatrix) {
    S21Matrix m(0, 0);
    EXPECT_NO_THROW(m.Transpose());
}
// *************** Determinant  *************** //

TEST(DeterminantTest, NonSquareMatrix) {
    S21Matrix m(3, 2); // Неквадратная матрица 3x2
    EXPECT_THROW(m.Determinant(), std::logic_error);
}

TEST(DeterminantTest, SingleElement) {
    S21Matrix m(1, 1);
    m(0,0) = 5.0;
    EXPECT_DOUBLE_EQ(m.Determinant(), 5.0);
}

TEST(DeterminantTest, Diagonal3x3) {
    S21Matrix m(3, 3);
    m(0,0)=2; m(1,1)=3; m(2,2)=4;
    EXPECT_DOUBLE_EQ(m.Determinant(), 24.0);
}

TEST(DeterminantTest, UpperTriangular4x4) {
    S21Matrix m(4, 4);
    for (int i = 0; i < 4; ++i) {
        m(i, i) = i + 1; 
        for (int j = i + 1; j < 4; ++j)
            m(i, j) = 1;
    }
    EXPECT_DOUBLE_EQ(m.Determinant(), 1 * 2 * 3 * 4); // 24
}

TEST(DeterminantTest, Zero5x5) {
    S21Matrix m(5, 5);
    EXPECT_NEAR(m.Determinant(), 0.0, 1e-12);
}

TEST(DeterminantTest, Negative2x2) {
    S21Matrix m(2, 2);
    m(0,0)=-1; m(0,1)=-2;
    m(1,0)=-3; m(1,1)=-4;
    EXPECT_DOUBLE_EQ(m.Determinant(), (-1)*(-4) - (-2)*(-3));
}

TEST(DeterminantTest, RandomInvertible6x6) {
    S21Matrix m = GenerateRandomInvertibleMatrix(6);
    double det = m.Determinant();
    EXPECT_TRUE(std::abs(det) > 1e-9);
}

TEST(InverseTest, FloatingPoint4x4) {
    S21Matrix m(4, 4);
    m(0,0) = 4.0; m(0,1) = 3.0; m(0,2) = 2.0; m(0,3) = 1.0;
    m(1,0) = 3.0; m(1,1) = 4.0; m(1,2) = 3.0; m(1,3) = 2.0;
    m(2,0) = 2.0; m(2,1) = 3.0; m(2,2) = 4.0; m(2,3) = 3.0;
    m(3,0) = 1.0; m(3,1) = 2.0; m(3,2) = 3.0; m(3,3) = 4.0;

    S21Matrix inv = m.InverseMatrix();
    S21Matrix product = m * inv;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double expected = (i == j) ? 1.0 : 0.0;
            EXPECT_NEAR(product(i, j), expected, 1e-6);
        }
    }
}

TEST(DeterminantTest, Identity10x10) {
    S21Matrix m = Identity(10);
    EXPECT_DOUBLE_EQ(m.Determinant(), 1.0);
}

TEST(DeterminantTest, LowerTriangular4x4) {
    S21Matrix m(4, 4);
    // Создаем нижнетреугольную матрицу с диагональю [2, 3, 4, 5]
    for (int i = 0; i < 4; ++i) {
        m(i, i) = i + 2; // Диагональ: 2, 3, 4, 5
        for (int j = 0; j < i; ++j) {
            m(i, j) = 1.0; // Заполняем нижний треугольник
        }
    }
    EXPECT_NEAR(m.Determinant(), 120.0, 1e-9);
}

TEST(DeterminantTest, LargeDiagonal19x19) {
    S21Matrix m = Identity(19) * 2;
    EXPECT_DOUBLE_EQ(m.Determinant(), std::pow(2, 19));
}

// *************** Calc Complements *************** //

TEST(CalcComplementsTest, SingleElement) {
    S21Matrix m(1, 1);
    m(0,0) = 5.0;
    S21Matrix res = m.CalcComplements();
    EXPECT_DOUBLE_EQ(res(0,0), 1.0);
}

TEST(CalcComplementsTest, ZeroElement3x3) {
    S21Matrix m(3, 3);
    m(0,0)=1; m(0,1)=0; m(0,2)=3;
    m(1,0)=4; m(1,1)=5; m(1,2)=6;
    m(2,0)=7; m(2,1)=8; m(2,2)=9;
    
    S21Matrix res = m.CalcComplements();
    double minor = (4*9 - 6*7);
    EXPECT_DOUBLE_EQ(res(0,1), -minor);
}

TEST(CalcComplementsTest, Negative2x2) {
    S21Matrix m(2, 2);
    m(0,0)=-1; m(0,1)=-2;
    m(1,0)=-3; m(1,1)=-4;
    
    S21Matrix res = m.CalcComplements();
    EXPECT_DOUBLE_EQ(res(0,0), -4); 
    EXPECT_DOUBLE_EQ(res(0,1), 3);
    EXPECT_DOUBLE_EQ(res(1,0), 2);
    EXPECT_DOUBLE_EQ(res(1,1), -1);
}

TEST(CalcComplementsTest, Diagonal4x4) {
    S21Matrix m = Identity(4);
    S21Matrix res = m.CalcComplements();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            EXPECT_DOUBLE_EQ(res(i,j), (i == j) ? 1.0 : 0.0);
}

TEST(CalcComplementsTest, RepeatedRows5x5) {
    S21Matrix m(5, 5);
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            m(i,j) = i; 
    
    S21Matrix res = m.CalcComplements();
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            EXPECT_NEAR(res(i,j), 0.0, 1e-9);
}

TEST(CalcComplementsTest, FloatingPoint3x3) {
    S21Matrix m(3, 3);
    m(0,0)=1.5; m(0,1)=2.5; m(0,2)=3.5;
    m(1,0)=4.5; m(1,1)=5.5; m(1,2)=6.5;
    m(2,0)=7.5; m(2,1)=8.5; m(2,2)=9.5;
    
    S21Matrix res = m.CalcComplements();
    double minor = (5.5*9.5 - 6.5*8.5);
    EXPECT_NEAR(res(0,0), minor, 1e-9);
}

TEST(CalcComplementsTest, Size6x6) {
    S21Matrix m = Identity(6);
    S21Matrix res = m.CalcComplements();
    EXPECT_EQ(res.GetRows(), 6);
    EXPECT_EQ(res.GetCols(), 6);
}

TEST(CalcComplementsTest, NonSquareMatrix) {
    S21Matrix m(2, 3);
    EXPECT_THROW(m.CalcComplements(), std::logic_error);
}

TEST(CalcComplementsTest, Large19x19) {
    S21Matrix m = Identity(19);
    S21Matrix res = m.CalcComplements();
    for (int i = 0; i < 19; ++i)
        for (int j = 0; j < 19; ++j)
            EXPECT_DOUBLE_EQ(res(i,j), (i == j) ? 1.0 : 0.0);
}

TEST(CalcComplementsTest, Singular2x2) {
    S21Matrix m(2, 2);
    m(0,0)=1; m(0,1)=2;
    m(1,0)=2; m(1,1)=4; // Строки пропорциональны
    
    S21Matrix res = m.CalcComplements();
    // Миноры для сингулярной матрицы
    EXPECT_DOUBLE_EQ(res(0,0), 4); 
    EXPECT_DOUBLE_EQ(res(0,1), -2);
    EXPECT_DOUBLE_EQ(res(1,0), -2);
    EXPECT_DOUBLE_EQ(res(1,1), 1);
}

// *************** Inverse matrix  *************** //
// 4.1 Обратная матрица для 1x1
TEST(InverseTest, SingleElement) {
    S21Matrix m(1, 1);
    m(0,0) = 5.0;
    S21Matrix inv = m.InverseMatrix();
    EXPECT_DOUBLE_EQ(inv(0,0), 0.2);
}

// 4.2 Обратная матрица для диагональной 3x3
TEST(InverseTest, Diagonal3x3) {
    S21Matrix m(3, 3);
    m(0,0)=2; m(1,1)=3; m(2,2)=4;
    S21Matrix inv = m.InverseMatrix();
    EXPECT_DOUBLE_EQ(inv(0,0), 0.5);
    EXPECT_DOUBLE_EQ(inv(1,1), 1.0/3);
    EXPECT_DOUBLE_EQ(inv(2,2), 0.25);
}

// 4.3 Умножение матрицы на обратную (2x2)
TEST(InverseTest, Multiply2x2) {
    S21Matrix m(2, 2);
    m(0,0)=1; m(0,1)=2;
    m(1,0)=3; m(1,1)=4;
    
    S21Matrix inv = m.InverseMatrix();
    S21Matrix product = m * inv;
    // Проверка на единичную матрицу
    EXPECT_NEAR(product(0,0), 1.0, 1e-9);
    EXPECT_NEAR(product(0,1), 0.0, 1e-9);
    EXPECT_NEAR(product(1,0), 0.0, 1e-9);
    EXPECT_NEAR(product(1,1), 1.0, 1e-9);
}

// 4.4 Неквадратная матрица (исключение)
TEST(InverseTest, NonSquareMatrix) {
    S21Matrix m(2, 3);
    EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

TEST(InverseTest, Singular4x4) {
    S21Matrix m(4, 4); 
    EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

TEST(InverseTest, UpperTriangular5x5) {
    S21Matrix m(5, 5);
    for (int i = 0; i < 5; ++i) {
        m(i,i) = i + 1;
        for (int j = i + 1; j < 5; ++j)
            m(i,j) = 1;
    }
    S21Matrix inv = m.InverseMatrix();
    S21Matrix product = m * inv;
    for (int i = 0; i < 5; ++i)
        EXPECT_NEAR(product(i,i), 1.0, 1e-9);
}

TEST(InverseTest, Large19x19) {
    S21Matrix m = GenerateRandomInvertibleMatrix(19);
    S21Matrix inv = m.InverseMatrix();
    S21Matrix product = m * inv;
    for (int i = 0; i < 19; ++i) {
        EXPECT_NEAR(product(i,i), 1.0, 1e-9);
        for (int j = 0; j < 19; ++j) {
            if (i != j) {
              EXPECT_NEAR(product(i,j), 0.0, 1e-9);
            }
        }
    }
}

TEST(InverseTest, Negative3x3) {
    S21Matrix m(3, 3);
    m(0,0)=-2; m(0,1)=1; m(0,2)=0;
    m(1,0)=1; m(1,1)=-2; m(1,2)=1;
    m(2,0)=0; m(2,1)=1; m(2,2)=-2;
    
    S21Matrix inv = m.InverseMatrix();
    S21Matrix product = m * inv;
    for (int i = 0; i < 3; ++i)
        EXPECT_NEAR(product(i,i), 1.0, 1e-9);
}

TEST(InverseTest, ZeroMatrix) {
    S21Matrix m(3, 3);
    EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

// *************** *************** //
// *************** *************** //
// *************** *************** //
