#include "vector.hpp"
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

#pragma once

namespace kar {
namespace linalg {

template <typename T> class Matrix {
public:
  Matrix() {}

  Matrix(const size_t &rows, const size_t &cols, const T val = T{})
      : shape_(std::make_pair(rows, cols)), matrix_(rows * cols, val) {}

  Matrix(const std::initializer_list<std::initializer_list<T>> &init_matrix)
      : shape_(std::make_pair(init_matrix.size(), init_matrix.begin().size())) {

    matrix_.reserve(shape_.first * shape_.second);
    for (const auto &row : matrix_) {
      matrix_.insert(matrix_.end(), row.begin(), row.end());
    }
  }



private:
  std::vector<Vector<T>> matrix_;
  std::pair<size_t, size_t> shape_;
};
} // namespace linalg
} // namespace kar
