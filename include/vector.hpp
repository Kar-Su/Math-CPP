#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ostream>


/**
* @brief 
*
* @Tparam
*
* @param
*
* @return
*/
template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &A){
  size_t precision_before = out.precision();
  out.precision(8);
  
  std::cout << "| ";
  size_t size_vector = A.size();
  for(size_t i = 0; i < size_vector; ++i){
    out << A[i];
    if (i != size_vector - 1){
      out << "  ";
    }
  }

  out << " |" << std::endl;
  out.precision(precision_before);
  
  return out;
}


template<typename T>
class Vector{
public:
  Vector(const std::vector<T> &X) : data_(X) {}
 

  friend std::ostream &operator<<(std::ostream &out, const Vector &A){
    size_t precision_before = out.precision();
    out.precision(8);
    
    std::cout << "| ";
    size_t size_vector = A.data_.size();
    for(size_t i = 0; i < size_vector; ++i){
      out << A.data_[i];
      if (i != size_vector - 1){
        out << "  ";
      }
    }

    out << " |" << std::endl;
    out.precision(precision_before);
    
    return out;
  }

  Vector operator+(const Vector<T> &other){
   checkSize_(other);

    std::vector<T> vector_sum;
    for (size_t i = 0; i < this->data_.size(); ++i){
      const T v1 = this->data_[i];
      const T v2 = other.data_[i];
      
      vector_sum.push_back(v1+v2);
    }
    return vector_sum;
  }

  Vector operator-(const Vector<T> &other){
   checkSize_(other);

    std::vector<T> vector_subtract;
    for (size_t i = 0; i < this->data_.size(); ++i){
      const T v1 = this->data_[i];
      const T v2 = other.data_[i];
      
      vector_subtract.push_back(v1-v2);
    }
    return vector_subtract;
  }

  Vector operator*(const T other){
    std::vector<T> vector_mul_scalar;
    for (size_t i = 0; i < this -> data_.size(); ++i){
      const T v = this->data_[i];
      vector_mul_scalar.push_back(v * other);
    }
    return vector_mul_scalar;
  }
  
  Vector operator/(const T other){
    std::vector<T> vector_div_scalar;
    for (size_t i = 0; i < this -> data_.size(); ++i){
      const T v = this->data_[i];
      vector_div_scalar.push_back(v / other);
    }
    return vector_div_scalar;
  }
  
  
private:
  std::vector<T> data_;

  void checkSize_(const Vector<T> &other){
    if (this->data_.size() != other.data_.size()){
      std::cerr << "ERROR in function " << __func__ <<" : ";
      std::cerr << "Size vector isn't same!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
};
