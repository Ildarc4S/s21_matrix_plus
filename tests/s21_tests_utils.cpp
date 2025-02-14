#include "./s21_tests.h"

    S21Matrix CreateTestMatrix(const std::vector<std::vector<double>>& data) {
        S21Matrix m(data.size(), data.empty() ? 0 : data[0].size());
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[i].size(); ++j) {
                m(i, j) = data[i][j];
            }
        }
        return m;
    }

S21Matrix CreateIdentity(int size) {
        S21Matrix m(size, size);
        for (int i = 0; i < size; ++i) {
            m(i, i) = 1.0;
        }
        return m;
    }
S21Matrix Identity(int size) {
    S21Matrix result(size, size);
    for (int i = 0; i < size; ++i) {
        result(i, i) = 1.0;
    }
  return result;
}


S21Matrix GenerateRandomInvertibleMatrix(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Matrix size must be positive");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    S21Matrix matrix(size, size);

    for (int i = 0; i < size; ++i) {
        matrix(i, i) = dist(gen);
        while (std::abs(matrix(i, i)) < 1e-3) {
            matrix(i, i) = dist(gen);
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                matrix(i, j) = dist(gen);
            }
        }
    }

    return matrix;
}

