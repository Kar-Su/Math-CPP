#pragma once

#include "vector.hpp"
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

namespace kar {
namespace linalg {

template <typename T> class Matrix {
public:
  Matrix() {}

  Matrix(const size_t &row, const size_t &col, const T val = T{})
      : shape_(std::make_pair(row, col)){

    matrix_.reserve(row);
    for (size_t i = 0; i < row; ++i){
      matrix_.push_back(Vector<T>(std::vector<T>(col, val)));
    }
  }

  Matrix(const std::initializer_list<std::initializer_list<T>> &init_matrix)
      : shape_(std::make_pair(init_matrix.size(), init_matrix.begin()->size())) {

    matrix_.reserve(shape_.first);
    for (const auto &rows : init_matrix) {
      matrix_.push_back(Vector<T>(rows));
    }
  }

  friend std::ostream &operator<<(std::ostream &out, Matrix<T> &A) {
   size_t precision_before = out.precision();
    out.precision(8);
    
    for (const auto &rows : A.matrix_) {
      out << rows;
    }

    out.precision(precision_before);
    return out;
  }

  std::pair<size_t, size_t> shape() const{
    return shape_;
  }
private:
  std::vector<Vector<T>> matrix_;
  std::pair<size_t, size_t> shape_;
};
} // namespace linalg
} // namespace kar
