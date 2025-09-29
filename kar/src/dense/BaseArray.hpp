#ifndef BASEARRAY_HPP
#define BASEARRAY_HPP

#include <array>
#include <cstddef>

namespace kar {
namespace container {

template <typename TYPE, std::size_t... DIMS_SEQ> class Array {
  static constexpr std::size_t rank = sizeof...(DIMS_SEQ);
  static constexpr std::size_t size = (std::size_t(1) * ... * DIMS_SEQ);

  static constexpr std::array<TYPE, rank> shape{DIMS_SEQ...};
  static constexpr std::array<TYPE, rank> stride_element = []() {
    std::array<TYPE, rank> s{};
    if constexpr (rank == 0) {
      return s;
    }
    s[rank - 1] = 1;
    for (std::size_t i = rank - 1; i-- > 0;) {
      s[i] = s[i + 1] * shape[i + 1];
    }
    return s;
  };

  static constexpr std::array<TYPE, rank> stride_byte = []() {
    std::size_t byte = sizeof(TYPE);
    std::array<TYPE, rank> s{};
    if constexpr (rank == 0) {
      return s;
    }

    s[rank - 1] = byte;
    for (std::size_t i = rank - 1; i-- < rank;) {
      s[i] = shape[i - 1] * s[i - 1];
    }
    return s;
  };
};

} // namespace container
} // namespace kar

#endif // !BASEARRAY_HPP
