#ifndef BASEARRAY_HPP
#define BASEARRAY_HPP

#include <array>
#include <cassert>
#include <cstddef>

namespace kar {
namespace container {

template <typename TYPE, std::size_t... DIMS_SEQ> class array {
public:
  [[nodiscard]] static constexpr auto rank() noexcept { return _rank; }

  [[nodiscard]] static constexpr auto size() noexcept { return _size; }

  [[nodiscard]] static constexpr auto shape() noexcept { return _shape; }

  [[nodiscard]] static constexpr auto strideElement() noexcept {
    return _stride_element;
  }
  [[nodiscard]] static constexpr auto strideByte() noexcept {
    return _stride_byte;
  }

  template <typename... SEQ>
  constexpr auto &operator()(const SEQ &...idx) noexcept {
    return _data[_lexicographic(
        std::array<std::size_t, _rank>{std::size_t(idx...)})];
  }

  template <typename... SEQ>
  constexpr const auto &operator()(const SEQ &...idx) const noexcept {
    return _data[_lexicographic(
        std::array<std::size_t, _rank>{std::size_t(idx...)})];
  }

  template <typename... SEQ> constexpr auto at(SEQ *...idx) noexcept {
    return _data[_lexicographic(
        std::array<std::size_t, _rank>{std::size_t(idx...)})];
  }

  template <typename... SEQ>
  constexpr const auto at(SEQ *...idx) const noexcept {
    return _data[_lexicographic(
        std::array<std::size_t, _rank>{std::size_t(idx...)})];
  }

protected:
  static constexpr std::size_t _rank = sizeof...(DIMS_SEQ);
  static constexpr std::size_t _size = (std::size_t(1) * ... * DIMS_SEQ);

  std::array<TYPE, _size> _data;

  static constexpr std::array<TYPE, _rank> _shape{DIMS_SEQ...};
  static constexpr std::array<TYPE, _rank> _stride_element = []() noexcept {
    std::array<TYPE, _rank> x_s{};
    if constexpr (_rank == 0)
      return x_s;

    x_s[_rank - 1] = 1;
    for (std::size_t i = _rank - 1; i-- > 0;)
      x_s[i] = x_s[i + 1] * _shape[i + 1];

    return x_s;
  };

  static constexpr std::array<TYPE, _rank> _stride_byte = []() noexcept {
    std::size_t byte = sizeof(TYPE);
    std::array<TYPE, _rank> x_s;
    if constexpr (_rank == 0)
      return x_s;

    x_s[_rank - 1] = byte;
    for (std::size_t i = _rank - 1; i-- < _rank;)
      x_s[i] = _shape[i - 1] * x_s[i - 1];

    return x_s;
  };

  static constexpr void
  _checkBound(const std::array<std::size_t, _rank> &idx) noexcept {
#ifndef NDEBUG
    for (std::size_t i = 0; i < _rank; ++i)
      assert(idx[i] < _shape[i]);
#endif // !NDEBUG
  }

  static constexpr std::size_t
  _lexicographic(const std::array<std::size_t, _rank> &idx) noexcept {
    if constexpr (_rank == 0)
      return 0;

    _checkBound(idx);

    std::size_t x_offside = 0;
    for (std::size_t i = 0; i < _rank; ++i)
      x_offside += idx[i] * _stride_element[i];

    return x_offside;
  }
};

} // namespace container
} // namespace kar

#endif // !BASEARRAY_HPP
