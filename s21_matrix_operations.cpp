#include "./s21_matrix_oop.h"

#include <cmath>
#include <utility>

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  bool result_code = true;

  for (int i = 0; i < rows_ && result_code; i++) {
    for (int j = 0; j < cols_ && result_code; j++) {
      if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        result_code = false;
      }
    }
  }
  return result_code;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw "Matrix Size Error";
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
       matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw "Matrix Size Error";
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
       matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
       matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_ || rows_ != other.cols_) {
    throw "Matrix Size Error";
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = std::move(result);
}
