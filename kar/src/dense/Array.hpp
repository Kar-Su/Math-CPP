#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "BaseArray.hpp"
#include "UnpackArray.hpp"
#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace kar {
namespace nd {

template <typename... VALUE_T>
constexpr auto arr(VALUE_T &&...VALUE) noexcept {
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

namespace detail {

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
    constexpr auto extent =
        std::extent_v<std::remove_reference_t<ARRAY>>;
    static_assert(extent > 0, "Extent must be greater than zero");
    return cast_to_std_array_impl<TYPE>(
        arr, std::make_index_sequence<extent>{});
  } else {
    return static_cast<TYPE>(arr);
  }
}

template <typename OUT_TYPE, typename ARRAY>
constexpr auto array_from_c_array(const ARRAY &data) noexcept {
  using base_value = std::remove_all_extents_t<ARRAY>;
  using value_type =
      std::conditional_t<std::is_void_v<OUT_TYPE>,
                         std::remove_cv_t<base_value>, OUT_TYPE>;
  auto nested = cast_to_std_array<value_type>(data);
  return make(nested);
}

} // namespace detail

template <typename TYPE = void, typename BASE, std::size_t N>
constexpr auto array(const BASE (&data)[N]) noexcept {
  return detail::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N,
          std::size_t M>
constexpr auto array(const BASE (&data)[N][M]) noexcept {
  return detail::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N,
          std::size_t M, std::size_t K>
constexpr auto array(const BASE (&data)[N][M][K]) noexcept {
  return detail::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N,
          std::size_t M, std::size_t K, std::size_t L>
constexpr auto array(const BASE (&data)[N][M][K][L]) noexcept {
  return detail::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N,
          std::size_t M, std::size_t K, std::size_t L, std::size_t O>
constexpr auto array(const BASE (&data)[N][M][K][L][O]) noexcept {
  return detail::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N,
          std::size_t M, std::size_t K, std::size_t L, std::size_t O,
          std::size_t P>
constexpr auto array(const BASE (&data)[N][M][K][L][O][P]) noexcept {
  return detail::array_from_c_array<TYPE>(data);
}

} // namespace nd
} // namespace kar

#endif // ARRAY_HPP
