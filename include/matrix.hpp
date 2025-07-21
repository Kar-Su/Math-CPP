#pragma once

#include "vector.hpp"
#include <cstddef>
#include <cstdlib>
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
    size_t check_size = 0;
    for (const auto &rows : init_matrix) {
      if ((check_size != 0) & (check_size != rows.size())) {
        std::cerr << "INIT ERROR at " << __func__ << " : "
          << "coloumn not match!" << std::endl;
        std::exit(EXIT_FAILURE);
      }
      check_size = rows.size();
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

  size_t size() const { return matrix_.size(); }

  Vector<T> &operator[](const size_t &i) {
    return matrix_[i];
  }

  const Vector<T> &operator[](const size_t &i) const {
    return matrix_[i];
  } 

  std::pair<size_t, size_t> shape() const{
    return shape_;
  }

  

  Matrix<T> transpose() const {
    Matrix<T> transpose_matrix(shape_.second, shape_.first);

    for (size_t i = 0; i < shape_.first; ++i) {
      for (size_t j = 0; j < shape_.second; ++j) {
        transpose_matrix[j][i] = matrix_[i][j];
      }
    }
    return transpose_matrix;
  }

  // T determinant() const {
  //   if (shape_.first != shape_.second) {
  //     std::cerr << "ERROR at " << __func__ << " : "
  //       << "not match shape!" << std::endl;
  //     std::exit(EXIT_FAILURE);
  //   }
  //
  //   if (shape_.first == 1) {
  //     return matrix_[0][0];
  //   }
  //
  //   const Vector<T> VECTOR_DOMINANT = matrix_[0];
  //   return 0;
  // }

  T sum() const {
    T result_sum = 0;

    for (const auto &row : matrix_) {
      result_sum += row.sum();
    }
    return result_sum;
  }
  
  
private:
  std::vector<Vector<T>> matrix_;
  std::pair<size_t, size_t> shape_;
};
} // namespace linalg
} // namespace kar
