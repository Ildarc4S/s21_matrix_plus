#pragma once

#include <gtest/gtest.h>
#include <utility>
#include <limits>
#include <vector>

#include <random>

#include "./../s21_matrix_oop.h"


S21Matrix CreateTestMatrix(const std::vector<std::vector<double>>& data);
S21Matrix Identity(int size);
S21Matrix CreateIdentity(int size);
S21Matrix GenerateRandomInvertibleMatrix(int size);

