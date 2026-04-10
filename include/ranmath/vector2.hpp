#ifndef RAN_VECTOR2_HPP_
#define RAN_VECTOR2_HPP_

#include <ranmath/forward.hpp>

namespace ran {

template<meta::numeric_type T>
struct Vec<2, T> {
public:
  using value_type = T;
  static RAN_CONSTEXPR u32 component_count = 2;

public:
  RAN_DEFAULT_SPECIAL(Vec);

  RAN_DEF Vec(T x_, T y_) noexcept : x(x_), y(y_) {}

  RAN_DEF explicit Vec(T scalar) noexcept : x(scalar), y(scalar) {}

  template<meta::numeric_convertible<T> U>
  RAN_DECL explicit Vec(U scalar) noexcept :
      x(static_cast<T>(scalar)), y(static_cast<T>(scalar)) {}

  template<meta::numeric_type X, meta::numeric_type Y>
  RAN_DECL Vec(X x_, Y y_) noexcept : x(static_cast<T>(x_)), y(static_cast<T>(y_)) {}

public:
  RAN_DEF const T& operator[](size_t idx) const noexcept {
    switch (idx) {
      default:
        [[fallthrough]];
      case 0:
        return x;
      case 1:
        return y;
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
  RAN_DECL Vec& operator=(const Vec<2, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator+=(const Vec<2, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator-=(const Vec<2, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator*=(const Vec<2, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Vec& operator/=(const Vec<2, U>& other) noexcept;

public:
  T x, y;
};

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator=(U scalar) noexcept {
  this->x = static_cast<T>(scalar);
  this->y = static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator+=(U scalar) noexcept {
  this->x += static_cast<T>(scalar);
  this->y += static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator-=(U scalar) noexcept {
  this->x -= static_cast<T>(scalar);
  this->y -= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator*=(U scalar) noexcept {
  this->x *= static_cast<T>(scalar);
  this->y *= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator/=(U scalar) noexcept {
  this->x /= static_cast<T>(scalar);
  this->y /= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator=(const Vec<2, U>& other) noexcept {
  this->x = static_cast<T>(other.x);
  this->y = static_cast<T>(other.y);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator+=(const Vec<2, U>& other) noexcept {
  this->x += static_cast<T>(other.x);
  this->y += static_cast<T>(other.y);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator-=(const Vec<2, U>& other) noexcept {
  this->x -= static_cast<T>(other.x);
  this->y -= static_cast<T>(other.y);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator*=(const Vec<2, U>& other) noexcept {
  this->x *= static_cast<T>(other.x);
  this->y *= static_cast<T>(other.y);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T>& Vec<2, T>::operator/=(const Vec<2, U>& other) noexcept {
  this->x /= static_cast<T>(other.x);
  this->y /= static_cast<T>(other.y);
  return *this;
}

template<typename T>
RAN_DEF Vec<2, T> operator==(const Vec<2, T>& a, const Vec<2, T>& b) noexcept {
  return (a.x == b.x) && (a.y == b.y);
}

template<typename T>
RAN_DEF Vec<2, T> operator!=(const Vec<2, T>& a, const Vec<2, T>& b) noexcept {
  return (a.x != b.x) || (a.y != b.y);
}

template<typename T>
RAN_DEF Vec<2, T> operator+(const Vec<2, T>& vec) noexcept {
  Vec<2, T> out;
  out.x = +vec.x;
  out.y = +vec.y;
  return out;
}

template<typename T>
RAN_DEF Vec<2, T> operator+(const Vec<2, T>& a, const Vec<2, T>& b) noexcept {
  Vec<2, T> out;
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator+(const Vec<2, T>& vec, U scalar) noexcept {
  Vec<2, T> out;
  out.x = vec.x + static_cast<T>(scalar);
  out.y = vec.y + static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator+(U scalar, const Vec<2, T>& vec) noexcept {
  Vec<2, T> out;
  out.x = static_cast<T>(scalar) * vec.x;
  out.y = static_cast<T>(scalar) + vec.y;
  return out;
}

template<typename T>
RAN_DEF Vec<2, T> operator-(const Vec<2, T>& vec) noexcept {
  Vec<2, T> out;
  out.x = -vec.x;
  out.y = -vec.y;
  return out;
}

template<typename T>
RAN_DEF Vec<2, T> operator-(const Vec<2, T>& a, const Vec<2, T>& b) noexcept {
  Vec<2, T> out;
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator-(const Vec<2, T>& vec, U scalar) noexcept {
  Vec<2, T> out;
  out.x = vec.x - static_cast<T>(scalar);
  out.y = vec.y - static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator-(U scalar, const Vec<2, T>& vec) noexcept {
  Vec<2, T> out;
  out.x = static_cast<T>(scalar) - vec.x;
  out.y = static_cast<T>(scalar) - vec.y;
  return out;
}

template<typename T>
RAN_DEF Vec<2, T> operator*(const Vec<2, T>& a, const Vec<2, T>& b) noexcept {
  Vec<2, T> out;
  out.x = a.x * b.x;
  out.y = a.y * b.y;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator*(const Vec<2, T>& vec, U scalar) noexcept {
  Vec<2, T> out;
  out.x = vec.x * static_cast<T>(scalar);
  out.y = vec.y * static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator*(U scalar, const Vec<2, T>& vec) noexcept {
  Vec<2, T> out;
  out.x = static_cast<T>(scalar) * vec.x;
  out.y = static_cast<T>(scalar) * vec.y;
  return out;
}

template<typename T>
RAN_DEF Vec<2, T> operator/(const Vec<2, T>& a, const Vec<2, T>& b) noexcept {
  Vec<2, T> out;
  out.x = a.x / b.x;
  out.y = a.y / b.y;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator/(const Vec<2, T>& vec, U scalar) noexcept {
  Vec<2, T> out;
  out.x = vec.x / static_cast<T>(scalar);
  out.y = vec.y / static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Vec<2, T> operator/(U scalar, const Vec<2, T>& vec) noexcept {
  Vec<2, T> out;
  out.x = static_cast<T>(scalar) / vec.x;
  out.y = static_cast<T>(scalar) / vec.y;
  return out;
}

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DEF Vec<2, U> vec_cast(const Vec<2, T>& vec) noexcept {
  return {static_cast<U>(vec.x), static_cast<U>(vec.y)};
}

template<typename T>
RAN_DEF T length2(const Vec<2, T>& vec) noexcept {
  return (vec.x * vec.x) + (vec.y * vec.y);
}

template<typename T>
RAN_DEF T length(const Vec<2, T>& vec) noexcept {
  return ::ran::sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

template<typename T>
RAN_DEF void normalize_at(Vec<2, T>& vec) noexcept {
  const T len = ::ran::length(vec);
  vec.x /= len;
  vec.y /= len;
}

template<typename T>
RAN_DEF Vec<2, T> normalize(const Vec<2, T>& vec) noexcept {
  Vec<2, T> out;
  const T len = ::ran::length(vec);
  out.x = vec.x / len;
  out.y = vec.y / len;
  return out;
}

template<typename T>
RAN_DEF T dot(const Vec<2, T>& a, const Vec<2, T>& b) noexcept {
  return (a.x * b.x) + (a.y * b.y);
}

} // namespace ran

#endif // #ifndef RAN_VECTOR2_HPP_
