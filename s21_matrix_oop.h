#pragma once

class S21Matrix {
 private:
    // Attributes
    int rows_, cols_;   // Rows and columns
    double **matrix_;   // Pointer to the memory where the matrix is allocated

    void CopyMatrix(const S21Matrix& other);
    void CallOperations(const S21Matrix& other,
                        double (*operation)(const double&, const double&));

    void FreeMatrix();

 public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);

    ~S21Matrix();

    int GetMaxInColumn(int column) const;
    void SwapRows(int row_one, int row_two);

    void TriangulateProcess(int curr_column);
    int TriangulateMatrix(int *swap_count);
    S21Matrix CreateMinor(const int skip_row, const int skip_column) const;

    int GetRows() const {
      return rows_;
    }

    int GetCols() const {
      return cols_;
    }

      bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);

    S21Matrix Transpose() const;
    S21Matrix CalcComplements() const;
    double Determinant() const;
    S21Matrix InverseMatrix() const;

    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(const double num);

    bool operator==(const S21Matrix& other);
    S21Matrix& operator=(S21Matrix&& other);
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);

    double operator()(int row, int col) const &;
    double operator()(int row, int col) const && = delete;

    double& operator()(int row, int col) &;
    double operator()(int row, int col) && = delete;
};

