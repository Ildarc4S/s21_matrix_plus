#include "./s21_matrix_oop.h"
#include <cmath>
#include <utility>

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
       result.matrix_[j][i] = matrix_[i][j];
    }
  }

  return result;
}

int S21Matrix::GetMaxInColumn(int column) const {
  int max_index = column;
  for (int i = column + 1; i < rows_; i++) {
    if (std::abs(matrix_[max_index][column]) < std::abs(matrix_[i][column])) {
      max_index = i;
    }
  }
  return max_index;
}

void S21Matrix::SwapRows(int row_one, int row_two) {
  for (int i = 0; i < cols_; i++) {
    std::swap(matrix_[row_one][i], matrix_[row_two][i]);
  }
}

void S21Matrix::TriangulateProcess(int curr_column) {
  for (int j = curr_column + 1; j < rows_; j++) {
    double factor =
        matrix_[j][curr_column] / matrix_[curr_column][curr_column];
    for (int i = curr_column; i < cols_; i++) {
      matrix_[j][i] -= matrix_[curr_column][i] * factor;
    }
  }
}

int S21Matrix::TriangulateMatrix(int *swap_count) {
  int result_code = 0;
  for (int curr_column = 0; curr_column < rows_ && result_code == 0;
       curr_column++) {
    int max_in_column = GetMaxInColumn(curr_column);

    if (std::abs(matrix_[max_in_column][curr_column]) < 1e-12) {
      result_code = -1;
    } else {
      if (max_in_column != curr_column) {
        SwapRows(max_in_column, curr_column);
        ++(*swap_count);
      }
      TriangulateProcess(curr_column);
    }
  }
  return result_code;
}

S21Matrix S21Matrix::CreateMinor(const int skip_row, const int skip_column) const {
  S21Matrix result(rows_ - 1, cols_ - 1);

  for (int i = 0, row = 0; i < rows_; i++) {
    int skip = 0;
    if (i == skip_row) {
      skip = 1;
    }

    for (int j = 0, column = 0; j < cols_ && skip == 0; j++) {
      if (j != skip_column) {
        result.matrix_[row][column++] = matrix_[i][j];
      }
    }
    if (skip == 0) {
      row++;
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw "Matrix is not square";
  }

  S21Matrix temp(*this);

  int swap_count = 0;
  double result = 1.0;

  if (temp.TriangulateMatrix(&swap_count) == -1) {
    result = 0.0;
  } else {
    if (swap_count % 2 == 1) {
      result = -1.0;
    }
    for (int i = 0; i < temp.rows_; i++) {
      result *= temp.matrix_[i][i];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw "Matrix is not square";
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        double det = 0.0;
        double factor = (i + j) % 2 != 0 ? -1.0 : 1.0;

        S21Matrix minor = CreateMinor(i, j);
        det = minor.Determinant();

        result.matrix_[i][j] = det * factor;
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw "Matrix is not square";
  }

  double det = Determinant();
  if (std::abs(det) < 1e-16) {
    throw "Determinan is zero";
  }

  det = 1.0 / det;
  return Transpose().CalcComplements()*det;
}
