#include "./s21_matrix_oop.h"
#include <utility>

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

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
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

double& S21Matrix::operator()(int row, int col) & {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw "Matrix Size Error";
  }

  return matrix_[row][col];
}

double S21Matrix::operator()(int row, int col) const & {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw "Matrix Size Error";
  }

  return matrix_[row][col];
}

