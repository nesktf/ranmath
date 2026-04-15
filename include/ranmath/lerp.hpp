#ifndef RAN_INTERPOLATOR_HPP_
#define RAN_INTERPOLATOR_HPP_

#include <ranmath/forward.hpp>

namespace ran {

template<meta::floating_point T>
RAN_DEF T lerp(T a, T b, T t) noexcept {
  return (a * (T(1) - t)) + (b * t);
}

template<usize N, meta::floating_point T>
RAN_DEF Vec<N, T> lerp(const Vec<N, T>& a, const Vec<N, T>& b, T t) noexcept {
  return (a * (T(1) - t)) + (b * t);
}

template<usize N, meta::floating_point T>
RAN_DEF Vec<N, T> slerp(const Vec<N, T>& a, const Vec<N, T>& b, T t) noexcept {
  const T c_theta = ::ran::dot(a, b);
  const T theta = ::ran::acos(c_theta);
  const T s_theta = ::ran::sin(theta);
  const T t1 = ::ran::sin((T(1) - t) * theta);
  const T t2 = ::ran::sin(t * theta);
  return ((a * t1) + (b * t2)) / s_theta;
}

template<meta::floating_point T>
RAN_DEF Quat<T> lerp(const Quat<T>& a, const Quat<T>& b, T t) noexcept {
  Quat<T> out;
  out.w = ::ran::lerp(a.w, b.w, t);
  out.x = ::ran::lerp(a.x, b.x, t);
  out.y = ::ran::lerp(a.y, b.y, t);
  out.z = ::ran::lerp(a.z, b.z, t);
  return out;
}

template<meta::floating_point T>
RAN_DEF Quat<T> slerp(const Quat<T>& a, const Quat<T>& b, T t) noexcept {
  T c_theta = ::ran::dot(a, b);
  Quat<T> c;
  if (c_theta < T(0)) {
    c_theta = -c_theta;
    c = -b;
  } else {
    c = b;
  }
  if (c_theta > T(1) - ::ran::epsilon<T>) {
    // Normal lerp to avoid sin(theta) == 0
    return lerp(a, c, t);
  } else {
    const T theta = ::ran::acos(c_theta);
    const T s_theta = ::ran::sin(theta);
    const T t1 = ::ran::sin((T(1) - t) * theta);
    const T t2 = ::ran::sin(t * theta);
    return ((a * t1) + (b * t2)) / s_theta;
  }
}

template<typename EasingFn>
struct LerpFn {
public:
  LerpFn() noexcept(std::is_nothrow_default_constructible_v<EasingFn>) = default;

  LerpFn(const EasingFn& easing) noexcept(std::is_nothrow_copy_constructible_v<EasingFn>) :
      _easing(easing) {}

public:
  template<meta::floating_point T>
  RAN_DEF T operator()(T a, T b, T t) {
    static_assert(meta::invocable<T, EasingFn, T>,
                  "Fn has to be invocable with floating point type T");
    return ::ran::lerp(a, b, _easing(t));
  }

  template<usize N, meta::floating_point T>
  RAN_DEF Vec<N, T> operator()(const Vec<N, T>& a, const Vec<N, T>& b, T t) {
    static_assert(meta::invocable<T, EasingFn, T>,
                  "Fn has to be invocable with floating point type T");
    return ::ran::lerp(a, b, _easing(t));
  }

  template<meta::floating_point T>
  RAN_DEF Quat<T> operator()(const Quat<T>& a, const Quat<T>& b, T t) {
    static_assert(meta::invocable<T, EasingFn, T>,
                  "Fn has to be invocable with floating point type T");
    return ::ran::lerp(a, b, _easing(t));
  }

private:
  [[no_unique_address]] EasingFn _easing;
};

template<typename Fn>
LerpFn(Fn) -> LerpFn<Fn>;

template<typename EasingFn>
struct SlerpFn {
public:
  SlerpFn() noexcept(std::is_nothrow_default_constructible_v<EasingFn>) = default;

  SlerpFn(const EasingFn& easing) noexcept(std::is_nothrow_copy_constructible_v<EasingFn>) :
      _easing(easing) {}

public:
  template<meta::floating_point T>
  RAN_DEF T operator()(T a, T b, T t) {
    static_assert(meta::invocable<T, EasingFn, T>,
                  "Fn has to be invocable with floating point type T");
    return ::ran::slerp(a, b, _easing(t));
  }

  template<usize N, meta::floating_point T>
  RAN_DEF Vec<N, T> operator()(const Vec<N, T>& a, const Vec<N, T>& b, T t) {
    static_assert(meta::invocable<T, EasingFn, T>,
                  "Fn has to be invocable with floating point type T");
    return ::ran::slerp(a, b, _easing(t));
  }

  template<meta::floating_point T>
  RAN_DEF Quat<T> operator()(const Quat<T>& a, const Quat<T>& b, T t) {
    static_assert(meta::invocable<T, EasingFn, T>,
                  "Fn has to be invocable with floating point type T");
    return ::ran::slerp(a, b, _easing(t));
  }

private:
  [[no_unique_address]] EasingFn _easing;
};

template<typename Fn>
SlerpFn(Fn) -> SlerpFn<Fn>;

template<meta::floating_point T>
struct EasingLinear {
  RAN_DEF T operator()(T t) const noexcept { return t; }
};

template<meta::floating_point T>
struct EasingSineIn {
  RAN_DEF T operator()(T t) const noexcept {
    // https://easings.net/
    return T(1) - ::ran::cos((t * ::ran::pi<T>) / T(2));
  }
};

template<meta::floating_point T>
struct EasingSineOut {
  RAN_DEF T operator()(T t) const noexcept {
    // https://easings.net/
    return ::ran::sin((t * ::ran::pi<T>) / T(2));
  }
};

template<meta::floating_point T>
struct EasingSineInOut {
  RAN_DEF T operator()(T t) const noexcept {
    // https://easings.net/
    return -(::ran::cos(::ran::pi<T> * t) - T(1)) / T(2);
  }
};

template<meta::floating_point T>
struct EasingElasticIn {
  RAN_DEF T operator()(T t) const noexcept {
    // https://easings.net/
    constexpr T c4 = T(2) * ::ran::pi<T> / T(3);
    if (t <= T(0) || t >= T(1)) {
      return t;
    }
    return -::ran::pow(T(2), T(10) * t - T(10)) * ::ran::sin((t * T(10) - (T(10.75))) * c4);
  }
};

template<meta::floating_point T>
struct EasingElasticOut {
  RAN_DEF T operator()(T t) const noexcept {
    constexpr T c4 = T(2) * ::ran::pi<T> / T(3);
    if (t <= T(0) || t >= T(1)) {
      return t;
    }
    return ::ran::pow(T(2), T(-10) * t) * (::ran::sin(((t * T(10)) - T(.75)) * c4) + T(1));
  }
};

template<meta::floating_point T>
struct EasingElasticInOut {
  RAN_DEF T operator()(T t) const noexcept {
    // https://easings.net/
    constexpr T c2 = T(1.70158 * 1.525);
    if (t < T(.5)) {
      return (::ran::pow(T(2) * t, T(2)) * ((c2 + T(1)) * T(2) * t - c2)) / T(2);
    }
    return (::ran::pow(T(2) * t - T(2), T(2)) * ((c2 + T(1)) * (t * T(2) - T(2)) + c2) + T(2)) /
           T(2);
  }
};

template<meta::floating_point T>
struct EasingPow {
public:
  EasingPow(u32 p) noexcept : _p(p) {}

public:
  RAN_DEF T operator()(T t) const noexcept {
    T res(1);
    for (u32 i = _p; i--;) {
      res *= t;
    }
    return res;
  }

private:
  u32 _p;
};

} // namespace ran

#endif // #ifndef RAN_INTERPOLATOR_HPP_
