#pragma once

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <initializer_list>

/**
 * @file vector.hpp
 * @brief Defines a basic 1D mathematical vector class with common operations.
 */

namespace kar {
/**
 * @namespace linalg
 * @brief Namespace for linear algebra functionalities.
 */
namespace linalg {

/**
 * @class Vector
 * @brief A template class for 1-dimensional mathematical vector operations.
 * @details This class acts as a wrapper around 'std::vector' to provide
 * a convenient interface for element-wise arithmetic, scalar operations,
 * and other common vector manipulations.
 * @tparam T The numeric type of the vector's elements. recommends ('float', 'double').
 */
template <typename T> class Vector {
public:
/**
 * @brief Constructs a Vector object to handle initialization basic.
 * @example Vector<int> v;
 */
  Vector() {}

  /**
   * @brief Constructsa Vector obkect to handle initialization 'std::vector'.
   * @example Vector<int> v = std::vector<int>{1,2,3};
   */
  Vector(const std::vector<T> &X) : vector_(X) {}

  /**
   * @brief Constructs a Vector object to handle initialization with assignment (=).
   * @param X An 'std::initializer_list' used to initialize the internal data.
   * @example Vector<int> v = {1, 2, 3};
   */
  Vector(const std::initializer_list<T> &X) : vector_(X) {}

  /**
   * @brief Constructs a Vector object to handle initialization size.
   * @detail each element 'vector_' will be defined as 0.
   * @param size An 'size_t' used reserve a vector.
   * @example Vector<int> v(5);
   */
  Vector(const size_t &size) : vector_(size, T{}) {}

  /**
   * @brief Overloads the stream insertion operator '<<' for formatted output.
   * @param out The output stream (e.g., 'std::cout').
   * @param A The Vector object to print.
   * @return A reference to the output stream.
   */
  friend std::ostream &operator<<(std::ostream &out, const Vector &A) {
    size_t precision_before = out.precision();
    out.precision(8);

    out << "| ";
    size_t size_vector = A.vector_.size();
    for (size_t i = 0; i < size_vector; ++i) {
      out << A.vector_[i];
      if (i != size_vector - 1) {
        out << "   ";
      }
    }

    out << " |" << std::endl;
    out.precision(precision_before);

    return out;
  }

  /**
   * @brief Accesses an element at a specific index (HANDLE MODIFICATION).
   * @param i The zero-based index of the element.
   * @return The value of the element at index 'i'.
   */
  T &operator[](const size_t &i) { return vector_[i]; }

  /**
   * @brief Accesses an element at a specific index (HANDLE READ ONLY).
   * @param i The zero-based index of the element.
   * @return The value of the element at index 'i'.
   */
  const T &operator[](const size_t &i) const { return vector_[i]; }
 
  /**
   * @brief Performs element-wise vector addition.
   * @param other The vector to add to this vector.
   * @return A new 'Vector' object containing the sum.
   * @note The program will terminate if the vectors have different sizes.
   */
  Vector operator+(const Vector<T> &other) const {
    checkSize_(other);

    std::vector<T> vector_sum;
    vector_sum.reserve(vector_.size());
    for (size_t i = 0; i < vector_.size(); ++i) {
      vector_sum.push_back(vector_[i] + other.vector_[i]);
    }
    return Vector(vector_sum);
  }

  /**
   * @brief Performs element-wise vector subtraction.
   * @param other The vector to subtract from this vector.
   * @return A new 'Vector' object containing the difference.
   * @note The program will terminate if the vectors have different sizes.
   */
  Vector operator-(const Vector<T> &other) const {
    checkSize_(other);

    std::vector<T> vector_subtract;
    vector_subtract.reserve(vector_.size());
    for (size_t i = 0; i < vector_.size(); ++i) {
      vector_subtract.push_back(vector_[i] - other.vector_[i]);
    }
    return Vector(vector_subtract);
  }

  /**
   * @brief Performs scalar multiplication.
   * @param scalar The scalar value to multiply each element by.
   * @return A new 'Vector' object containing the scaled elements.
   */
  Vector operator*(const T &scalar) const {
    std::vector<T> vector_mul_scalar;
    vector_mul_scalar.reserve(vector_.size());
    for (const auto &x : vector_) {
      vector_mul_scalar.push_back(x * scalar);
    }
    return Vector(vector_mul_scalar);
  }

  /**
   * @brief Performs hadamard product.
   * @param other The vector to perfoms hadamard product from this vector.
   * @return A new 'Vector' object containing the hadamard product result.
   * @note The program will multiply v1_i * v2_i and store value to new 'Vector'.
   */
  Vector operator*(const Vector<T> &other) const {
    checkSize_(other);

    std::vector<T> hadamard_product_result;
    hadamard_product_result.reserve(vector_.size());

    for (size_t i = 0; i < vector_.size(); ++i) {
      hadamard_product_result.push_back(vector_[i] * other.vector_[i]);
    }
    return Vector(hadamard_product_result);
  }

  /**
   * @brief Performs scalar division.
   * @param scalar The scalar value to divide each element by.
   * @return A new 'Vector' object containing the result of the division.
   */
  Vector operator/(const T &scalar) const {
    std::vector<T> vector_div_scalar;
    vector_div_scalar.reserve(vector_.size());
    for (const auto &x : vector_) {
      vector_div_scalar.push_back(x / scalar);
    }
    return Vector(vector_div_scalar);
  }

  /**
   * @brief Calculates the sum of all elements in the vector.
   * @return The total sum as a scalar value of type 'T'.
   */
  T sum() const {
    T total{}; // Use brace initialization for zero-initialization
    for (const auto &x : vector_) {
      total += x;
    }
    return total;
  }

  /**
   * @brief Creates a new vector by dividing each element by the total sum.
   * @warning This method does not compute the average of elements. It performs
   * a normalization where each new element v_i = v_i / sum(v).
   * @return A new 'Vector' where each element is its original value divided by
   * the sum of all elements.
   */
  Vector proportionOfSum() const {
    T total = sum();
    std::vector<T> prop_vector;
    prop_vector.reserve(vector_.size());

    // Handle division by zero case
    if (total == T{}) {
        return Vector(std::vector<T>(vector_.size(), T{}));
    }
    
    for (const auto &x : vector_) {
      prop_vector.push_back(x / total);
    }
    return Vector(prop_vector);
  }

  /**
   * @brief Returns the shape of the vector, represented as (1, N).
   * @return A 'std::pair<size_t, size_t>' of the form (1, number_of_elements).
   */
  std::pair<size_t, size_t> shape() const {
    return std::make_pair(1, vector_.size());
  }

private:
  // @brief The underlying 'std::vector' that stores the elements.
  std::vector<T> vector_;

  /**
   * @brief Helper function to verify that two vectors have the same size.
   * @param other The vector to compare the size against.
   * @note Terminates the program with 'EXIT_FAILURE' if sizes are mismatched.
   */
  void checkSize_(const Vector<T> &other) const {
    if (vector_.size() != other.vector_.size()) {
      std::cerr << "FATAL ERROR: Vector sizes do not match for operation."
                << " Left: " << vector_.size() << ", Right: " << other.vector_.size() << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
};

} // namespace linalg
} // namespace kar
