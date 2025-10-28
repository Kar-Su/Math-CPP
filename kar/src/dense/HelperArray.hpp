#ifndef HELPER_ARRAY_HPP
#define HELPER_ARRAY_HPP

#include "BaseArray.hpp"
#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace kar {
namespace helper {

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

template <typename TYPE, typename ARRAY>
constexpr auto cast_to_std_array(const ARRAY &arr) noexcept;

template <typename TYPE, typename ARRAY, std::size_t... I>
constexpr auto cast_to_std_array_impl(const ARRAY &arr,
                                      std::index_sequence<I...>) noexcept {
  return std::array{cast_to_std_array<TYPE>(arr[I])...};
}

template <typename TYPE, typename ARRAY>
constexpr auto cast_to_std_array(const ARRAY &arr) noexcept {
  if constexpr (std::is_array_v<std::remove_reference_t<ARRAY>>) {
    constexpr auto extent = std::extent_v<std::remove_reference_t<ARRAY>>;
    static_assert(extent > 0, "Extent must be greater than zero");
    return cast_to_std_array_impl<TYPE>(arr,
                                        std::make_index_sequence<extent>{});
  } else {
    return static_cast<TYPE>(arr);
  }
}

template <typename OUT_TYPE, typename ARRAY>
constexpr auto array_from_c_array(const ARRAY &data) noexcept {
  using base_value = std::remove_all_extents_t<ARRAY>;
  using value_type = std::conditional_t<std::is_void_v<OUT_TYPE>,
                                        std::remove_cv_t<base_value>, OUT_TYPE>;
  auto nested = cast_to_std_array<value_type>(data);
  return make(nested);
}

} // namespace helper

} // namespace kar

#endif // !HELPER_ARRAY_HPP
