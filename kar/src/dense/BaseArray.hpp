#ifndef BASEARRAY_HPP
#define BASEARRAY_HPP

#include <array>
#include <cassert>
#include <cstddef>

namespace kar {
namespace container {

template <typename TYPE, std::size_t... DIMS_SEQ> class Array {
public:
  static constexpr std::size_t rank = sizeof...(DIMS_SEQ);
  static constexpr std::size_t size = (std::size_t(1) * ... * DIMS_SEQ);

  static constexpr std::array<TYPE, rank> shape{DIMS_SEQ...};
  static constexpr std::array<TYPE, rank> stride_element = []() {
    std::array<TYPE, rank> s{};
    if constexpr (rank == 0)
      return s;

    s[rank - 1] = 1;
    for (std::size_t i = rank - 1; i-- > 0;)
      s[i] = s[i + 1] * shape[i + 1];

    return s;
  };

  static constexpr std::array<TYPE, rank> stride_byte = []() {
    std::size_t byte = sizeof(TYPE);
    std::array<TYPE, rank> s{};
    if constexpr (rank == 0)
      return s;

    s[rank - 1] = byte;
    for (std::size_t i = rank - 1; i-- < rank;)
      s[i] = shape[i - 1] * s[i - 1];

    return s;
  };

private:
  std::array<TYPE, size> data;

  static constexpr std::size_t
  lexicographic(std::array<std::size_t, rank> idx) {
    if constexpr (rank == 0)
      return 0;

#ifndef NDEBUG
    for (std::size_t i = 0; i < rank; ++i)
      assert(idx[i] < shape[i]);
#endif // !NDEBUG
    std::size_t offside = 0;
    for (std::size_t i = 0; i < rank; ++i)
      offside += idx[i] * stride_element[i];

    return offside;
  }
};

} // namespace container
} // namespace kar

#endif // !BASEARRAY_HPP
