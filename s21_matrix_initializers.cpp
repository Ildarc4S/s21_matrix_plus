#include "./s21_matrix_oop.h"

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix()
  : rows_(0),
    cols_(0),
    matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows  < 1 || cols < 1) {
    throw "Matrix size error";
  }

  matrix_ = new double* [rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]();
  }

  rows_ = rows;
  cols_ = cols;
}

S21Matrix::S21Matrix(const S21Matrix& other)
  : S21Matrix(other.rows_, other.cols_) {
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other)
  : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

