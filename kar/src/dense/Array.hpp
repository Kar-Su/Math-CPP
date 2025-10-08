#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "BaseArray.hpp"
#include "UnpackArray.hpp"
#include <array>
#include <cstddef>
#include <utility>

namespace kar {
namespace nd {

template <typename... VALUE_T> constexpr auto arr(VALUE_T &&...VALUE) noexcept {
  return std::array{std::forward<VALUE_T>(VALUE)...};
}

template <typename TYPE, typename NOTSEQ> struct make_array;
template <typename TYPE, std::size_t... N>
struct make_array<TYPE, std::index_sequence<N...>> {
  using type = kar::container::array<TYPE, N...>;
};

template <typename TYPE>
using make_array_t =
    typename make_array<kar::internal::base_value_t<TYPE>,
                        typename kar::internal::dims_seq<TYPE>>::type;

template <typename TYPE> constexpr auto make(const TYPE &a) {
  using OUT = make_array_t<TYPE>;
  OUT out(a);
  return out;
}

} // namespace nd
} // namespace kar

#endif // ARRAY_HPP
