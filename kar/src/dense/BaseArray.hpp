#ifndef BASE_ARRAY_HPP
#define BASE_ARRAY_HPP

#include <array>
#include <utility>

namespace kar {
namespace nd {

template <typename... VALUE_T> constexpr auto arr(VALUE_T &&...VALUE) {
  return std::array{std::forward<VALUE_T>(VALUE)...};
}
} // namespace nd
} // namespace kar

#endif // BASE_ARRAY_HPP
