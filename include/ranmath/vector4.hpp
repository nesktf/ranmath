#ifndef RAN_VECTOR4_HPP_
#define RAN_VECTOR4_HPP_

#include "./forward.hpp"

namespace ran {

template<meta::numeric_type T>
struct Vec<4, T> {
public:
  using value_type = T;
  static RAN_CONSTEXPR u32 component_count = 4;

public:
  RAN_DEFAULT_SPECIAL(Vec);

  RAN_DEF Vec(T x_, T y_, T z_, T w_) noexcept : x(x_), y(y_), z(z_), w(w_) {}

  template<meta::numeric_convertible<T> U>
  RAN_DEF explicit Vec(U scalar) noexcept :
      x(static_cast<T>(scalar)), y(static_cast<T>(scalar)), z(static_cast<T>(scalar)),
      w(static_cast<T>(scalar)) {}

  template<meta::numeric_convertible<T> X, meta::numeric_convertible<T> Y,
           meta::numeric_convertible<T> Z, meta::numeric_convertible<T> W>
  RAN_DEF Vec(X x_, Y y_, Z z_, W w_) noexcept :
      x(static_cast<T>(x_)), y(static_cast<T>(y_)), z(static_cast<T>(z_)), w(static_cast<T>(w_)) {}

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
      case 3:
        return w;
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
  RAN_DECL Vec& operator=(const Vec<4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator+=(const Vec<4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator-=(const Vec<4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator*=(const Vec<4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator/=(const Vec<4, U>& other) noexcept;

public:
  T x, y, z, w;
};

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator=(U scalar) noexcept {
  this->x = static_cast<T>(scalar);
  this->y = static_cast<T>(scalar);
  this->z = static_cast<T>(scalar);
  this->w = static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator+=(U scalar) noexcept {
  this->x += static_cast<T>(scalar);
  this->y += static_cast<T>(scalar);
  this->z += static_cast<T>(scalar);
  this->w += static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator-=(U scalar) noexcept {
  this->x -= static_cast<T>(scalar);
  this->y -= static_cast<T>(scalar);
  this->z -= static_cast<T>(scalar);
  this->w -= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator*=(U scalar) noexcept {
  this->x *= static_cast<T>(scalar);
  this->y *= static_cast<T>(scalar);
  this->z *= static_cast<T>(scalar);
  this->w *= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator/=(U scalar) noexcept {
  this->x /= static_cast<T>(scalar);
  this->y /= static_cast<T>(scalar);
  this->z /= static_cast<T>(scalar);
  this->w /= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator=(const Vec<4, U>& other) noexcept {
  this->x = static_cast<T>(other.x);
  this->y = static_cast<T>(other.y);
  this->z = static_cast<T>(other.z);
  this->w = static_cast<T>(other.w);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator+=(const Vec<4, U>& other) noexcept {
  this->x += static_cast<T>(other.x);
  this->y += static_cast<T>(other.y);
  this->z += static_cast<T>(other.z);
  this->w += static_cast<T>(other.w);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator-=(const Vec<4, U>& other) noexcept {
  this->x -= static_cast<T>(other.x);
  this->y -= static_cast<T>(other.y);
  this->z -= static_cast<T>(other.z);
  this->w -= static_cast<T>(other.w);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator*=(const Vec<4, U>& other) noexcept {
  this->x *= static_cast<T>(other.x);
  this->y *= static_cast<T>(other.y);
  this->z *= static_cast<T>(other.z);
  this->w *= static_cast<T>(other.w);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T>& Vec<4, T>::operator/=(const Vec<4, U>& other) noexcept {
  this->x /= static_cast<T>(other.x);
  this->y /= static_cast<T>(other.y);
  this->z /= static_cast<T>(other.z);
  this->w /= static_cast<T>(other.w);
  return *this;
}

template<typename T>
RAN_DEF bool operator==(const Vec<4, T>& a, const Vec<4, T>& b) noexcept {
  return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
}

template<typename T>
RAN_DEF bool operator!=(const Vec<4, T>& a, const Vec<4, T>& b) noexcept {
  return (a.x != b.x) || (a.y != b.y) || (a.z != b.z) || (a.w != b.w);
}

template<typename T>
RAN_DEF Vec<4, T> operator+(const Vec<4, T>& vec) noexcept {
  Vec<4, T> out;
  out.x = +vec.x;
  out.y = +vec.y;
  out.z = +vec.z;
  out.w = +vec.w;
  return out;
}

template<typename T>
RAN_DEF Vec<4, T> operator+(const Vec<4, T>& a, const Vec<4, T>& b) noexcept {
  Vec<4, T> out;
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  out.z = a.z + b.z;
  out.w = a.w + b.w;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator+(const Vec<4, T>& vec, U scalar) noexcept {
  Vec<4, T> out;
  out.x = vec.x + static_cast<T>(scalar);
  out.y = vec.y + static_cast<T>(scalar);
  out.z = vec.z + static_cast<T>(scalar);
  out.w = vec.w + static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator+(U scalar, const Vec<4, T>& vec) noexcept {
  Vec<4, T> out;
  out.x = static_cast<T>(scalar) + vec.x;
  out.y = static_cast<T>(scalar) + vec.y;
  out.z = static_cast<T>(scalar) + vec.z;
  out.w = static_cast<T>(scalar) + vec.w;
  return out;
}

template<typename T>
RAN_DEF Vec<4, T> operator-(const Vec<4, T>& vec) noexcept {
  Vec<4, T> out;
  out.x = -vec.x;
  out.y = -vec.y;
  out.z = -vec.z;
  out.w = -vec.w;
  return out;
}

template<typename T>
RAN_DEF Vec<4, T> operator-(const Vec<4, T>& a, const Vec<4, T>& b) noexcept {
  Vec<4, T> out;
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  out.z = a.z - b.z;
  out.w = a.w - b.w;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator-(const Vec<4, T>& vec, U scalar) noexcept {
  Vec<4, T> out;
  out.x = vec.x - static_cast<T>(scalar);
  out.y = vec.y - static_cast<T>(scalar);
  out.z = vec.z - static_cast<T>(scalar);
  out.w = vec.w - static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator-(U scalar, const Vec<4, T>& vec) noexcept {
  Vec<4, T> out;
  out.x = static_cast<T>(scalar) - vec.x;
  out.y = static_cast<T>(scalar) - vec.y;
  out.z = static_cast<T>(scalar) - vec.z;
  out.w = static_cast<T>(scalar) - vec.w;
  return out;
}

template<typename T>
RAN_DEF Vec<4, T> operator*(const Vec<4, T>& a, const Vec<4, T>& b) noexcept {
  Vec<4, T> out;
  out.x = a.x * b.x;
  out.y = a.y * b.y;
  out.z = a.z * b.z;
  out.w = a.w * b.w;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator*(const Vec<4, T>& vec, U scalar) noexcept {
  Vec<4, T> out;
  out.x = vec.x * static_cast<T>(scalar);
  out.y = vec.y * static_cast<T>(scalar);
  out.z = vec.z * static_cast<T>(scalar);
  out.w = vec.w * static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator*(U scalar, const Vec<4, T>& vec) noexcept {
  Vec<4, T> out;
  out.x = static_cast<T>(scalar) * vec.x;
  out.y = static_cast<T>(scalar) * vec.y;
  out.z = static_cast<T>(scalar) * vec.z;
  out.w = static_cast<T>(scalar) * vec.w;
  return out;
}

template<typename T>
RAN_DEF Vec<4, T> operator/(const Vec<4, T>& a, const Vec<4, T>& b) noexcept {
  Vec<4, T> out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  out.z = a.z / b.z;
  out.w = a.w / b.w;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator/(const Vec<4, T>& vec, U scalar) noexcept {
  Vec<4, T> out;
  out.x = vec.x / static_cast<T>(scalar);
  out.y = vec.y / static_cast<T>(scalar);
  out.z = vec.z / static_cast<T>(scalar);
  out.w = vec.w / static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<4, T> operator/(U scalar, const Vec<4, T>& vec) noexcept {
  Vec<4, T> out;
  out.x = static_cast<T>(scalar) / vec.x;
  out.y = static_cast<T>(scalar) / vec.y;
  out.z = static_cast<T>(scalar) / vec.z;
  out.w = static_cast<T>(scalar) / vec.w;
  return out;
}

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DEF Vec<4, U> vec_cast(const Vec<4, T>& vec) noexcept {
  return {static_cast<U>(vec.x), static_cast<U>(vec.y), static_cast<U>(vec.z),
          static_cast<U>(vec.z)};
}

template<typename T>
RAN_DEF T length2(const Vec<4, T>& vec) noexcept {
  return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w);
}

template<typename T>
RAN_DEF T length(const Vec<4, T>& vec) noexcept {
  return ::ran::sqrt((vec.x * vec.c) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w));
}

template<typename T>
RAN_DEF void normalize_at(Vec<4, T>& vec) noexcept {
  const T len = ::ran::length(vec);
  vec.x /= len;
  vec.y /= len;
  vec.z /= len;
  vec.w /= len;
}

template<typename T>
RAN_DEF Vec<4, T> normalize(const Vec<4, T>& vec) noexcept {
  Vec<4, T> out;
  const T len = ::ran::length(vec);
  out.x = vec.x / len;
  out.y = vec.y / len;
  out.z = vec.z / len;
  out.w = vec.w / len;
  return out;
}

template<typename T>
RAN_DEF T dot(const Vec<4, T>& a, const Vec<4, T>& b) noexcept {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

} // namespace ran

#endif // #ifndef RAN_VECTOR4_HPP_
