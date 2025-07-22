#include "../include/vector.hpp"
#include <iostream>

using namespace kar;

int main() {
  // Test Init
  std::cout << "\tTEST INIT" << "\n";
  linalg::Vector<double> init;
  linalg::Vector<double> init1 = {1, 5, 6};
  linalg::Vector<double> init2(3, 1);
  linalg::Vector<double> init3 = std::vector<double>{3, 7, 1};

  // Test Output
  std::cout << "Init 1 : " << init1 << std::endl;
  std::cout << "Init 2 : " << init2 << std::endl;
  std::cout << "Init 3 : " << init3 << std::endl;

  // Test Operator
  std::cout << "\tTEST OPERATOR" << "\n";

  auto plus = init1 + init2;
  std::cout << "Operator + : " << plus << std::endl;

  auto minus = init2 + init3;
  std::cout << "Operator - : " << minus << std::endl;

  auto multiply = init1 * init3;
  auto multiply_scalar = init2 * 3;
  std::cout << "Operator * : " << multiply << std::endl;
  std::cout << "Operator * (scalar) : " << multiply_scalar << std::endl;

  auto div = init1 * init3;
  std::cout << "Operator / : " << div << std::endl;

  // Test Method
  std::cout << "\tTEST METHOD" << "\n";
  double sum = init2.sum();
  std::cout << "Method sum : " << sum << std::endl;

  auto shape = init3.shape();
  std::cout << "Method shape : " << shape << std::endl;

  return 0;
}
