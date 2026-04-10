#ifndef RAN_CONCEPTS_HPP_
#define RAN_CONCEPTS_HPP_

#include "./version.hpp"

#include <concepts>

namespace ran::meta {

template<typename T, typename Ret, typename... Args>
concept invocable = std::is_invocable_r_v<Ret, T, Args...>;

template<typename T>
concept integral = std::integral<T>;

template<typename T>
concept floating_point = std::floating_point<T>;

template<typename T>
concept numeric_type = integral<T> || floating_point<T>;

template<typename From, typename To>
concept numeric_convertible = numeric_type<From> && std::convertible_to<From, To>;

template<typename T, typename U>
concept interpolable = requires(T a, T b, U scalar) {
  { a + b } -> std::convertible_to<T>;
  { a - b } -> std::convertible_to<T>;
  { scalar* a } -> std::convertible_to<T>;
};

template<typename Fn, typename T, typename U>
concept lerp_fn = invocable<Fn, T, const T&, const T&, U>;

// f(T x) -> T
template<typename Fn, typename T>
concept integration_fn = invocable<T, Fn, T> && numeric_type<T>;

// f(T x, T y) -> T
// \phi(x, y, h) = f(x, y)
template<typename Fn, typename T>
concept ode_fn = invocable<T, Fn, T, T> && numeric_type<T>;

} // namespace ran::meta

#endif // #ifndef RAN_CONCEPTS_HPP_
