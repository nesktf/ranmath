#pragma once

#include "./forward.hpp"

namespace ran {

template<meta::numeric_type T>
struct Vec<3, T> {
public:
  using value_type = T;
  static RAN_CONSTEXPR u32 component_count = 3;

public:
  RAN_DEFAULT_SPECIAL(Vec);

  RAN_DEF Vec(T x_, T y_, T z_) noexcept : x(x_), y(y_), z(z_) {}

  RAN_DEF explicit Vec(T scalar) noexcept : x(scalar), y(scalar), z(scalar) {}

  template<meta::numeric_convertible<T> U>
  RAN_DEF explicit Vec(U scalar) noexcept :
      x(static_cast<T>(scalar)), y(static_cast<T>(scalar)), z(static_cast<T>(scalar)) {}

  template<meta::numeric_convertible<T> X, meta::numeric_convertible<T> Y,
           meta::numeric_convertible<T> Z>
  RAN_DEF Vec(X x_, Y y_, Z z_) noexcept :
      x(static_cast<T>(x_)), y(static_cast<T>(y_)), z(static_cast<T>(z_)) {}

public:
  RAN_DEF const T& operator[](size_t idx) const noexcept {
    switch (idx) {
      default:
        [[fallthrough]];
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
    }
  }

  RAN_DEF T& operator[](size_t idx) noexcept { return const_cast<T&>(std::as_const(*this)[idx]); }

public:
  RAN_DEF const T* data() const noexcept { return &this->x; }

  RAN_DEF T* data() noexcept { return const_cast<T*>(std::as_const(*this).data()); }

public:
  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator+=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator-=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator*=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator/=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator=(const Vec<3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator+=(const Vec<3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator-=(const Vec<3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator*=(const Vec<3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator/=(const Vec<3, U>& other) noexcept;

public:
  T x, y, z;
};

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator=(U scalar) noexcept {
  this->x = static_cast<T>(scalar);
  this->y = static_cast<T>(scalar);
  this->z = static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator+=(U scalar) noexcept {
  this->x += static_cast<T>(scalar);
  this->y += static_cast<T>(scalar);
  this->z += static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator-=(U scalar) noexcept {
  this->x -= static_cast<T>(scalar);
  this->y -= static_cast<T>(scalar);
  this->z -= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator*=(U scalar) noexcept {
  this->x *= static_cast<T>(scalar);
  this->y *= static_cast<T>(scalar);
  this->z *= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator/=(U scalar) noexcept {
  this->x /= static_cast<T>(scalar);
  this->y /= static_cast<T>(scalar);
  this->z /= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator=(const Vec<3, U>& other) noexcept {
  this->x = static_cast<T>(other.x);
  this->y = static_cast<T>(other.y);
  this->z = static_cast<T>(other.z);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator+=(const Vec<3, U>& other) noexcept {
  this->x += static_cast<T>(other.x);
  this->y += static_cast<T>(other.y);
  this->z += static_cast<T>(other.z);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator-=(const Vec<3, U>& other) noexcept {
  this->x -= static_cast<T>(other.x);
  this->y -= static_cast<T>(other.y);
  this->z -= static_cast<T>(other.z);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator*=(const Vec<3, U>& other) noexcept {
  this->x *= static_cast<T>(other.x);
  this->y *= static_cast<T>(other.y);
  this->z *= static_cast<T>(other.z);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T>& Vec<3, T>::operator/=(const Vec<3, U>& other) noexcept {
  this->x /= static_cast<T>(other.x);
  this->y /= static_cast<T>(other.y);
  this->z /= static_cast<T>(other.z);
  return *this;
}

template<typename T>
RAN_DEF bool operator==(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

template<typename T>
RAN_DEF bool operator!=(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  return (a.x != b.x) || (a.y != b.y) || (a.z != b.z);
}

template<typename T>
RAN_DEF Vec<3, T> operator+(const Vec<3, T>& vec) noexcept {
  Vec<3, T> out;
  out.x = +vec.x;
  out.y = +vec.y;
  out.z = +vec.z;
  return out;
}

template<typename T>
RAN_DEF Vec<3, T> operator+(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  Vec<3, T> out;
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  out.z = a.z + b.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator+(const Vec<3, T>& vec, U scalar) noexcept {
  Vec<3, T> out;
  out.x = vec.x + static_cast<T>(scalar);
  out.y = vec.y + static_cast<T>(scalar);
  out.z = vec.z + static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator+(U scalar, const Vec<3, T>& vec) noexcept {
  Vec<3, T> out;
  out.x = static_cast<T>(scalar) + vec.x;
  out.y = static_cast<T>(scalar) + vec.y;
  out.z = static_cast<T>(scalar) + vec.z;
  return out;
}

template<typename T>
RAN_DEF Vec<3, T> operator-(const Vec<3, T>& vec) noexcept {
  Vec<3, T> out;
  out.x = -vec.x;
  out.y = -vec.y;
  out.z = -vec.z;
  return out;
}

template<typename T>
RAN_DEF Vec<3, T> operator-(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  Vec<3, T> out;
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  out.z = a.z - b.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator-(const Vec<3, T>& vec, U scalar) noexcept {
  Vec<3, T> out;
  out.x = vec.x - static_cast<T>(scalar);
  out.y = vec.y - static_cast<T>(scalar);
  out.z = vec.z - static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator-(U scalar, const Vec<3, T>& vec) noexcept {
  Vec<3, T> out;
  out.x = static_cast<T>(scalar) - vec.x;
  out.y = static_cast<T>(scalar) - vec.y;
  out.z = static_cast<T>(scalar) - vec.z;
  return out;
}

template<typename T>
RAN_DEF Vec<3, T> operator*(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  Vec<3, T> out;
  out.x = a.x * b.x;
  out.y = a.y * b.y;
  out.z = a.z * b.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator*(const Vec<3, T>& vec, U scalar) noexcept {
  Vec<3, T> out;
  out.x = vec.x * static_cast<T>(scalar);
  out.y = vec.y * static_cast<T>(scalar);
  out.z = vec.z * static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator*(U scalar, const Vec<3, T>& vec) noexcept {
  Vec<3, T> out = vec;
  out.x = static_cast<T>(scalar) * vec.x;
  out.y = static_cast<T>(scalar) * vec.y;
  out.z = static_cast<T>(scalar) * vec.z;
  return out;
}

template<typename T>
RAN_DEF Vec<3, T> operator/(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  Vec<3, T> out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  out.z = a.z / b.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator/(const Vec<3, T>& vec, U scalar) noexcept {
  Vec<3, T> out;
  out.x = vec.x / static_cast<T>(scalar);
  out.y = vec.y / static_cast<T>(scalar);
  out.z = vec.z / static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<3, T> operator/(U scalar, const Vec<3, T>& vec) noexcept {
  Vec<3, T> out = vec;
  out.x = static_cast<T>(scalar) / vec.x;
  out.y = static_cast<T>(scalar) / vec.y;
  out.z = static_cast<T>(scalar) / vec.z;
  return out;
}

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DEF Vec<3, U> vec_cast(const Vec<3, T>& vec) noexcept {
  return {static_cast<U>(vec.x), static_cast<U>(vec.y), static_cast<U>(vec.z)};
}

template<typename T>
RAN_DEF T length2(const Vec<3, T>& vec) noexcept {
  return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
}

template<typename T>
RAN_DEF T length(const Vec<3, T>& vec) noexcept {
  return ::ran::sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

template<typename T>
RAN_DEF void normalize_at(Vec<3, T>& vec) noexcept {
  const T len = ::ran::length(vec);
  vec.x /= len;
  vec.y /= len;
  vec.z /= len;
}

template<typename T>
RAN_DEF Vec<3, T> normalize(const Vec<3, T>& vec) noexcept {
  Vec<3, T> out;
  const T len = ::ran::length(vec);
  out.x = vec.x / len;
  out.y = vec.y / len;
  out.z = vec.z / len;
  return out;
}

template<typename T>
RAN_DEF T dot(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

template<typename T>
RAN_DEF Vec<3, T> cross(const Vec<3, T>& a, const Vec<3, T>& b) noexcept {
  Vec<3, T> out;
  out.x = (a.y * b.z) - (b.y * a.z);
  out.y = (a.z * b.x) - (b.z * a.x);
  out.z = (a.x * b.y) - (b.x * a.y);
  return out;
}

template<meta::numeric_type T>
RAN_DEF void gl_to_cartesian_at(Vec<3, T>& vec) noexcept {
  const T x = vec.x;
  vec.x = vec.z;
  vec.z = vec.y;
  vec.y = x;
}

template<typename T>
RAN_DEF Vec<3, T> gl_to_cartesian(const Vec<3, T>& vec) noexcept {
  Vec<3, T> out;
  out.x = vec.z;
  out.y = vec.x;
  out.z = vec.y;
  return out;
}

template<meta::numeric_type T>
RAN_DEF Vec<3, T> sph_to_cartesian(T rho, T theta, T phi) noexcept {
  Vec<3, T> out;
  out.x = rho * ::ran::sin(theta) * ::ran::cos(phi);
  out.y = rho * ::ran::sin(theta) * ::ran::sin(phi);
  out.z = rho * ::ran::cos(theta);
  return out;
}

template<meta::numeric_type T>
RAN_DEF void cartesian_to_gl_at(Vec<3, T>& vec) noexcept {
  const T x = vec.x;
  vec.x = vec.y;
  vec.y = vec.z;
  vec.z = x;
}

template<typename T>
RAN_DEF Vec<3, T> cartesian_to_gl(const Vec<3, T>& vec) noexcept {
  Vec<3, T> out;
  out.x = vec.y;
  out.y = vec.z;
  out.z = vec.x;
  return out;
}

} // namespace ran
