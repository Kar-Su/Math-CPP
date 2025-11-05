#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "HelperArray.hpp"
#include <cstddef>

namespace kar {
namespace nd {

template <typename TYPE = void, typename BASE, std::size_t N>
constexpr auto array(const BASE (&data)[N]) noexcept {
  return helper::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N, std::size_t M>
constexpr auto array(const BASE (&data)[N][M]) noexcept {
  return helper::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N, std::size_t M,
          std::size_t K>
constexpr auto array(const BASE (&data)[N][M][K]) noexcept {
  return helper::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N, std::size_t M,
          std::size_t K, std::size_t L>
constexpr auto array(const BASE (&data)[N][M][K][L]) noexcept {
  return helper::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N, std::size_t M,
          std::size_t K, std::size_t L, std::size_t O>
constexpr auto array(const BASE (&data)[N][M][K][L][O]) noexcept {
  return helper::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N, std::size_t M,
          std::size_t K, std::size_t L, std::size_t O, std::size_t P>
constexpr auto array(const BASE (&data)[N][M][K][L][O][P]) noexcept {
  return helper::array_from_c_array<TYPE>(data);
}

template <typename TYPE = void, typename BASE, std::size_t N, std::size_t M,
          std::size_t K, std::size_t L, std::size_t O, std::size_t P,
          std::size_t Q>
constexpr auto array(const BASE (&data)[N][M][K][L][O][P][Q]) noexcept {
  return helper::array_from_c_array<TYPE>(data);
}

} // namespace nd
} // namespace kar

#endif // ARRAY_HPP
