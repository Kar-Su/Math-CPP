#ifndef WRAPPER_ARRAY_HPP
#define WRAPPER_ARRAY_HPP

#include <array>
#include <cstddef>
#include <utility>

namespace kar {
namespace internal {

// Get base value type
template <typename BASE_T> struct base_value {
  using type = BASE_T;
};
template <typename FORWARD_T, std::size_t N>
struct base_value<std::array<FORWARD_T, N>> : base_value<FORWARD_T> {};
template <typename BASE_T>
using base_value_t = typename base_value<BASE_T>::type;

// Get concate sequence
template <typename BASE_INDEX, typename FORWARD_PACK>
struct sequence_concate {};
template <typename std::size_t... BASE_INDEX, std::size_t... FORWARD_PACK>
struct sequence_concate<std::index_sequence<BASE_INDEX...>,
                        std::index_sequence<FORWARD_PACK...>> {
  using type = std::index_sequence<BASE_INDEX..., FORWARD_PACK...>;
};

// Get Dimension
template <typename BASE_DIMS> struct dimension_sequence {
  std::index_sequence<>;
};
template <typename RECURSIVE_DIMS, std::size_t N>
struct dimension_sequence<std::array<RECURSIVE_DIMS, N>> {
  using type = typename sequence_concate<
      std::index_sequence<N>,
      typename dimension_sequence<RECURSIVE_DIMS>::type>::type;
};
} // namespace internal
} // namespace kar

#endif // !WRAPPER_ARRAY.HPP
