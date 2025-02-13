#include "./s21_matrix_oop.h"

#include <cmath>
#include <utility>
#include <stdexcept>

int S21Matrix::GetRows() const noexcept {
  return rows_;
}

int S21Matrix::GetCols() const noexcept {
  return cols_;
}

void S21Matrix::SetCols(const int& new_cols) {
  if (new_cols < 0) {
    throw std::logic_error("SetCols: Cols count must be positive");
  }

  if (cols_ != new_cols) {
    ResizeAndCopyMatrix(rows_, new_cols);
  }
}

void S21Matrix::SetRows(const int& new_rows) {
  if (new_rows < 0) {
    throw std::logic_error("SetRows: Rows count must be positive");
  }

  if (cols_ != new_rows) {
    ResizeAndCopyMatrix(new_rows, cols_);
  }
}


bool S21Matrix::EqMatrix(const S21Matrix& other) const {
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
    throw std::logic_error("SumMatrix: Matrix Size Error");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
       matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("SubMatrix: Matrix Size Error");
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
    if (cols_ != other.rows_) {
        throw std::logic_error("MulMatrix: Matrix Size Error");
    }

    S21Matrix result(rows_, other.cols_);

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }

    *this = std::move(result);
}
