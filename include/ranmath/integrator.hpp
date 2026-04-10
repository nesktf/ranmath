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

template<meta::floating_point T, typename Alloc>
struct DFTNaiveFn {
public:
  using value_type = T;
  using cmplx_type = Cmplx<T>;

public:
  RAN_DEF
  DFTNaiveFn(const Alloc& alloc = {}) noexcept(std::is_nothrow_default_constructible_v<Alloc>) :
      _alloc(alloc) {}

public:
  template<meta::random_iter_of<cmplx_type> It>
  RAN_DEF void operator()(It samples_begin, It samples_end, bool inv) {
    const auto n_it = std::distance(samples_begin, samples_end);
    if (n_it <= 0) {
      return;
    }

    const u32 n = static_cast<u32>(n_it);

    // Copy to buffer
    cmplx_type* buffer = _alloc.allocate(n_it);
    static_assert(std::is_trivially_copy_constructible_v<cmplx_type>);
    std::memcpy(buffer, &*samples_begin, n_it * sizeof(buffer[0]));

    const T omega = T(2) * ::ran::pi<T> / static_cast<T>(n) * (inv ? T(1) : T(-1));
    const T scale = (inv ? T{1} / static_cast<T>(n) : T(1));

    for (usize k = 0; k < n; ++k) {
      cmplx_type sum{0, 0};
      for (usize i = 0; i < n; ++i) {
        const T angle = omega * static_cast<T>(k) * static_cast<T>(i);
        const cmplx_type rot{::ran::cos(angle), ::ran::sin(angle)};
        sum = sum + buffer[i] * rot;
      }
      *(samples_begin + k) = sum * scale;
    }
    _alloc.deallocate(buffer, n_it);
  }

private:
  [[no_unique_address]] Alloc _alloc;
};

template<meta::floating_point T, typename Alloc>
struct DFTRecursiveFn {
public:
  using value_type = T;
  using cmplx_type = Cmplx<T>;

public:
  RAN_DEF DFTRecursiveFn(const Alloc& alloc = {}) noexcept(
    std::is_nothrow_default_constructible_v<Alloc>) : _alloc(alloc) {}

public:
  template<meta::random_iter_of<cmplx_type> It>
  RAN_DEF void operator()(It samples_begin, It samples_end, bool inv) {
    const auto n_it = std::distance(samples_begin, samples_end);
    if (n_it <= 0) {
      return;
    }

    const u32 n = static_cast<u32>(n_it);
    if ((n & (n - 1))) { // Only powers of two
      return;
    }

    _compute(&*samples_begin, n, inv);
  }

private:
  RAN_DEF void _compute(cmplx_type* samples, u32 n, bool inv) {
    if (n == 1) {
      return;
    }

    // https://cp-algorithms.com/algebra/fft.html
    const u32 half = n / 2;
    auto* evens = _alloc.allocate(n);
    auto* odds = _alloc.allocate(n);
    for (usize i = 0; i < half; ++i) {
      evens[i] = *(samples + 2 * i);
      odds[i] = *(samples + 2 * i + 1);
    }
    _compute(odds, half, inv);
    _compute(evens, half, inv);

    const T angle = T(2) * ::ran::pi<T> / static_cast<T>(n) * (inv ? T(1) : T(-1));
    const T scale = (inv ? T(1) / T(2) : T(1));
    for (usize k = 0; k < half; ++k) {
      const cmplx_type w{::ran::cos(static_cast<T>(k) * angle),
                         ::ran::sin(static_cast<T>(k) * angle)};
      *(samples + k) = (evens[k] + w * odds[k]) * scale;
      *(samples + k + half) = (evens[k] - w * odds[k]) * scale;
    }
    _alloc.deallocate(odds, half);
    _alloc.deallocate(evens, half);
  }

private:
  [[no_unique_address]] Alloc _alloc;
};

template<meta::floating_point T>
struct DFTInplaceFn {
public:
  using value_type = T;
  using cmplx_type = Cmplx<T>;

public:
  template<meta::random_iter_of<cmplx_type> It>
  RAN_DEF void operator()(It samples_begin, It samples_end, bool inv) {
    const auto n_it = std::distance(samples_begin, samples_end);
    if (n_it <= 0) {
      return;
    }

    const u32 n = static_cast<u32>(n_it);
    if ((n & (n - 1))) { // Only powers of two
      return;
    }

    // https://cp-algorithms.com/algebra/fft.html
    for (u32 i = 1, j = 0; i < n; ++i) {
      u32 bit = n >> 1;
      for (; j & bit; bit >>= 1) {
        j ^= bit;
      }
      j ^= bit;

      if (i < j) {
        std::swap(*(samples_begin + i), *(samples_begin + j));
      }
    }

    for (usize len = 2; len <= n; len <<= 1) {
      const T angle = T(2) * ::ran::pi<T> / static_cast<T>(len) * (inv ? T(1) : T(-1));
      const cmplx_type rot{::ran::cos(angle), ::ran::sin(angle)};
      for (usize i = 0; i < n; i += len) {
        const usize half = len / 2;
        cmplx_type w{T{1}};
        for (usize j = 0; j < half; ++j) {
          const cmplx_type u = *(samples_begin + i + j);
          const cmplx_type v = (*(samples_begin + i + j + half)) * w;
          *(samples_begin + i + j) = u + v;
          *(samples_begin + i + j + half) = u - v;
          w *= rot;
        }
      }
    }

    if (inv) {
      for (auto it = samples_begin; it != samples_end; ++it) {
        (*it) /= static_cast<T>(n);
      }
    }
  }
};

} // namespace ran

#endif // #ifndef RAN_INTEGRATOR_HPP_
