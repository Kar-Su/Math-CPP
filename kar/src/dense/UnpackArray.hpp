#ifndef UNPACKARRAY_HPP
#define UNPACKARRAY_HPP

#include <array>
#include <cstddef>
#include <utility>

namespace kar {
namespace container {
template <typename TYPE, std::size_t... DIMS_SEQ> class array;
} // namespace container
namespace internal {
/*
 * @STRUCT base_value<BASE_T>
 * @BRIEF template struct default for get base value type.
 * @DETAILS This struct is the end of loop of inheritence looping.
 * @TPARAM BASE_T any type except std::array, kar::container::array
 * */
template <typename BASE_T> struct base_value {
  using type = BASE_T;
};

/*
 * @STRUCT base_value<std::array<FORWARD_T, N>>
 * @BRIEF template struct specifics for get base value type an array
 *
   This process using looping inheritence on default->struct and this->struct
   that struct check if template type of std::array is std::array again or not
 *
 * @TPARAM FORWARD_T same as template type of std::array
 * @TPARAM N same as template size of std::array
 * */
template <typename FORWARD_T, std::size_t N>
struct base_value<std::array<FORWARD_T, N>> : base_value<FORWARD_T> {};

/*
 * @STRUCT base_value<container::array>
 * @BRIEF template variadic struct specifics for get base value type an array
    costum
 *
   This process using looping inheritence on default->struct and this->struct
   that struct check if template type of container::array is container::array
   again or not
 *
 * @TPARAM FORWARD_T same as template type of container::array
 * @TPARAM N same as template ellipsis size of container::array
 * */
template <typename FORWARD_T, std::size_t... DIMS_SEQ>
struct base_value<container::array<FORWARD_T, DIMS_SEQ...>>
    : base_value<FORWARD_T> {};

/*
 * @USING base_value_t
 * @BRIEF template alias for defining an type base value
 * @DETAILS developers only using this to declare all logic to get base value
 * type
 * @TPARAM BASE_T is a type that developers want to get base value type
 * */
template <typename BASE_T>
using base_value_t = typename base_value<BASE_T>::type;

/*
 * @STRUCT sequence_concate<BASE_INDEX, FORWARD_PACK>
 * @BRIEF template struct default to concate index sequence
 * @DETAILS this struct will be used in the dimension_sequence struct
 * @TPARAM BASE_INDEX is an index in this->loop
 * @TPARAM FORWARD_PACK is an next loop dimension_sequence
 * */
template <typename BASE_INDEX, typename FORWARD_PACK>
struct sequence_concate {};

/*
 * @STRUCT sequence_concate<std::index_sequence<BASE_INDEX...>,
 *                          std::index_sequence<FORWARD_PACK>>
 * @BRIEF template variadic struct to looping concate an index sequence
 * @DETAILS this struct will be used in the dimension_sequence struct
 * @TPARAM BASE_INDEX is an index in this->loop
 * @TPARAM FORWARD_PACK is an next loop dimension_sequence
 * @EXAMPLE
    using type = typename sequence_concate<
     std::index_sequence<N>,
     typename dimension_sequence<RECURSIVE_DIMS>::type>::type;
 * */
template <typename std::size_t... BASE_INDEX, std::size_t... FORWARD_PACK>
struct sequence_concate<std::index_sequence<BASE_INDEX...>,
                        std::index_sequence<FORWARD_PACK...>> {
  using type = std::index_sequence<BASE_INDEX..., FORWARD_PACK...>;
};

/*
 * @STRUCT dimension_sequence<BASE_DIMS>
 * @BRIEF template struct default if BASE_DIMS doesn't have index
 * @DETAILS dims_seq will be 1 for default.
 * @BASE_DIMS any type that doesn't have index
 * */
template <typename BASE_DIMS> struct dimension_sequence {
  using type = std::index_sequence<>;
};

/*
 * @STRUCT dimension_sequence<std::array<RECURSIVE_DIMS,N>>
 * @BRIEF template struct spesifics to get std::array dimensions

   It will loop through second parameter template std::index_sequence
   as you see it will call dimension_sequence type again.

 * @TPARAM RECURSIVE_DIMS is a next type of recursive.
 * @TPARAM N is a std::size of this->dimension
 * */
template <typename RECURSIVE_DIMS, std::size_t N>
struct dimension_sequence<std::array<RECURSIVE_DIMS, N>> {
  using type = typename sequence_concate<
      std::index_sequence<N>,
      typename dimension_sequence<RECURSIVE_DIMS>::type>::type;
};

/*
 * @STRUCT dimension_sequence<container::array<RECURSIVE_DIMS, DIMS_SEQ...>>
 * @BRIEF template variadic struct spesifics to get an array costum dims

   It will send DIMS_SEQ ellipsis as template parameter for std::index_sequence

 * @TPARAM BASE_TYPE is type value of custom array
 * @TPARAM DIMS_SEQ is an ellipsis of dimension.
 **/
template <typename BASE_TYPE, std::size_t... DIMS_SEQ>
struct dimension_sequence<container::array<BASE_TYPE, DIMS_SEQ...>> {
  using type = std::index_sequence<DIMS_SEQ...>;
};

/*
 * @USING dims_seq
 * @BRIEF template alias for defining an type of dimension_sequence struct
 * @DETAILS developers only using this to declare all logic to get dimension of
    an array
 * @TPARAM BASE_DIMS is a type that developers want to get dimension of an array
 * */
template <typename BASE_DIMS>
using dims_seq = typename dimension_sequence<BASE_DIMS>::type;

} // namespace internal
} // namespace kar

#endif // !UNPACKARRAY_HPP
