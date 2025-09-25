#include "kar/src/dense/BaseArray.hpp"
#include "kar/src/dense/WrapperArray.hpp"
#include <iostream>
#include <type_traits>
#include <utility>

using namespace kar;

int main() {
  auto nest = nd::arr(nd::arr(1.0f, 2.2f, 3.2f), nd::arr(4.1f, 5.1f, 6.4f));
  std::cout << typeid(nest).name() << std::endl;

  // for (int i = 0; i < 2; i++) {
  //   for (int j = 0; j < 3; j++) {
  //     std::cout << nest[i][j] << std::endl;
  //   }
  // }

  using leaf = internal::base_value_t<decltype(nest)>;
  static_assert(std::is_same_v<leaf, float>, "Harus sama leaf dan nest");

  using dims_seq = internal::dims_seq<decltype(nest)>;
  static_assert(std::is_same_v<std::index_sequence<2, 3>, dims_seq>,
                "Dimensi sama");

  return 0;
}
