#pragma once

class S21Matrix {
 private:
    int rows_, cols_;
    double **matrix_;

    void ResizeAndCopyMatrix(const int& new_rows, const int& new_cols) noexcept;
    void CopyMatrix(const S21Matrix& other);
    void FreeMatrix();

    int GetMaxInColumn(const int& column) const noexcept;
    void SwapRows(const int& row_one, const int& row_two) noexcept;

    void TriangulateProcess(const int& curr_column) noexcept;
    int TriangulateMatrix(int* const swap_count) noexcept;
    S21Matrix CreateMinor(const int& skip_row, const int& skip_column) const noexcept;

 public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);

    ~S21Matrix();

    int GetRows() const noexcept;
    int GetCols() const noexcept;

    void SetRows(const int& new_rows);
    void SetCols(const int& new_cols);

    bool EqMatrix(const S21Matrix& other) const;
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);

    S21Matrix Transpose() const;
    S21Matrix CalcComplements() const;
    double Determinant() const;
    S21Matrix InverseMatrix() const;

    S21Matrix operator+(const S21Matrix& other) const;
    S21Matrix operator-(const S21Matrix& other) const;
    S21Matrix operator*(const S21Matrix& other) const;
    S21Matrix operator*(const double num) const;
    friend S21Matrix operator*(const double num, const S21Matrix& other);

    S21Matrix& operator=(S21Matrix&& other);
    S21Matrix& operator=(const S21Matrix& other);
    bool operator==(const S21Matrix& other) const;
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(const double& num);

    double operator()(const int& row, const int& col) const &;
    double operator()(const int& row, const int& col) const && = delete;

    double& operator()(const int& row, const int& col) &;
    double operator()(const int& row, const int& col) && = delete;
};

