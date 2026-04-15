#ifndef RAN_FUNCS_HPP_
#define RAN_FUNCS_HPP_

#include <ranmath/forward.hpp>

namespace ran {

template<meta::numeric_type T>
RAN_DEF T sqrt(T x) noexcept {
  return std::sqrt(x);
}

template<meta::numeric_type T>
RAN_DEF T rsqrt(T x) noexcept {
  return T(1) / std::sqrt(x);
}

namespace impl {

template<typename T>
RAN_DEF auto newton_rsqrt(T x, T y) noexcept -> T {
  return y * (T(1.5) - (x * y * y * T(.5)));
}

template<std::size_t Iters, typename T>
struct qrsqrt_iter {
  static RAN_DEF auto calc(T x, T y) noexcept -> T {
    return qrsqrt_iter<Iters - 1, T>::calc(x, newton_rsqrt(x, y));
  }
};

template<typename T>
struct qrsqrt_iter<1, T> {
  static RAN_DEF auto calc(T x, T y) noexcept -> T { return newton_rsqrt(x, y); }
};

template<typename T>
struct qrsqrt_shift;

template<>
struct qrsqrt_shift<f32> {
  static RAN_DEF auto calc(f32 x) noexcept -> f32 {
    const s32 shifted = std::bit_cast<s32>(x) >> 1;
    return std::bit_cast<f32>(0x5F3759DF - shifted); // what the fuck?
  }
};

template<>
struct qrsqrt_shift<f64> {
  static RAN_DEF auto calc(f64 x) noexcept -> f64 {
    const s64 shifted = std::bit_cast<s64>(x) >> 1;
    return std::bit_cast<f64>(0x5FE6EB50C7B537A9 - shifted); // what the fuck?
  }
};

} // namespace impl

template<usize Iters, meta::floating_point T>
RAN_DEF T qrsqrt(T x) noexcept {
#if 0
  const s32 shifted_x = 0x5F3759DF - (std::bit_cast<s32>(x) >> 1); // what the fuck?
  f32 y = std::bit_cast<f32>(shifted_x);
  y = y * (1.5f - (x * y * y * .5f)); // 1st iteration
  // y = y * (1.5f - (x * y * y * .5f)); // 2nd iteration
  return y;
#endif
  static_assert(Iters > 0, "Invalid iteration number");
  return ::ran::impl::qrsqrt_iter<Iters, T>::calc(x, ::ran::impl::qrsqrt_shift<T>::calc(x));
}

template<meta::numeric_type T>
RAN_DEF T cos(T x) noexcept {
  return std::cos(x);
}

template<meta::numeric_type T>
RAN_DEF T sin(T x) noexcept {
  return std::sin(x);
}

template<meta::numeric_type T>
RAN_DEF T tan(T x) noexcept {
  return std::tan(x);
}

template<meta::numeric_type T>
RAN_DEF T acos(T x) noexcept {
  return std::acos(x);
}

template<meta::numeric_type T>
RAN_DEF T asin(T x) noexcept {
  return std::asin(x);
}

template<meta::numeric_type T>
RAN_DEF T atan(T x) noexcept {
  return std::atan(x);
}

template<meta::numeric_type T>
RAN_DEF T atan2(T y, T x) noexcept {
  return std::atan2(y, x);
}

template<meta::numeric_type T>
RAN_DEF T rad(T degs) noexcept {
  return degs * static_cast<T>(0.01745329251994329576923690768489);
}

template<typename T>
RAN_DEF T deg(T rads) {
  return rads * static_cast<T>(57.295779513082320876798154814105);
}

template<meta::numeric_type T>
RAN_DEF T abs(T x) noexcept {
  return std::abs(x);
}

template<meta::numeric_type T>
RAN_DEF T clamp(T x, T min, T max) noexcept {
  return std::clamp(x, min, max);
}

template<meta::numeric_type T>
RAN_DEF T max(T a, T b) noexcept {
  return std::max(a, b);
}

template<meta::numeric_type T>
RAN_DEF T min(T a, T b) noexcept {
  return std::min(a, b);
}

template<meta::numeric_type T>
RAN_DEF T pow(T a, T b) noexcept {
  return std::pow(a, b);
}

template<meta::numeric_type T>
RAN_DEF T epsilon_err(T a, T b) noexcept {
  return ::ran::abs((b - a) / b);
}

template<meta::numeric_type TL, meta::numeric_type TR>
RAN_DEF auto periodic_add(const TL& a, const TR& b, decltype(a + b) min,
                          decltype(a + b) max) noexcept {
  auto res = a + b;
  auto range = max - min;
  while (res >= max)
    res -= range;
  while (res < min)
    res += range;
  return res;
}

template<meta::floating_point T>
RAN_DEF bool fequal(T a, T b) noexcept {
  return (std::fabs(a - b) <=
          std::numeric_limits<T>::epsilon() * std::fmax(std::fabs(a), std::fabs(b)));
}

} // namespace ran

#endif // #ifndef RAN_FUNCS_HPP_
