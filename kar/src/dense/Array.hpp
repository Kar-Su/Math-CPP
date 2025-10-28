#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <array>

namespace kar {
namespace nd {

template <typename... VALUE_T> constexpr auto arr(VALUE_T &&...VALUE) noexcept {
  return std::array{std::forward<VALUE_T>(VALUE)...};
}

} // namespace nd
} // namespace kar

#endif // ARRAY_HPP
