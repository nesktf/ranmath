#ifndef RAN_QUATERNION_HPP_
#define RAN_QUATERNION_HPP_

#include "./forward.hpp"

namespace ran {

template<meta::numeric_type T>
struct Quat {
public:
  using value_type = T;
  static RAN_CONSTEXPR u32 component_count = 4;

  static RAN_CONSTEXPR Quat identity() noexcept { return Quat{T(1)}; }

public:
  RAN_DEFAULT_SPECIAL(Quat);

  RAN_DEF Quat(T w_, T x_, T y_, T z_) noexcept : w(w_), x(x_), y(y_), z(z_) {}

  template<meta::numeric_convertible<T> W, meta::numeric_convertible<T> X,
           meta::numeric_convertible<T> Y, meta::numeric_convertible<T> Z>
  RAN_DEF Quat(W w_, X x_, Y y_, Z z_) noexcept :
      w(static_cast<T>(w_)), x(static_cast<T>(x_)), y(static_cast<T>(y_)), z(static_cast<T>(z_)) {}

  template<meta::numeric_convertible<T> U>
  RAN_DEF explicit Quat(const Quat<U>& other) noexcept :
      w(static_cast<T>(other.w)), x(static_cast<T>(other.x)), y(static_cast<T>(other.y)),
      z(static_cast<T>(other.z)) {}

  template<meta::numeric_convertible<T> U, meta::numeric_convertible<T> V>
  RAN_DEF Quat(U w_, const Vec<3, V>& v) noexcept :
      w(static_cast<T>(w_)), x(static_cast<T>(v.x)), y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)) {}

  template<meta::numeric_convertible<T> U>
  RAN_DECL explicit Quat(const Vec<3, U>& euler) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL explicit Quat(const Mat<3, 3, U>& m) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL explicit Quat(const Mat<4, 4, U>& m) noexcept;

public:
  RAN_DEF const T& operator[](size_t idx) const noexcept {
    switch (idx) {
      default:
        [[fallthrough]];
      case 0:
        return w;
      case 1:
        return x;
      case 2:
        return y;
      case 3:
        return z;
    }
  }

  RAN_DEF T& operator[](size_t idx) noexcept { return const_cast<T&>(std::as_const(*this)[idx]); }

public:
  RAN_DEF const T* data() const noexcept { return &this->x; }

  RAN_DEF T* data() noexcept { return const_cast<T*>(std::as_const(*this).data()); }

public:
  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator+=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator-=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator*=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator/=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator=(const Quat<U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator+=(const Quat<U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator-=(const Quat<U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Quat& operator*=(const Quat<U>& other) noexcept;

public:
  T w, x, y, z;
};

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DEF Quat<U> vec_cast(const Quat<T>& q) noexcept {
  return {static_cast<U>(q.w), static_cast<U>(q.x), static_cast<U>(q.y), static_cast<U>(q.z)};
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator=(U scalar) noexcept {
  this->w = static_cast<T>(scalar);
  this->x = static_cast<T>(scalar);
  this->y = static_cast<T>(scalar);
  this->z = static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator+=(U scalar) noexcept {
  this->w += static_cast<T>(scalar);
  this->x += static_cast<T>(scalar);
  this->y += static_cast<T>(scalar);
  this->z += static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator-=(U scalar) noexcept {
  this->w -= static_cast<T>(scalar);
  this->x -= static_cast<T>(scalar);
  this->y -= static_cast<T>(scalar);
  this->z -= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator*=(U scalar) noexcept {
  this->w *= static_cast<T>(scalar);
  this->x *= static_cast<T>(scalar);
  this->y *= static_cast<T>(scalar);
  this->z *= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator/=(U scalar) noexcept {
  this->w /= static_cast<T>(scalar);
  this->x /= static_cast<T>(scalar);
  this->y /= static_cast<T>(scalar);
  this->z /= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator=(const Quat<U>& other) noexcept {
  this->w = static_cast<T>(other.w);
  this->x = static_cast<T>(other.x);
  this->y = static_cast<T>(other.y);
  this->z = static_cast<T>(other.z);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator+=(const Quat<U>& other) noexcept {
  this->w += static_cast<T>(other.w);
  this->x += static_cast<T>(other.x);
  this->y += static_cast<T>(other.y);
  this->z += static_cast<T>(other.z);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator-=(const Quat<U>& other) noexcept {
  this->w -= static_cast<T>(other.w);
  this->x -= static_cast<T>(other.x);
  this->y -= static_cast<T>(other.y);
  this->z -= static_cast<T>(other.z);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>& Quat<T>::operator*=(const Quat<U>& other) noexcept {
  const auto q = ::ran::vec_cast<T>(other);
  const Quat<T> self = *this;
  this->w = (self.w * q.w) - (self.x * q.x) - (self.y * q.y) - (self.z * q.z);
  this->x = (self.w * q.x) + (self.x * q.w) + (self.y * q.z) - (self.z * q.y);
  this->y = (self.w * q.y) + (self.y * q.w) + (self.z * q.x) - (self.x * q.z);
  this->z = (self.w * q.z) + (self.z * q.w) + (self.x * q.y) - (self.y * q.x);
  return *this;
}

template<typename T>
RAN_DEF bool operator==(const Quat<T>& a, const Quat<T>& b) noexcept {
  return (a.w == b.w) && (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

template<typename T>
RAN_DEF bool operator!=(const Quat<T>& a, const Quat<T>& b) noexcept {
  return (a.w != b.w) || (a.x != b.x) || (a.y != b.y) || (a.z != b.z);
}

template<typename T>
RAN_DEF Quat<T> operator+(const Quat<T>& q) noexcept {
  Quat<T> out;
  out.w = +q.w;
  out.x = +q.x;
  out.y = +q.y;
  out.z = +q.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator+(const Quat<T>& a, const Quat<U>& b) noexcept {
  Quat<T> out;
  out.w = a.w + static_cast<T>(b.w);
  out.x = a.x + static_cast<T>(b.x);
  out.y = a.y + static_cast<T>(b.y);
  out.z = a.z + static_cast<T>(b.z);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator+(const Quat<T>& q, U scalar) noexcept {
  Quat<T> out;
  out.w = q.w + static_cast<T>(scalar);
  out.x = q.x + static_cast<T>(scalar);
  out.y = q.y + static_cast<T>(scalar);
  out.z = q.z + static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator+(U scalar, const Quat<T>& q) noexcept {
  Quat<T> out;
  out.w = static_cast<T>(scalar) + q.w;
  out.x = static_cast<T>(scalar) + q.x;
  out.y = static_cast<T>(scalar) + q.y;
  out.z = static_cast<T>(scalar) + q.z;
  return out;
}

template<typename T>
RAN_DEF Quat<T> operator-(const Quat<T>& q) noexcept {
  Quat<T> out;
  out.w = -q.w;
  out.x = -q.x;
  out.y = -q.y;
  out.z = -q.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator-(const Quat<T>& a, const Quat<U>& b) noexcept {
  Quat<T> out;
  out.w = a.w - static_cast<T>(b.w);
  out.x = a.x - static_cast<T>(b.x);
  out.y = a.y - static_cast<T>(b.y);
  out.z = a.z - static_cast<T>(b.z);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator-(const Quat<T>& q, U scalar) noexcept {
  Quat<T> out;
  out.w = q.w - static_cast<T>(scalar);
  out.x = q.x - static_cast<T>(scalar);
  out.y = q.y - static_cast<T>(scalar);
  out.z = q.z - static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator-(U scalar, const Quat<T>& q) noexcept {
  Quat<T> out;
  out.w = static_cast<T>(scalar) - q.w;
  out.x = static_cast<T>(scalar) - q.x;
  out.y = static_cast<T>(scalar) - q.y;
  out.z = static_cast<T>(scalar) - q.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator*(const Quat<T>& a, const Quat<U>& b) noexcept {
  const auto q = ::ran::vec_cast<T>(b);
  Quat<T> out;
  out.w = (a.w * q.w) - (a.x * q.x) - (a.y * q.y) - (a.z * q.z);
  out.x = (a.w * q.x) + (a.x * q.w) + (a.y * q.z) - (a.z * q.y);
  out.y = (a.w * q.y) + (a.y * q.w) + (a.z * q.x) - (a.x * q.z);
  out.z = (a.w * q.z) + (a.z * q.w) + (a.x * q.y) - (a.y * q.x);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator*(const Quat<T>& q, const Vec<3, U>& v) noexcept {
  const auto vt = ::ran::vec_cast<T>(v);
  const Vec<3, T> qv = ::ran::to_vec3(q);
  const Vec<3, T> c1 = ::ran::cross(qv, vt);
  const Vec<3, T> c2 = ::ran::cross(qv, c1);
  return vt + (((c1 * q.w) + c2) * T(2));
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator*(const Quat<T>& q, const Vec<4, U>& v) noexcept {
  const Vec<3, U> v3{v.x, v.y, v.z};
  const Vec<3, T> vq = q * ::ran::vec_cast<T>(v3);
  return Vec<4, T>{vq.x, vq.y, vq.z, static_cast<T>(v.w)};
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator*(const Quat<T>& q, U scalar) noexcept {
  Quat<T> out;
  out.w = q.w * static_cast<T>(scalar);
  out.x = q.x * static_cast<T>(scalar);
  out.y = q.y * static_cast<T>(scalar);
  out.z = q.z * static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator*(U scalar, const Quat<T>& q) noexcept {
  Quat<T> out;
  out.w = static_cast<T>(scalar) * q.w;
  out.x = static_cast<T>(scalar) * q.x;
  out.y = static_cast<T>(scalar) * q.y;
  out.z = static_cast<T>(scalar) * q.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator/(const Quat<T>& q, U scalar) noexcept {
  Quat<T> out;
  out.w = q.w / static_cast<T>(scalar);
  out.x = q.x / static_cast<T>(scalar);
  out.y = q.y / static_cast<T>(scalar);
  out.z = q.z / static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> operator/(U scalar, const Quat<T>& q) noexcept {
  Quat<T> out;
  out.w = static_cast<T>(scalar) / q.w;
  out.x = static_cast<T>(scalar) / q.x;
  out.y = static_cast<T>(scalar) / q.y;
  out.z = static_cast<T>(scalar) / q.z;
  return out;
}

template<typename T>
RAN_DEF Quat<T> conjugate(const Quat<T>& q) noexcept {
  Quat<T> out;
  out.w = q.w;
  out.x = -q.x;
  out.y = -q.y;
  out.z = -q.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF T dot(const Quat<T>& a, const Quat<U>& b) noexcept {
  const T w = a.w * static_cast<T>(b.w);
  const T x = a.x * static_cast<T>(b.x);
  const T y = a.y * static_cast<T>(b.y);
  const T z = a.z * static_cast<T>(b.z);
  return (w + x + y + z);
}

template<typename T>
RAN_DEF Quat<T> inverse(const Quat<T>& q) noexcept {
  const T d = ::ran::dot(q, q);
  Quat<T> out;
  out.w = q.w / d;
  out.x = -q.x / d;
  out.y = -q.y / d;
  out.z = -q.z / d;
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> to_mat3(const Quat<T>& q) noexcept {
  const T qxx = q.x * q.x;
  const T qyy = q.y * q.y;
  const T qzz = q.z * q.z;
  const T qxz = q.x * q.z;
  const T qxy = q.x * q.y;
  const T qyz = q.y * q.z;
  const T qwx = q.w * q.x;
  const T qwy = q.w * q.y;
  const T qwz = q.w * q.z;

  Mat<3, 3, T> out;
  out.x1 = T(1) - (T(2) * (qyy + qzz));
  out.y1 = T(2) * (qxy + qwz);
  out.z1 = T(2) * (qxz - qwy);
  out.x2 = T(2) * (qxy - qwz);
  out.y2 = T(1) - (T(2) * (qxx + qzz));
  out.z2 = T(2) * (qyz + qwx);
  out.x3 = T(2) * (qxz + qwy);
  out.y3 = T(2) * (qyz - qwx);
  out.z3 = T(1) - (T(2) * (qxx + qyy));
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> to_mat4(const Quat<T>& q) noexcept {
  const T qxx = q.x * q.x;
  const T qyy = q.y * q.y;
  const T qzz = q.z * q.z;
  const T qxz = q.x * q.z;
  const T qxy = q.x * q.y;
  const T qyz = q.y * q.z;
  const T qwx = q.w * q.x;
  const T qwy = q.w * q.y;
  const T qwz = q.w * q.z;

  Mat<4, 4, T> out;
  out.x1 = T(1) - (T(2) * (qyy + qzz));
  out.y1 = T(2) * (qxy + qwz);
  out.z1 = T(2) * (qxz - qwy);
  out.w1 = T(0);
  out.x2 = T(2) * (qxy - qwz);
  out.y2 = T(1) - (T(2) * (qxx + qzz));
  out.z2 = T(2) * (qyz + qwx);
  out.w2 = T(0);
  out.x3 = T(2) * (qxz + qwy);
  out.y3 = T(2) * (qyz - qwx);
  out.z3 = T(1) - (T(2) * (qxx + qyy));
  out.w3 = T(0);
  out.x4 = T(0);
  out.y4 = T(0);
  out.z4 = T(0);
  out.w4 = T(1);
  return out;
}

template<typename T>
RAN_DEF Quat<T> to_quat(const Mat<3, 3, T>& m) noexcept {
  const auto [biggest, idx] = [](auto&& m) -> std::pair<T, u32> {
    const T x2m1 = m.x1 - m.x2 - m.x3;
    const T y2m1 = m.y2 - m.x1 - m.z3;
    const T z2m1 = m.z3 - m.x1 - m.y2;
    const T w2m1 = m.x1 + m.y2 + m.z3;
    u32 idx = 0;
    T biggest = w2m1;
    if (x2m1 > biggest) {
      biggest = x2m1;
      idx = 1;
    }
    if (y2m1 > biggest) {
      biggest = y2m1;
      idx = 2;
    }
    if (z2m1 > biggest) {
      biggest = z2m1;
      idx = 3;
    }
    return {::ran::sqrt(biggest + T(1)) * T(0.5), idx};
  }(m);

  const T mult = T(0.25) / biggest;
  const T y3z2m = (m.y3 - m.z2) * mult;
  const T z1x3m = (m.z1 - m.x3) * mult;
  const T y2x1m = (m.y2 - m.x1) * mult;
  const T y2x2p = (m.y2 + m.x1) * mult;
  const T z1x3p = (m.z1 + m.x3) * mult;
  const T y3z2p = (m.y3 + m.z2) * mult;
  Quat<T> out[] = {
    {biggest, y3z2m, z1x3m, y2x1m},
    {y3z2m, biggest, y2x2p, z1x3p},
    {z1x3m, y2x2p, biggest, y3z2p},
    {y2x1m, z1x3p, y3z2p, biggest},
  };
  return out[idx];
}

template<typename T>
RAN_DEF Quat<T> to_quat(const Mat<4, 4, T>& m) noexcept {
  return ::ran::to_quat(::ran::to_mat3(m));
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Quat<T> to_quat(T angle, const Vec<3, U>& axis) noexcept {
  const Vec<3, U> norm = ::ran::normalize(axis);
  Quat<T> out;
  out.w = ::ran::cos(angle * T(0.5));
  out.x = ::ran::sin(angle * T(0.5)) * axis.x;
  out.y = ::ran::sin(angle * T(0.5)) * axis.y;
  out.z = ::ran::sin(angle * T(0.5)) * axis.z;
  return out;
}

template<typename T>
RAN_DEF Quat<T> to_quat(const Vec<3, T>& euler) noexcept {
  const T cx = ::ran::cos(euler.x * T(0.5));
  const T cy = ::ran::cos(euler.y * T(0.5));
  const T cz = ::ran::cos(euler.z * T(0.5));
  const T sx = ::ran::sin(euler.x * T(0.5));
  const T sy = ::ran::sin(euler.y * T(0.5));
  const T sz = ::ran::sin(euler.z * T(0.5));

  Quat<T> out;
  out.w = (cx * cy * cz) + (sx * sy * sz);
  out.x = (sx * cy * cz) - (cx * sy * sz);
  out.y = (cx * sy * cz) + (sx * cy * sz);
  out.z = (cx * cy * sz) - (sx * sy * cz);
  return out;
}

template<typename T>
RAN_DEF T roll(const Quat<T>& q) noexcept {
  const T y = T(2) * ((q.x * q.y) + (q.w * q.z));
  const T x = (q.w * q.w) + (q.x * q.x) - (q.y * q.y) - (q.z * q.z);
  return ::ran::atan2(y, x);
}

template<typename T>
RAN_DEF T pitch(const Quat<T>& q) noexcept {
  const T y = T(2) * ((q.y * q.z) + (q.w * q.x));
  const T x = (q.w * q.w) - (q.x * q.x) - (q.y * q.y) + (q.z * q.z);

  const bool singularity = [](auto&& x, auto&& y) -> bool {
    if constexpr (std::floating_point<T>) {
      return ::ran::fequal(x, T(0)) && ::ran::fequal(y, T(0));
    } else {
      return (x == T(0)) && (y == T(0));
    }
  }(x, y);

  return singularity ? (T(2) * ::ran::atan2(q.x, q.w)) : ::ran::atan2(y, x);
}

template<typename T>
RAN_DEF T yaw(const Quat<T>& q) noexcept {
  const T v = T(-2) * ((q.x * q.z) - (q.w * q.y));
  return ::ran::asin(::ran::clamp(v, T(-1), T(1)));
}

template<typename T>
RAN_DEF Vec<3, T> to_euler(const Quat<T>& q) noexcept {
  Vec<3, T> out;
  out.x = ::ran::pitch(q);
  out.y = ::ran::yaw(q);
  out.z = ::ran::roll(q);
  return out;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>::Quat(const Vec<3, U>& euler) noexcept : Quat(::ran::to_quat(euler)) {}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>::Quat(const Mat<3, 3, U>& m) noexcept : Quat(::ran::to_quat(m)) {}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Quat<T>::Quat(const Mat<4, 4, U>& m) noexcept : Quat(::ran::to_quat(m)) {}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator*(const Vec<3, U>& v, const Quat<T>& q) noexcept {
  return ::ran::inverse(q) * v;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator*(const Vec<4, U>& v, const Quat<T>& q) noexcept {
  return ::ran::inverse(q) * v;
}

} // namespace ran

#endif // #ifndef RAN_QUATERNION_HPP_
