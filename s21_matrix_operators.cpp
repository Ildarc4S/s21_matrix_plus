#include "./s21_matrix_oop.h"
#include <utility>
#include <stdexcept>
#include <algorithm>

void S21Matrix::ResizeAndCopyMatrix(const int& new_rows, const int& new_cols) noexcept {
  S21Matrix temp(new_rows, new_cols);

  int min_rows = std::min(rows_, new_rows);
  int min_cols = std::min(cols_, new_cols);
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < min_cols; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(temp);
}


void S21Matrix::FreeMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (&other != this) {
    FreeMatrix();

    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix temp(other);
  *this = std::move(temp);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
  S21Matrix temp = other * num;
  return temp;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return S21Matrix::EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  S21Matrix::SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  S21Matrix::SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  S21Matrix::MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& number) {
  S21Matrix::MulNumber(number);
  return *this;
}

double& S21Matrix::operator()(const int& row, const int& col) & {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::logic_error("Matrix Size Error");
  }

  return matrix_[row][col];
}

double S21Matrix::operator()(const int& row, const int& col) const & {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::logic_error("Matrix Size Error");
  }

  return matrix_[row][col];
}

