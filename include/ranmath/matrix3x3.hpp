#pragma once

#include "./forward.hpp"

namespace ran {

template<meta::numeric_type T>
struct Mat<3, 3, T> {
public:
  using value_type = T;
  static RAN_CONSTEXPR u32 component_count = 9;

  using row_type = Vec<3, T>;
  using col_type = Vec<3, T>;

  static RAN_CONSTEXPR Mat identity() noexcept { return Mat{T(1)}; }

public:
  RAN_DEFAULT_SPECIAL(Mat);

  RAN_DEF explicit Mat(T scalar) noexcept :
      x1(scalar), y1(), z1(), x2(), y2(scalar), z2(), x3(), y3(), z3(scalar) {}

  template<meta::numeric_convertible<T> U>
  RAN_DEF explicit Mat(U scalar) noexcept :
      x1(static_cast<T>(scalar)), y1(), z1(), x2(), y2(static_cast<T>(scalar)), z2(), x3(), y3(),
      z3(static_cast<T>(scalar)) {}

  RAN_DEF Mat(T x1_, T y1_, T z1_, T x2_, T y2_, T z2_, T x3_, T y3_, T z3_) noexcept :
      x1(x1_), y1(y1_), z1(z1_), x2(x2_), y2(y2_), z2(z2_), x3(x3_), y3(y3_), z3(z3_) {}

  template<typename X1, typename Y1, typename Z1, typename X2, typename Y2, typename Z2,
           typename X3, typename Y3, typename Z3>
  RAN_DEF Mat(X1 x1_, Y1 y1_, Z1 z1_, X2 x2_, Y2 y2_, Z2 z2_, X3 x3_, Y3 y3_, Z3 z3_) noexcept :
      x1(static_cast<T>(x1_)), y1(static_cast<T>(y1_)), z1(static_cast<T>(z1_)),
      x2(static_cast<T>(x2_)), y2(static_cast<T>(y2_)), z2(static_cast<T>(z2_)),
      x3(static_cast<T>(x3_)), y3(static_cast<T>(y3_)), z3(static_cast<T>(z3_)) {}

  template<typename V1, typename V2, typename V3>
  RAN_DEF Mat(const Vec<3, V1>& v1, const Vec<3, V2>& v2, const Vec<3, V3>& v3) noexcept :
      x1(static_cast<T>(v1.x)), y1(static_cast<T>(v1.y)), z1(static_cast<T>(v1.z)),
      x2(static_cast<T>(v2.x)), y2(static_cast<T>(v2.y)), z2(static_cast<T>(v2.z)),
      x3(static_cast<T>(v3.x)), y3(static_cast<T>(v3.y)), z3(static_cast<T>(v3.z)) {}

public:
  RAN_DEF const T& operator[](size_t idx) const noexcept {
    switch (idx) {
      default:
        [[fallthrough]];
      case 0:
        return x1;
      case 1:
        return y1;
      case 2:
        return z1;
      case 3:
        return x2;
      case 4:
        return y2;
      case 5:
        return z2;
      case 6:
        return x3;
      case 7:
        return y3;
      case 8:
        return z3;
    }
  }

  RAN_DEF T& operator[](size_t idx) noexcept { return const_cast<T&>(std::as_const(*this)[idx]); }

  RAN_DEF col_type column_at(size_t idx) const noexcept {
    switch (idx) {
      default:
        [[fallthrough]];
      case 0:
        return {x1, y1, z1};
      case 1:
        return {x2, y2, z2};
      case 2:
        return {x3, y3, z3};
    }
  }

  RAN_DEF row_type row_at(size_t idx) const noexcept {
    switch (idx) {
      default:
        [[fallthrough]];
      case 0:
        return {x1, x2, x3};
      case 1:
        return {y1, y2, y3};
      case 2:
        return {z1, z2, z3};
    }
  }

public:
  RAN_DEF const T* data() const noexcept { return &this->x1; }

  RAN_DEF T* data() noexcept { return const_cast<T*>(std::as_const(*this).data()); }

public:
  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator+=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator-=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator*=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator/=(U scalar) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator=(const Mat<3, 3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator+=(const Mat<3, 3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator-=(const Mat<3, 3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator*=(const Mat<3, 3, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator/=(const Mat<3, 3, U>& other) noexcept;

public:
  // Column major ordering
  T x1, y1, z1;
  T x2, y2, z2;
  T x3, y3, z3;
};

template<typename T>
RAN_DEF T determinant(const Mat<3, 3, T>& m) noexcept {
  return ((m.x1 * m.y2 * m.z3) - (m.x1 * m.z2 * m.y3)) -
         ((m.x2 * m.y1 * m.z3) - (m.x2 * m.z1 * m.y3)) +
         ((m.x3 * m.y1 * m.z1) - (m.x3 * m.z1 * m.y2));
}

template<typename T>
RAN_DEF Mat<3, 3, T> inverse(const Mat<3, 3, T>& m) noexcept {
  const T invdet = static_cast<T>(1) / ::ran::determinant(m);
  Mat<3, 3, T> out;
  out.x1 = ((m.y2 * m.z3) - (m.z2 * m.y3)) * invdet;
  out.y1 = ((m.z1 * m.y3) - (m.y1 * m.z3)) * invdet;
  out.z1 = ((m.y1 * m.z2) - (m.z1 * m.y2)) * invdet;
  out.x2 = ((m.z2 * m.x3) - (m.x2 * m.z3)) * invdet;
  out.y2 = ((m.x1 * m.z3) - (m.z1 * m.x3)) * invdet;
  out.z2 = ((m.z1 * m.x2) - (m.x1 * m.z2)) * invdet;
  out.x3 = ((m.x2 * m.y3) - (m.y2 * m.x3)) * invdet;
  out.y3 = ((m.y1 * m.x3) - (m.x1 * m.y3)) * invdet;
  out.z3 = ((m.x1 * m.y2) - (m.y1 * m.x2)) * invdet;
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> transpose(const Mat<3, 3, T>& m) noexcept {
  Mat<3, 3, T> out;
  out.x1 = m.x1;
  out.y1 = m.x2;
  out.z1 = m.x3;
  out.x2 = m.y1;
  out.y2 = m.y2;
  out.z2 = m.y3;
  out.x3 = m.z1;
  out.y3 = m.z2;
  out.z3 = m.z3;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> translate(const Mat<3, 3, T>& m, const Vec<2, U>& v) noexcept {
  Mat<3, 3, T> out;
  out.x3 = (m.x1 * static_cast<T>(v.x)) + (m.x2 * static_cast<T>(v.y)) + m.x3;
  out.y3 = (m.y1 * static_cast<T>(v.x)) + (m.y2 * static_cast<T>(v.y)) + m.y3;
  out.z3 = (m.z1 * static_cast<T>(v.x)) + (m.z2 * static_cast<T>(v.y)) + m.z3;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> scale(const Mat<3, 3, T>& m, const Vec<2, U>& v) noexcept {
  Mat<3, 3, T> out;
  out.x1 = m.x1 * static_cast<T>(v.x);
  out.y1 = m.y1 * static_cast<T>(v.x);
  out.z1 = m.z1 * static_cast<T>(v.x);
  out.x2 = m.x2 * static_cast<T>(v.y);
  out.y2 = m.y2 * static_cast<T>(v.y);
  out.z2 = m.z2 * static_cast<T>(v.y);
  out.x3 = m.x3;
  out.y3 = m.y3;
  out.z3 = m.z3;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> rotate(const Mat<3, 3, T>& m, U angle) noexcept {
  const U c = ::ran::cos(angle);
  const U s = ::ran::sin(angle);
  Mat<3, 3, T> other;
  other.x1 = static_cast<T>(c);
  other.y1 = static_cast<T>(s);
  other.z1 = T(0);
  other.x2 = -static_cast<T>(s);
  other.y2 = static_cast<T>(c);
  other.z2 = T(0);
  other.x3 = T(0);
  other.y3 = T(0);
  other.z3 = T(1);
  return m * other;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> lookat_rh(const Vec<3, T>& dir, const Vec<3, U>& up) noexcept {
  const Vec<3, T> col3 = -dir;
  const Vec<3, T> right = ::ran::cross(::ran::vec_cast<T>(up), col3);
  const T r2 = ::ran::length2(right);
  const Vec<3, T> col1 = right * ::ran::rsqrt(::ran::max(T(0.000001), r2));
  const Vec<3, T> col2 = ::ran::cross(col3, col1);

  Mat<3, 3, T> out;
  out.x1 = col1.x;
  out.y1 = col1.y;
  out.z1 = col1.z;
  out.x2 = col2.x;
  out.y2 = col2.y;
  out.z2 = col2.z;
  out.x3 = col3.x;
  out.y3 = col3.y;
  out.z3 = col3.z;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> lookat_lh(const Vec<3, T>& dir, const Vec<3, U>& up) noexcept {
  const Vec<3, T> col3 = dir;
  const Vec<3, T> right = ::ran::cross(::ran::vec_cast<T>(up), col3);
  const T r2 = ::ran::length2(right);
  const Vec<3, T> col1 = right * ::ran::rsqrt(::ran::max(T(0.000001), r2));
  const Vec<3, T> col2 = ::ran::cross(col3, col1);

  Mat<3, 3, T> out;
  out.x1 = col1.x;
  out.y1 = col1.y;
  out.z1 = col1.z;
  out.x2 = col2.x;
  out.y2 = col2.y;
  out.z2 = col2.z;
  out.x3 = col3.x;
  out.y3 = col3.y;
  out.z3 = col3.z;
  return out;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator=(U scalar) noexcept {
  this->x1 = static_cast<T>(scalar);
  this->y1 = static_cast<T>(scalar);
  this->z1 = static_cast<T>(scalar);
  this->x2 = static_cast<T>(scalar);
  this->y2 = static_cast<T>(scalar);
  this->z2 = static_cast<T>(scalar);
  this->x3 = static_cast<T>(scalar);
  this->y3 = static_cast<T>(scalar);
  this->z3 = static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator+=(U scalar) noexcept {
  this->x1 += static_cast<T>(scalar);
  this->y1 += static_cast<T>(scalar);
  this->z1 += static_cast<T>(scalar);
  this->x2 += static_cast<T>(scalar);
  this->y2 += static_cast<T>(scalar);
  this->z2 += static_cast<T>(scalar);
  this->x3 += static_cast<T>(scalar);
  this->y3 += static_cast<T>(scalar);
  this->z3 += static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator-=(U scalar) noexcept {
  this->x1 -= static_cast<T>(scalar);
  this->y1 -= static_cast<T>(scalar);
  this->z1 -= static_cast<T>(scalar);
  this->x2 -= static_cast<T>(scalar);
  this->y2 -= static_cast<T>(scalar);
  this->z2 -= static_cast<T>(scalar);
  this->x3 -= static_cast<T>(scalar);
  this->y3 -= static_cast<T>(scalar);
  this->z3 -= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator*=(U scalar) noexcept {
  this->x1 *= static_cast<T>(scalar);
  this->y1 *= static_cast<T>(scalar);
  this->z1 *= static_cast<T>(scalar);
  this->x2 *= static_cast<T>(scalar);
  this->y2 *= static_cast<T>(scalar);
  this->z2 *= static_cast<T>(scalar);
  this->x3 *= static_cast<T>(scalar);
  this->y3 *= static_cast<T>(scalar);
  this->z3 *= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator/=(U scalar) noexcept {
  this->x1 /= static_cast<T>(scalar);
  this->y1 /= static_cast<T>(scalar);
  this->z1 /= static_cast<T>(scalar);
  this->x2 /= static_cast<T>(scalar);
  this->y2 /= static_cast<T>(scalar);
  this->z2 /= static_cast<T>(scalar);
  this->x3 /= static_cast<T>(scalar);
  this->y3 /= static_cast<T>(scalar);
  this->z3 /= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator=(const Mat<3, 3, U>& other) noexcept {
  this->x1 = static_cast<T>(other.x1);
  this->y1 = static_cast<T>(other.y1);
  this->z1 = static_cast<T>(other.z1);
  this->x2 = static_cast<T>(other.x2);
  this->y2 = static_cast<T>(other.y2);
  this->z2 = static_cast<T>(other.z2);
  this->x3 = static_cast<T>(other.x3);
  this->y3 = static_cast<T>(other.y3);
  this->z3 = static_cast<T>(other.z3);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator+=(const Mat<3, 3, U>& other) noexcept {
  this->x1 += static_cast<T>(other.x1);
  this->y1 += static_cast<T>(other.y1);
  this->z1 += static_cast<T>(other.z1);
  this->x2 += static_cast<T>(other.x2);
  this->y2 += static_cast<T>(other.y2);
  this->z2 += static_cast<T>(other.z2);
  this->x3 += static_cast<T>(other.x3);
  this->y3 += static_cast<T>(other.y3);
  this->z3 += static_cast<T>(other.z3);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator-=(const Mat<3, 3, U>& other) noexcept {
  this->x1 -= static_cast<T>(other.x1);
  this->y1 -= static_cast<T>(other.y1);
  this->z1 -= static_cast<T>(other.z1);
  this->x2 -= static_cast<T>(other.x2);
  this->y2 -= static_cast<T>(other.y2);
  this->z2 -= static_cast<T>(other.z2);
  this->x3 -= static_cast<T>(other.x3);
  this->y3 -= static_cast<T>(other.y3);
  this->z3 -= static_cast<T>(other.z3);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator*=(const Mat<3, 3, U>& m) noexcept {
  const Mat<3, 3, T> self = *this;
  this->x1 = (self.x1 * m.x1) + (self.x2 * m.y1) + (self.x3 * m.z1);
  this->y1 = (self.y1 * m.x1) + (self.y2 * m.y1) + (self.y3 * m.z1);
  this->z1 = (self.z1 * m.x1) + (self.z2 * m.y1) + (self.z3 * m.z1);
  this->x2 = (self.x1 * m.x2) + (self.x2 * m.y2) + (self.x3 * m.z2);
  this->y2 = (self.y1 * m.x2) + (self.y2 * m.y2) + (self.y3 * m.z2);
  this->z2 = (self.z1 * m.x2) + (self.z2 * m.y2) + (self.z3 * m.z2);
  this->x3 = (self.x1 * m.x3) + (self.x2 * m.y3) + (self.x3 * m.z3);
  this->y3 = (self.y1 * m.x3) + (self.y2 * m.y3) + (self.y3 * m.z3);
  this->z3 = (self.z1 * m.x3) + (self.z2 * m.y3) + (self.z3 * m.z3);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T>& Mat<3, 3, T>::operator/=(const Mat<3, 3, U>& other) noexcept {
  return (*this *= ::ran::inverse(other));
}

template<typename T>
RAN_DEF bool operator==(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept {
  return (a.x1 == b.x1) && (a.y1 == b.y1) && (a.z1 == b.z1) && (a.x2 == b.x2) && (a.y2 == b.y2) &&
         (a.z2 == b.z2) && (a.x3 == b.x3) && (a.y3 == b.y3) && (a.z3 == b.z3);
}

template<typename T>
RAN_DEF bool operator!=(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept {
  return (a.x1 != b.x1) || (a.y1 != b.y1) || (a.z1 != b.z1) || (a.x2 != b.x2) || (a.y2 != b.y2) ||
         (a.z2 != b.z2) || (a.x3 != b.x3) || (a.y3 != b.y3) || (a.z3 != b.z3);
}

template<typename T>
RAN_DEF Mat<3, 3, T> operator+(const Mat<3, 3, T>& mat) noexcept {
  Mat<3, 3, T> out;
  out.x1 = +mat.x1;
  out.y1 = +mat.y1;
  out.z1 = +mat.z1;
  out.x2 = +mat.x2;
  out.y2 = +mat.y2;
  out.z2 = +mat.z2;
  out.x3 = +mat.x3;
  out.y3 = +mat.y3;
  out.z3 = +mat.z3;
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> operator+(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept {
  Mat<3, 3, T> out;
  out.x1 = a.x1 + b.x1;
  out.y1 = a.y1 + b.y1;
  out.z1 = a.z1 + b.z1;
  out.x2 = a.x2 + b.x2;
  out.y2 = a.y2 + b.y2;
  out.z2 = a.z2 + b.z2;
  out.x3 = a.x3 + b.x3;
  out.y3 = a.y3 + b.y3;
  out.z3 = a.z3 + b.z3;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator+(const Mat<3, 3, T>& mat, U scalar) noexcept {
  Mat<3, 3, T> out;
  out.x1 = mat.x1 + static_cast<T>(scalar);
  out.y1 = mat.y1 + static_cast<T>(scalar);
  out.z1 = mat.z1 + static_cast<T>(scalar);
  out.x2 = mat.x2 + static_cast<T>(scalar);
  out.y2 = mat.y2 + static_cast<T>(scalar);
  out.z2 = mat.z2 + static_cast<T>(scalar);
  out.x3 = mat.x3 + static_cast<T>(scalar);
  out.y3 = mat.y3 + static_cast<T>(scalar);
  out.z3 = mat.z3 + static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator+(U scalar, const Mat<3, 3, T>& mat) noexcept {
  Mat<3, 3, T> out;
  out.x1 = static_cast<T>(scalar) + mat.x1;
  out.y1 = static_cast<T>(scalar) + mat.y1;
  out.z1 = static_cast<T>(scalar) + mat.z1;
  out.x2 = static_cast<T>(scalar) + mat.x2;
  out.y2 = static_cast<T>(scalar) + mat.y2;
  out.z2 = static_cast<T>(scalar) + mat.z2;
  out.x3 = static_cast<T>(scalar) + mat.x3;
  out.y3 = static_cast<T>(scalar) + mat.y3;
  out.z3 = static_cast<T>(scalar) + mat.z3;
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> operator-(const Mat<3, 3, T>& mat) noexcept {
  Mat<3, 3, T> out;
  out.x1 = -mat.x1;
  out.y1 = -mat.y1;
  out.z1 = -mat.z1;
  out.x2 = -mat.x2;
  out.y2 = -mat.y2;
  out.z2 = -mat.z2;
  out.x3 = -mat.x3;
  out.y3 = -mat.y3;
  out.z3 = -mat.z3;
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> operator-(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept {
  Mat<3, 3, T> out;
  out.x1 = a.x1 - b.x1;
  out.y1 = a.y1 - b.y1;
  out.z1 = a.z1 - b.z1;
  out.x2 = a.x2 - b.x2;
  out.y2 = a.y2 - b.y2;
  out.z2 = a.z2 - b.z2;
  out.x3 = a.x3 - b.x3;
  out.y3 = a.y3 - b.y3;
  out.z3 = a.z3 - b.z3;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator-(const Mat<3, 3, T>& mat, U scalar) noexcept {
  Mat<3, 3, T> out;
  out.x1 = mat.x1 - static_cast<T>(scalar);
  out.y1 = mat.y1 - static_cast<T>(scalar);
  out.z1 = mat.z1 - static_cast<T>(scalar);
  out.x2 = mat.x2 - static_cast<T>(scalar);
  out.y2 = mat.y2 - static_cast<T>(scalar);
  out.z2 = mat.z2 - static_cast<T>(scalar);
  out.x3 = mat.x3 - static_cast<T>(scalar);
  out.y3 = mat.y3 - static_cast<T>(scalar);
  out.z3 = mat.z3 - static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator-(U scalar, const Mat<3, 3, T>& mat) noexcept {
  Mat<3, 3, T> out;
  out.x1 = static_cast<T>(scalar) - mat.x1;
  out.y1 = static_cast<T>(scalar) - mat.y1;
  out.z1 = static_cast<T>(scalar) - mat.z1;
  out.x2 = static_cast<T>(scalar) - mat.x2;
  out.y2 = static_cast<T>(scalar) - mat.y2;
  out.z2 = static_cast<T>(scalar) - mat.z2;
  out.x3 = static_cast<T>(scalar) - mat.x3;
  out.y3 = static_cast<T>(scalar) - mat.y3;
  out.z3 = static_cast<T>(scalar) - mat.z3;
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> operator*(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept {
  Mat<3, 3, T> out;
  out.x1 = (a.x1 * b.x1) + (a.x2 * b.y1) + (a.x3 * b.z1);
  out.y1 = (a.y1 * b.x1) + (a.y2 * b.y1) + (a.y3 * b.z1);
  out.z1 = (a.z1 * b.x1) + (a.z2 * b.y1) + (a.z3 * b.z1);
  out.x2 = (a.x1 * b.x2) + (a.x2 * b.y2) + (a.x3 * b.z2);
  out.y2 = (a.y1 * b.x2) + (a.y2 * b.y2) + (a.y3 * b.z2);
  out.z2 = (a.z1 * b.x2) + (a.z2 * b.y2) + (a.z3 * b.z2);
  out.x3 = (a.x1 * b.x3) + (a.x2 * b.y3) + (a.x3 * b.z3);
  out.y3 = (a.y1 * b.x3) + (a.y2 * b.y3) + (a.y3 * b.z3);
  out.z3 = (a.z1 * b.x3) + (a.z2 * b.y3) + (a.z3 * b.z3);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator*(const Mat<3, 3, T>& mat, U scalar) noexcept {
  Mat<3, 3, T> out;
  out.x1 = mat.x1 * static_cast<T>(scalar);
  out.y1 = mat.y1 * static_cast<T>(scalar);
  out.z1 = mat.z1 * static_cast<T>(scalar);
  out.x2 = mat.x2 * static_cast<T>(scalar);
  out.y2 = mat.y2 * static_cast<T>(scalar);
  out.z2 = mat.z2 * static_cast<T>(scalar);
  out.x3 = mat.x3 * static_cast<T>(scalar);
  out.y3 = mat.y3 * static_cast<T>(scalar);
  out.z3 = mat.z3 * static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator*(U scalar, const Mat<3, 3, T>& mat) noexcept {
  Mat<3, 3, T> out;
  out.x1 = static_cast<T>(scalar) * mat.x1;
  out.y1 = static_cast<T>(scalar) * mat.y1;
  out.z1 = static_cast<T>(scalar) * mat.z1;
  out.x2 = static_cast<T>(scalar) * mat.x2;
  out.y2 = static_cast<T>(scalar) * mat.y2;
  out.z2 = static_cast<T>(scalar) * mat.z2;
  out.x3 = static_cast<T>(scalar) * mat.x3;
  out.y3 = static_cast<T>(scalar) * mat.y3;
  out.z3 = static_cast<T>(scalar) * mat.z3;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<3, 3, T>::col_type operator*(const Mat<3, 3, T>& m,
                                                  const Vec<3, U>& v) noexcept {
  typename Mat<3, 3, T>::col_type out;
  out.x = (m.x1 * v.x) + (m.x2 * v.y) + (m.x3 * v.z);
  out.y = (m.y1 * v.x) + (m.y2 * v.y) + (m.y3 * v.z);
  out.z = (m.z1 * v.x) + (m.z2 * v.y) + (m.z3 * v.z);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<3, 3, T>::row_type operator*(const Vec<3, U>& v,
                                                  const Mat<3, 3, T>& m) noexcept {
  typename Mat<3, 3, T>::row_type out;
  out.x = (v.x * m.x1) + (v.y * m.y1) + (v.z * m.z1);
  out.y = (v.x * m.x2) + (v.y * m.y2) + (v.z * m.z2);
  out.z = (v.x * m.x3) + (v.y * m.y3) + (v.z * m.z3);
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> operator/(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept {
  return a * ::ran::inverse(b);
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator/(const Mat<3, 3, T>& mat, U scalar) noexcept {
  Mat<3, 3, T> out;
  out.x1 = mat.x1 / static_cast<T>(scalar);
  out.y1 = mat.y1 / static_cast<T>(scalar);
  out.z1 = mat.z1 / static_cast<T>(scalar);
  out.x2 = mat.x2 / static_cast<T>(scalar);
  out.y2 = mat.y2 / static_cast<T>(scalar);
  out.z2 = mat.z2 / static_cast<T>(scalar);
  out.x3 = mat.x3 / static_cast<T>(scalar);
  out.y3 = mat.y3 / static_cast<T>(scalar);
  out.z3 = mat.z3 / static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> operator/(U scalar, const Mat<3, 3, T>& mat) noexcept {
  Mat<3, 3, T> out;
  out.x1 = static_cast<T>(scalar) / mat.x1;
  out.y1 = static_cast<T>(scalar) / mat.y1;
  out.z1 = static_cast<T>(scalar) / mat.z1;
  out.x2 = static_cast<T>(scalar) / mat.x2;
  out.y2 = static_cast<T>(scalar) / mat.y2;
  out.z2 = static_cast<T>(scalar) / mat.z2;
  out.x3 = static_cast<T>(scalar) / mat.x3;
  out.y3 = static_cast<T>(scalar) / mat.y3;
  out.z3 = static_cast<T>(scalar) / mat.z3;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<3, 3, T>::col_type operator/(const Mat<3, 3, T>& mat,
                                                  const Vec<3, U>& vec) noexcept {
  return ::ran::inverse(mat) * vec;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<3, 3, T>::row_type operator/(const Vec<3, U>& vec,
                                                  const Mat<3, 3, T>& mat) noexcept {
  return vec * ::ran::inverse(mat);
}

} // namespace ran
