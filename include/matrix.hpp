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

  Matrix(const Vector<T> &X) { matrix_.push_back(X); }

  Matrix(const size_t &row, const size_t &col, const T val = T{})
      : row_(row), col_(col) {

    matrix_.reserve(row);
    for (size_t i = 0; i < row; ++i) {
      matrix_.push_back(Vector<T>(std::vector<T>(col, val)));
    }
  }

  Matrix(const std::initializer_list<std::initializer_list<T>> &init_matrix)
      : row_(init_matrix.size()), col_(init_matrix.begin()->size()) {

    matrix_.reserve(row_);
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

  Vector<T> &operator[](const size_t &i) { return matrix_[i]; }

  const Vector<T> &operator[](const size_t &i) const { return matrix_[i]; }

  void push_back(const Vector<T> &rows) { matrix_.push_back(rows); }

  void reserve(const size_t &size) { matrix_.reserve(size); }

  std::pair<size_t, size_t> shape() const { return std::make_pair(row_, col_); }

  Matrix operator+(const Matrix<T> &other) const {
    checkSize_(other);

    Matrix<T> sum_matrix;
    sum_matrix.reserve(row_);
    for (size_t row = 0; row < row_; ++row) {
      sum_matrix.push_back(matrix_[row] + other.matrix_[row]);
    }
    return sum_matrix;
  }

  Matrix operator-(const Matrix<T> &other) const {
    checkSize_(other);

    Matrix<T> subtract_matrix;
    subtract_matrix.reserve(row_);
    for (size_t row = 0; row < row_; ++row) {
      subtract_matrix.push_back(matrix_[row] - other.matrix_[row]);
    }
    return subtract_matrix;
  }

  Matrix operator*(const Matrix<T> &other) const {
    checkSize_(other);

    Matrix<T> multiply_matrix;
    multiply_matrix.reserve(row_);
    for (size_t row = 0; row < row_; ++row) {
      multiply_matrix.push_back(matrix_[row] * other.matrix_[row]);
    }
    return multiply_matrix;
  }

  Matrix operator*(const T &scalar) const {
    Matrix<T> mul_scalar_matrix;
    mul_scalar_matrix.reserve(row_);
    for (size_t row = 0; row < row_; ++row) {
      mul_scalar_matrix.push_back(matrix_[row] - scalar);
    }
    return mul_scalar_matrix;
  }
  Matrix operator/(const T &scalar) const {
    Matrix<T> div_scalar_matrix;
    div_scalar_matrix.reserve(row_);
    for (size_t row = 0; row < row_; ++row) {
      div_scalar_matrix.push_back(matrix_[row] / scalar);
    }
    return div_scalar_matrix;
  }

  Matrix transpose() const {
    Matrix<T> transpose_matrix(col_, row_);

    for (size_t i = 0; i < row_; ++i) {
      for (size_t j = 0; j < col_; ++j) {
        transpose_matrix[j][i] = matrix_[i][j];
      }
    }
    return transpose_matrix;
  }

  // T determinant() const {
  //   if (row_ != col_) {
  //     std::cerr << "ERROR at " << __func__ << " : "
  //       << "not match shape!" << std::endl;
  //     std::exit(EXIT_FAILURE);
  //   }
  //
  //   if (row_ == 1) {
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
  size_t row_;
  size_t col_;

  void checkSize_(const Matrix<T> &other) const {
    if ((row_ != other.shape().first) &
        (col_ != other.shape().second)) {
      std::cerr << "FATAL ERROR: Matrix sizes do not match for operation."
                << " Row " << row_ << " -> " << other.shape().first
                << ", Col " << col_ << " -> " << other.shape().second
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
};

} // namespace linalg
} // namespace kar
