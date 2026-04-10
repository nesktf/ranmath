#ifndef RAN_INTEGRATOR_HPP_
#define RAN_INTEGRATOR_HPP_

#include <ranmath/forward.hpp>

namespace ran {

template<meta::numeric_type T>
struct IntegratorTrap {
  template<meta::integration_fn<T> Fun>
  RAN_DEF T operator()(T a, T b, Fun&& f) {
    const T size = b - a;
    return (size / 2) * (f(a) + f(b));
  }

  template<meta::integration_fn<T> Fun>
  RAN_DEF T operator()(T a, T b, uint n, Fun&& f) {
    const T size = b - a;
    const T h = size / static_cast<T>(n);

    T out = f(a);
    for (uint i = 1; i < n; ++i) {
      out += 2 * f(a + (i * h));
    }
    out += f(b);

    return (size * out) / (2 * n);
  }
};

template<meta::numeric_type T>
struct IntegratorSimp13 {
  template<meta::integration_fn<T> Fun>
  RAN_DEF T operator()(T a, T b, Fun&& f) {
    const T size = b - a;
    const T x_1 = a + ((b - a) / 3);

    return (size / 6) * (f(a) + 4 * f(x_1) + f(b));
  }

  template<meta::integration_fn<T> Fun>
  RAN_DEF T operator()(T a, T b, uint n, Fun&& f) {
    const T size = b - a;
    const T h = size / static_cast<T>(n);

    T out = f(a);
    for (uint i = 1; i < n; i += 2) {
      out += 4 * f(a + (i * h)); // Odd
    }
    for (uint i = 2; i < n; i += 2) {
      out += 2 * f(a + (i * h)); // Even
    }
    out += f(b);

    return (size * out) / (3 * n);
  }
};

template<meta::numeric_type T>
struct IntegratorSimp38 {
  template<meta::integration_fn<T> Fun>
  RAN_DEF T operator()(T a, T b, Fun&& f) {
    const T size = b - a;
    const T h = size / 4;
    const T x_1 = a + h;
    const T x_2 = a + (h * 2);

    return (size / 8) * (f(a) + 3 * f(x_1) + 3 * f(x_2) + f(b));
  }
};

template<meta::numeric_type T>
struct OdeRK4 {
  template<meta::ode_fn<T> Fun>
  RAN_DEF T operator()(T x, T y, T h, Fun&& f) {
    const auto k1 = h * f(x, y);
    const auto k2 = h * f(x + h * T{0.5}, y + k1 * T{0.5});
    const auto k3 = h * f(x + h * T{0.5}, y + k2 * T{0.5});
    const auto k4 = h * f(x + h, y + k3);

    return y + T{1 / 6.0} * (k1 + 2 * k2 + 2 * k3 + k4);
  }
};

template<meta::numeric_type T>
struct OdeEuler {
  template<meta::ode_fn<T> Fun>
  RAN_DEF T operator()(T x, T y, T h, Fun&& f) {
    return y + h * f(x, y);
  }
};
} // namespace ran

#endif // #ifndef RAN_INTEGRATOR_HPP_
