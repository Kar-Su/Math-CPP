#include "kar/src/dense/Array.hpp"
#include <iostream>

using namespace kar;

int main() {
  auto line = nd::array<float>({1.0f, 2.2f, 3.2f, 4.4f});
  auto nest = nd::array<float>({{1.0f, 2.2f, 3.2f}, {4.1f, 5.1f, 6.4f}});
  std::cout << typeid(nest).name() << std::endl;

  using leaf = internal::base_value_t<decltype(nest)>;
  static_assert(std::is_same_v<leaf, float>, "Harus sama leaf dan nest");

  using dims_seq = internal::dims_seq<decltype(nest)>;
  static_assert(std::is_same_v<std::index_sequence<2, 3>, dims_seq>,
                "Dimensi sama");

  auto test = nd::array<int>({{1, 2, 3}, {4, 5, 6}});
  static_cast<void>(test);
  static_cast<void>(line);
  auto many = nd::array<int>({{{{{{1}}}}}});
  return 0;
}
