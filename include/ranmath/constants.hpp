#ifndef RAN_CONSTANTS_HPP_
#define RAN_CONSTANTS_HPP_

#include <ranmath/concepts.hpp>

namespace ran {

template<meta::numeric_type T>
constexpr T pi = static_cast<T>(3.14159265358979323846);

template<meta::numeric_type T>
constexpr T e = static_cast<T>(2.7182818284590452354);

} // namespace ran

#endif // #ifndef RAN_CONSTANTS_HPP_
