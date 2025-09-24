#ifdef BASE_ARRAY_HPP

#include "WrapperArray.hpp"
#include <array>
#include <utility>

namespace kar {

template <typename VALUE_T> constexpr auto arr(VALUE_T &&...VALUE) {
  return std::array<VALUE_T>{std::forward<VALUE_T>(std::move(VALUE...))};
}
} // namespace kar

#endif // BASE_ARRAY_HPP
