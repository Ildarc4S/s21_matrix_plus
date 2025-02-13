#include "./s21_matrix_oop.h"

#include <iostream>

void printMatrix(const S21Matrix& matrix) {
  std::cout << std::endl;
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      std::cout << matrix(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

void fillRandomNum(S21Matrix* matrix) {
  for (int i = 0; i < matrix->GetRows(); i++) {
    for (int j = 0; j < matrix->GetCols(); j++) {
      (*matrix)(i, j) = static_cast<double>(rand() % 100);
    }
  }
}

int main() {
  srand(time(nullptr));
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  S21Matrix F(3, 3);

  fillRandomNum(&A);
  fillRandomNum(&B);
  fillRandomNum(&C);
  fillRandomNum(&F);

  printMatrix(A);
  printMatrix(B);
  printMatrix(C);
  printMatrix(F);

  std::cout << "\n";
  std::cout << A.Determinant();
  std::cout << "\n";

  S21Matrix G = B.Transpose();
  printMatrix(G);

  S21Matrix D = C.CalcComplements();
  printMatrix(D);


  S21Matrix E = F.InverseMatrix();
  printMatrix(E);

  return 0;
}
