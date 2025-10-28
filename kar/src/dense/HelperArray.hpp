#ifndef HELPER_ARRAY_HPP
#define HELPER_ARRAY_HPP

#include <array>
#include <cstddef>

namespace kar {
namespace helper {

template <class T, std::size_t N, std::size_t... I>
constexpr std::array<std::remove_cv_t<T>, N>
to_array_impl(T (&a)[N], std::index_sequence<I...>) {
  return {{a[I]...}};
}
} // namespace helper
} // namespace kar

#endif // !HELPER_ARRAY_HPP
