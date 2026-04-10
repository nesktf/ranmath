#ifndef RAN_MATRIX4X4_HPP_
#define RAN_MATRIX4X4_HPP_

#include <ranmath/forward.hpp>

namespace ran {

template<meta::numeric_type T>
struct Mat<4, 4, T> {
public:
  using value_type = T;
  static RAN_CONSTEXPR u32 component_count = 16;

  using row_type = Vec<4, T>;
  using col_type = Vec<4, T>;

  static RAN_CONSTEXPR Mat identity() noexcept { return Mat{T(1)}; }

public:
  RAN_DEFAULT_SPECIAL(Mat);

  RAN_DEF explicit Mat(T scalar) noexcept :
      x1(scalar), y1(), z1(), w1(), x2(), y2(scalar), z2(), w2(), x3(), y3(), z3(scalar), w3(),
      x4(), y4(), z4(), w4(scalar) {}

  template<meta::numeric_convertible<T> U>
  RAN_DEF explicit Mat(U scalar) noexcept :
      x1(static_cast<T>(scalar)), y1(), z1(), w1(), x2(), y2(static_cast<T>(scalar)), z2(), w2(),
      x3(), y3(), z3(static_cast<T>(scalar)), w3(), x4(), y4(), z4(), w4(static_cast<T>(scalar)) {}

  RAN_DEF Mat(T x1_, T y1_, T z1_, T w1_, T x2_, T y2_, T z2_, T w2_, T x3_, T y3_, T z3_, T w3_,
              T x4_, T y4_, T z4_, T w4_) noexcept :
      x1(x1_), y1(y1_), z1(z1_), w1(w1_), x2(x2_), y2(y2_), z2(z2_), w2(w2_), x3(x3_), y3(y3_),
      z3(z3_), w3(w3_), x4(x4_), y4(y4_), z4(z4_), w4(w4_) {}

  template<typename X1, typename Y1, typename Z1, typename W1, typename X2, typename Y2,
           typename Z2, typename W2, typename X3, typename Y3, typename Z3, typename W3,
           typename X4, typename Y4, typename Z4, typename W4>
  RAN_DEF Mat(X1 x1_, Y1 y1_, Z1 z1_, W1 w1_, X2 x2_, Y2 y2_, Z2 z2_, W2 w2_, X3 x3_, Y3 y3_,
              Z3 z3_, W3 w3_, X4 x4_, Y4 y4_, Z4 z4_, W4 w4_) noexcept :
      x1(static_cast<T>(x1_)), y1(static_cast<T>(y1_)), z1(static_cast<T>(z1_)),
      w1(static_cast<T>(w1_)), x2(static_cast<T>(x2_)), y2(static_cast<T>(y2_)),
      z2(static_cast<T>(z2_)), w2(static_cast<T>(w2_)), x3(static_cast<T>(x3_)),
      y3(static_cast<T>(y3_)), z3(static_cast<T>(z3_)), w3(static_cast<T>(w3_)),
      x4(static_cast<T>(x4_)), y4(static_cast<T>(y4_)), z4(static_cast<T>(z4_)),
      w4(static_cast<T>(w4_)) {}

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
        return {x1, y1, z1, w1};
      case 1:
        return {x2, y2, z2, w2};
      case 2:
        return {x3, y3, z3, w3};
      case 3:
        return {x4, y4, z4, w4};
    }
  }

  RAN_DEF row_type row_at(size_t idx) const noexcept {
    switch (idx) {
      default:
        [[fallthrough]];
      case 0:
        return {x1, x2, x3, x4};
      case 1:
        return {y1, y2, y3, y4};
      case 2:
        return {z1, z2, z3, z4};
      case 3:
        return {w1, w2, w3, w4};
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
  RAN_DECL Mat& operator=(const Mat<4, 4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator+=(const Mat<4, 4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator-=(const Mat<4, 4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator*=(const Mat<4, 4, U>& other) noexcept;

  template<meta::numeric_convertible<T> U>
  RAN_DECL Mat& operator/=(const Mat<4, 4, U>& other) noexcept;

public:
  // Column major ordering
  T x1, y1, z1, w1;
  T x2, y2, z2, w2;
  T x3, y3, z3, w3;
  T x4, y4, z4, w4;
};

template<typename T>
RAN_DEF T determinant(const Mat<4, 4, T>& m) noexcept {
  const T t0 = (m.y2 * (m.z3 * m.w4 - m.z4 * m.w3) - m.z2 * (m.y3 * m.w4 - m.y4 * m.w3) +
                m.w2 * (m.y3 * m.z4 - m.y4 * m.z3));
  const T t1 = -(m.y1 * (m.z3 * m.w4 - m.z4 * m.w3) - m.z1 * (m.y3 * m.w4 - m.y4 * m.w3) +
                 m.w1 * (m.y3 * m.z4 - m.y4 * m.z3));
  const T t2 = (m.y1 * (m.z2 * m.w4 - m.z4 * m.w2) - m.z1 * (m.y2 * m.w4 - m.y4 * m.w2) +
                m.w1 * (m.y2 * m.z4 - m.y4 * m.z2));
  const T t3 = -(m.y1 * (m.z2 * m.w3 - m.z3 * m.w2) - m.z1 * (m.y2 * m.w3 - m.y3 * m.w2) +
                 m.w1 * (m.y2 * m.z3 - m.y3 * m.z2));
  return m.x1 * t0 + m.x2 * t1 + m.x3 * t2 + m.x4 * t3;
}

template<typename T>
RAN_DEF Mat<4, 4, T> inverse(const Mat<4, 4, T>& m) noexcept {
  const T c01 = m.y2 * (m.z3 * m.w4 - m.z4 * m.w3) - m.z2 * (m.y3 * m.w4 - m.y4 * m.w3) +
                m.w2 * (m.y3 * m.z4 - m.y4 * m.z3);
  const T c02 = -(m.y1 * (m.z3 * m.w4 - m.z4 * m.w3) - m.z1 * (m.y3 * m.w4 - m.y4 * m.w3) +
                  m.w1 * (m.y3 * m.z4 - m.y4 * m.z3));
  const T c03 = m.y1 * (m.z2 * m.w4 - m.z4 * m.w2) - m.z1 * (m.y2 * m.w4 - m.y4 * m.w2) +
                m.w1 * (m.y2 * m.z4 - m.y4 * m.z2);
  const T c04 = -(m.y1 * (m.z2 * m.w3 - m.z3 * m.w2) - m.z1 * (m.y2 * m.w3 - m.y3 * m.w2) +
                  m.w1 * (m.y2 * m.z3 - m.y3 * m.z2));

  const T invdet = static_cast<T>(1) / (m.x1 * c01 + m.x2 * c02 + m.x3 * c03 + m.x4 * c04);
  Mat<4, 4, T> out;
  out.x1 = c01 * invdet;
  out.y1 = c02 * invdet;
  out.z1 = c03 * invdet;
  out.w1 = c04 * invdet;
  out.x2 = -(m.x2 * (m.z3 * m.w4 - m.z4 * m.w3) - m.z2 * (m.x3 * m.w4 - m.x4 * m.w3) +
             m.w2 * (m.x3 * m.z4 - m.x4 * m.z3)) *
           invdet;
  out.y2 = (m.x1 * (m.z3 * m.w4 - m.z4 * m.w3) - m.z1 * (m.x3 * m.w4 - m.x4 * m.w3) +
            m.w1 * (m.x3 * m.z4 - m.x4 * m.z3)) *
           invdet;
  out.z2 = -(m.x1 * (m.z2 * m.w4 - m.z4 * m.w2) - m.z1 * (m.x2 * m.w4 - m.x4 * m.w2) +
             m.w1 * (m.x2 * m.z4 - m.x4 * m.z2)) *
           invdet;
  out.w2 = (m.x1 * (m.z2 * m.w3 - m.z3 * m.w2) - m.z1 * (m.x2 * m.w3 - m.x3 * m.w2) +
            m.w1 * (m.x2 * m.z3 - m.x3 * m.z2)) *
           invdet;
  out.x3 = (m.x2 * (m.y3 * m.w4 - m.y4 * m.w3) - m.y2 * (m.x3 * m.w4 - m.x4 * m.w3) +
            m.w2 * (m.x3 * m.y4 - m.x4 * m.y3)) *
           invdet;
  out.y3 = -(m.x1 * (m.y3 * m.w4 - m.y4 * m.w3) - m.y1 * (m.x3 * m.w4 - m.x4 * m.w3) +
             m.w1 * (m.x3 * m.y4 - m.x4 * m.y3)) *
           invdet;
  out.z3 = (m.x1 * (m.y2 * m.w4 - m.y4 * m.w2) - m.y1 * (m.x2 * m.w4 - m.x4 * m.w2) +
            m.w1 * (m.x2 * m.y4 - m.x4 * m.y2)) *
           invdet;
  out.w3 = -(m.x1 * (m.y2 * m.w3 - m.y3 * m.w2) - m.y1 * (m.x2 * m.w3 - m.x3 * m.y2) +
             m.w1 * (m.x2 * m.y3 - m.x3 * m.y2)) *
           invdet;
  out.x4 = -(m.x2 * (m.y3 * m.z4 - m.y4 * m.z3) - m.y2 * (m.x3 * m.z4 - m.x4 * m.z3) +
             m.z2 * (m.x3 * m.y4 - m.x4 * m.y3)) *
           invdet;
  out.y4 = (m.x1 * (m.y3 * m.z4 - m.y4 * m.z3) - m.y1 * (m.x3 * m.z4 - m.x4 * m.z3) +
            m.z1 * (m.x3 * m.y4 - m.x4 * m.y3)) *
           invdet;
  out.z4 = -(m.x1 * (m.y2 * m.z4 - m.y4 * m.z2) - m.y1 * (m.x2 * m.z4 - m.x4 * m.z2) +
             m.z1 * (m.x2 * m.y4 - m.x4 * m.y2)) *
           invdet;
  out.w4 = (m.x1 * (m.y2 * m.z3 - m.y3 * m.z2) - m.y1 * (m.x2 * m.z3 - m.x3 * m.z2) +
            m.z1 * (m.x2 * m.y3 - m.x3 * m.y2)) *
           invdet;
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> transpose(const Mat<4, 4, T>& m) noexcept {
  Mat<4, 4, T> out;
  out.x1 = m.x1;
  out.y1 = m.x2;
  out.z1 = m.x3;
  out.w1 = m.x4;
  out.x2 = m.y1;
  out.y2 = m.y2;
  out.z2 = m.y3;
  out.w2 = m.y4;
  out.x3 = m.z1;
  out.y3 = m.z2;
  out.z3 = m.z3;
  out.w3 = m.z4;
  out.x4 = m.w1;
  out.y4 = m.w2;
  out.z4 = m.w3;
  out.w4 = m.w4;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> translate(const Mat<4, 4, T>& m, const Vec<3, U>& v) noexcept {
  Mat<4, 4, T> out = m;
  out.x4 = (m.x1 * static_cast<T>(v.x)) + (m.x2 * static_cast<T>(v.y)) +
           (m.x3 * static_cast<T>(v.z)) + m.x4;
  out.y4 = (m.y1 * static_cast<T>(v.x)) + (m.y2 * static_cast<T>(v.y)) +
           (m.y3 * static_cast<T>(v.z)) + m.y4;
  out.z4 = (m.z1 * static_cast<T>(v.x)) + (m.z2 * static_cast<T>(v.y)) +
           (m.z3 * static_cast<T>(v.z)) + m.z4;
  out.w4 = (m.w1 * static_cast<T>(v.x)) + (m.w2 * static_cast<T>(v.y)) +
           (m.w3 * static_cast<T>(v.z)) + m.w4;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> scale(const Mat<4, 4, T>& m, const Vec<3, U>& v) noexcept {
  Mat<4, 4, T> out(T(1));
  out.x1 = m.x1 * static_cast<T>(v.x);
  out.y1 = m.y1 * static_cast<T>(v.x);
  out.z1 = m.z1 * static_cast<T>(v.x);
  out.x2 = m.x2 * static_cast<T>(v.y);
  out.y2 = m.y2 * static_cast<T>(v.y);
  out.z2 = m.z2 * static_cast<T>(v.y);
  out.x3 = m.x3 * static_cast<T>(v.z);
  out.y3 = m.y3 * static_cast<T>(v.z);
  out.z3 = m.z3 * static_cast<T>(v.z);
  out.x4 = m.x4;
  out.y4 = m.y4;
  out.z4 = m.z4;
  return out;
}

template<typename T, meta::numeric_convertible<T> U, meta::numeric_convertible<T> V>
RAN_DEF Mat<4, 4, T> rotate(const Mat<4, 4, T>& m, U angle, const Vec<3, V>& axis) noexcept {
  const T c = static_cast<T>(::ran::cos(angle));
  const T s = static_cast<T>(::ran::sin(angle));

  const auto ax = ::ran::vec_cast<T>(::ran::normalize(axis));
  const auto inv_c = (ax * (T(1) - c));

  Mat<3, 3, T> rot;
  rot.x1 = c + (inv_c.x * ax.x);
  rot.y1 = (inv_c.x * ax.y) + (s * ax.z);
  rot.z1 = (inv_c.x * ax.z) - (s * ax.y);
  rot.x2 = (inv_c.y * ax.x) - (s * ax.z);
  rot.y2 = c + (inv_c.y * ax.y);
  rot.z2 = (inv_c.y * ax.z) + (s * ax.x);
  rot.x3 = (inv_c.z * ax.x) + (s * ax.y);
  rot.y3 = (inv_c.z * ax.y) - (s * ax.x);
  rot.z3 = c + (inv_c.z * ax.z);

  Mat<4, 4, T> out;
  out.x1 = (m.x1 * rot.x1) + (m.x2 * rot.y1) + (m.x3 * rot.z1);
  out.y1 = (m.y1 * rot.x1) + (m.y2 * rot.y1) + (m.y3 * rot.z1);
  out.z1 = (m.z1 * rot.x1) + (m.z2 * rot.y1) + (m.z3 * rot.z1);
  out.x2 = (m.x1 * rot.x2) + (m.x2 * rot.y2) + (m.x3 * rot.z2);
  out.y2 = (m.y1 * rot.x2) + (m.y2 * rot.y2) + (m.y3 * rot.z2);
  out.z2 = (m.z1 * rot.x2) + (m.z2 * rot.y2) + (m.z3 * rot.z2);
  out.x3 = (m.x1 * rot.x3) + (m.x2 * rot.y3) + (m.x3 * rot.z3);
  out.y3 = (m.y1 * rot.x3) + (m.y2 * rot.y3) + (m.y3 * rot.z3);
  out.z3 = (m.z1 * rot.x3) + (m.z2 * rot.y3) + (m.z3 * rot.z3);
  out.x4 = m.x4;
  out.y4 = m.y4;
  out.z4 = m.z4;
  out.w4 = m.w4;
  return out;
}

template<typename T>
RAN_DEF Mat<3, 3, T> to_mat3(const Mat<4, 4, T>& m) noexcept {
  Mat<3, 3, T> out;
  out.x1 = m.x1;
  out.y1 = m.y1;
  out.z1 = m.z1;
  out.x2 = m.x2;
  out.y2 = m.y2;
  out.z2 = m.z2;
  out.x3 = m.x3;
  out.y3 = m.y3;
  out.z3 = m.z3;
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> to_mat4(const Mat<3, 3, T>& m) noexcept {
  Mat<4, 4, T> out;
  out.x1 = m.x1;
  out.y1 = m.y1;
  out.z1 = m.z1;
  out.w1 = T(0);
  out.x2 = m.x2;
  out.y2 = m.y2;
  out.z2 = m.z2;
  out.w2 = T(0);
  out.x3 = m.x3;
  out.y3 = m.y3;
  out.z3 = m.z3;
  out.w3 = T(0);
  out.x4 = T(0);
  out.y4 = T(0);
  out.z4 = T(0);
  out.w4 = T(1);
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> lookat_rh(const Vec<3, T>& pos, const Vec<3, T>& center,
                               const Vec<3, T>& up) noexcept {
  const Vec<3, T> row3 = ::ran::normalize(center - pos);
  const Vec<3, T> row1 = ::ran::normalize(::ran::cross(row3, up));
  const Vec<3, T> row2 = ::ran::cross(row1, row3);

  Mat<4, 4, T> out;
  out.x1 = row1.x;
  out.x2 = row1.y;
  out.x3 = row1.z;
  out.x4 = -::ran::dot(row1, pos);
  out.y1 = row2.x;
  out.y2 = row2.y;
  out.y3 = row2.z;
  out.y4 = -::ran::dot(row2, pos);
  out.z1 = -row3.x;
  out.z2 = -row3.y;
  out.z3 = -row3.z;
  out.z4 = ::ran::dot(row3, pos);
  out.w1 = T(0);
  out.w2 = T(0);
  out.w3 = T(0);
  out.w4 = T(1);
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> lookat_lh(const Vec<3, T>& pos, const Vec<3, T>& center,
                               const Vec<3, T>& up) noexcept {
  const Vec<3, T> row3 = ::ran::normalize(center - pos);
  const Vec<3, T> row1 = ::ran::normalize(::ran::cross(row3, up));
  const Vec<3, T> row2 = ::ran::cross(row1, row3);

  Mat<4, 4, T> out;
  out.x1 = row1.x;
  out.x2 = row1.y;
  out.x3 = row1.z;
  out.x4 = -::ran::dot(row1, pos);
  out.y1 = row2.x;
  out.y2 = row2.y;
  out.y3 = row2.z;
  out.y4 = -::ran::dot(row2, pos);
  out.z1 = row3.x;
  out.z2 = row3.y;
  out.z3 = row3.z;
  out.z4 = -::ran::dot(row3, pos);
  out.w1 = T(0);
  out.w2 = T(0);
  out.w3 = T(0);
  out.w4 = T(1);
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> ortho(T left, T right, T bottom, T top) noexcept {
  Mat<4, 4, T> out(T(1));
  out.x1 = T(2) / (right - left);
  out.y2 = T(2) / (top - bottom);
  out.z3 = -T(1);
  out.x4 = -(right + left) / (right - left);
  out.y4 = -(top + bottom) / (top - bottom);
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> ortho(T left, T right, T bottom, T top, T znear, T zfar) noexcept {
  Mat<4, 4, T> out(T(1));
  out.x1 = T(2) / (right - left);
  out.y2 = T(2) / (top - bottom);
  out.z3 = T(2) / (zfar - znear);
  out.x4 = -(right + left) / (right - left);
  out.y4 = -(top + bottom) / (top - bottom);
  out.z4 = -(zfar + znear) / (zfar - znear);
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> perspective(T fov, T aspect, T znear, T zfar) noexcept {
  if constexpr (std::floating_point<T>) {
    if (::ran::fequal(fov, T(0))) {
      fov = T(0.0001);
    }
  } else {
    if (fov == T(0)) {
      fov = 1;
    }
  }
  const T halftan = ::ran::tan(fov / T(2));

  Mat<4, 4, T> out(T(0));
  out.x1 = T(1) / (aspect * halftan);
  out.y2 = T(1) / halftan;
  out.z3 = -(zfar + znear) / (zfar - znear);
  out.w3 = -T(1);
  out.z4 = -(zfar * znear) / (zfar - znear);
  return out;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator=(U scalar) noexcept {
  this->x1 = static_cast<T>(scalar);
  this->y1 = static_cast<T>(scalar);
  this->z1 = static_cast<T>(scalar);
  this->w1 = static_cast<T>(scalar);
  this->x2 = static_cast<T>(scalar);
  this->y2 = static_cast<T>(scalar);
  this->z2 = static_cast<T>(scalar);
  this->w2 = static_cast<T>(scalar);
  this->x3 = static_cast<T>(scalar);
  this->y3 = static_cast<T>(scalar);
  this->z3 = static_cast<T>(scalar);
  this->w3 = static_cast<T>(scalar);
  this->x4 = static_cast<T>(scalar);
  this->y4 = static_cast<T>(scalar);
  this->z4 = static_cast<T>(scalar);
  this->w4 = static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator+=(U scalar) noexcept {
  this->x1 += static_cast<T>(scalar);
  this->y1 += static_cast<T>(scalar);
  this->z1 += static_cast<T>(scalar);
  this->w1 += static_cast<T>(scalar);
  this->x2 += static_cast<T>(scalar);
  this->y2 += static_cast<T>(scalar);
  this->z2 += static_cast<T>(scalar);
  this->w2 += static_cast<T>(scalar);
  this->x3 += static_cast<T>(scalar);
  this->y3 += static_cast<T>(scalar);
  this->z3 += static_cast<T>(scalar);
  this->w3 += static_cast<T>(scalar);
  this->x4 += static_cast<T>(scalar);
  this->y4 += static_cast<T>(scalar);
  this->z4 += static_cast<T>(scalar);
  this->w4 += static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator-=(U scalar) noexcept {
  this->x1 -= static_cast<T>(scalar);
  this->y1 -= static_cast<T>(scalar);
  this->z1 -= static_cast<T>(scalar);
  this->w1 -= static_cast<T>(scalar);
  this->x2 -= static_cast<T>(scalar);
  this->y2 -= static_cast<T>(scalar);
  this->z2 -= static_cast<T>(scalar);
  this->w2 -= static_cast<T>(scalar);
  this->x3 -= static_cast<T>(scalar);
  this->y3 -= static_cast<T>(scalar);
  this->z3 -= static_cast<T>(scalar);
  this->w3 -= static_cast<T>(scalar);
  this->x4 -= static_cast<T>(scalar);
  this->y4 -= static_cast<T>(scalar);
  this->z4 -= static_cast<T>(scalar);
  this->w4 -= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator*=(U scalar) noexcept {
  this->x1 *= static_cast<T>(scalar);
  this->y1 *= static_cast<T>(scalar);
  this->z1 *= static_cast<T>(scalar);
  this->w1 *= static_cast<T>(scalar);
  this->x2 *= static_cast<T>(scalar);
  this->y2 *= static_cast<T>(scalar);
  this->z2 *= static_cast<T>(scalar);
  this->w2 *= static_cast<T>(scalar);
  this->x3 *= static_cast<T>(scalar);
  this->y3 *= static_cast<T>(scalar);
  this->z3 *= static_cast<T>(scalar);
  this->w3 *= static_cast<T>(scalar);
  this->x4 *= static_cast<T>(scalar);
  this->y4 *= static_cast<T>(scalar);
  this->z4 *= static_cast<T>(scalar);
  this->w4 *= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator/=(U scalar) noexcept {
  this->x1 /= static_cast<T>(scalar);
  this->y1 /= static_cast<T>(scalar);
  this->z1 /= static_cast<T>(scalar);
  this->w1 /= static_cast<T>(scalar);
  this->x2 /= static_cast<T>(scalar);
  this->y2 /= static_cast<T>(scalar);
  this->z2 /= static_cast<T>(scalar);
  this->w2 /= static_cast<T>(scalar);
  this->x3 /= static_cast<T>(scalar);
  this->y3 /= static_cast<T>(scalar);
  this->z3 /= static_cast<T>(scalar);
  this->w3 /= static_cast<T>(scalar);
  this->x4 /= static_cast<T>(scalar);
  this->y4 /= static_cast<T>(scalar);
  this->z4 /= static_cast<T>(scalar);
  this->w4 /= static_cast<T>(scalar);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator=(const Mat<4, 4, U>& other) noexcept {
  this->x1 = static_cast<T>(other.x1);
  this->y1 = static_cast<T>(other.y1);
  this->z1 = static_cast<T>(other.z1);
  this->w1 = static_cast<T>(other.w1);
  this->x2 = static_cast<T>(other.x2);
  this->y2 = static_cast<T>(other.y2);
  this->z2 = static_cast<T>(other.z2);
  this->w2 = static_cast<T>(other.w2);
  this->x3 = static_cast<T>(other.x3);
  this->y3 = static_cast<T>(other.y3);
  this->z3 = static_cast<T>(other.z3);
  this->w3 = static_cast<T>(other.w3);
  this->x4 = static_cast<T>(other.x4);
  this->y4 = static_cast<T>(other.y4);
  this->z4 = static_cast<T>(other.z4);
  this->w4 = static_cast<T>(other.w4);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator+=(const Mat<4, 4, U>& other) noexcept {
  this->x1 += static_cast<T>(other.x1);
  this->y1 += static_cast<T>(other.y1);
  this->z1 += static_cast<T>(other.z1);
  this->w1 += static_cast<T>(other.w1);
  this->x2 += static_cast<T>(other.x2);
  this->y2 += static_cast<T>(other.y2);
  this->z2 += static_cast<T>(other.z2);
  this->w2 += static_cast<T>(other.w2);
  this->x3 += static_cast<T>(other.x3);
  this->y3 += static_cast<T>(other.y3);
  this->z3 += static_cast<T>(other.z3);
  this->w3 += static_cast<T>(other.w3);
  this->x4 += static_cast<T>(other.x4);
  this->y4 += static_cast<T>(other.y4);
  this->z4 += static_cast<T>(other.z4);
  this->w4 += static_cast<T>(other.w4);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator-=(const Mat<4, 4, U>& other) noexcept {
  this->x1 -= static_cast<T>(other.x1);
  this->y1 -= static_cast<T>(other.y1);
  this->z1 -= static_cast<T>(other.z1);
  this->w1 -= static_cast<T>(other.w1);
  this->x2 -= static_cast<T>(other.x2);
  this->y2 -= static_cast<T>(other.y2);
  this->z2 -= static_cast<T>(other.z2);
  this->w2 -= static_cast<T>(other.w2);
  this->x3 -= static_cast<T>(other.x3);
  this->y3 -= static_cast<T>(other.y3);
  this->z3 -= static_cast<T>(other.z3);
  this->w3 -= static_cast<T>(other.w3);
  this->x4 -= static_cast<T>(other.x4);
  this->y4 -= static_cast<T>(other.y4);
  this->z4 -= static_cast<T>(other.z4);
  this->w4 -= static_cast<T>(other.w4);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator*=(const Mat<4, 4, U>& m) noexcept {
  const Mat<4, 4, T> self = *this;
  this->x1 = (self.x1 * m.x1) + (self.x2 * m.y1) + (self.x3 * m.z1) + (self.x4 * m.w1);
  this->y1 = (self.y1 * m.x1) + (self.y2 * m.y1) + (self.y3 * m.z1) + (self.y4 * m.w1);
  this->z1 = (self.z1 * m.x1) + (self.z2 * m.y1) + (self.z3 * m.z1) + (self.z4 * m.w1);
  this->w1 = (self.w1 * m.x1) + (self.w2 * m.y1) + (self.w3 * m.z1) + (self.w4 * m.w1);
  this->x2 = (self.x1 * m.x2) + (self.x2 * m.y2) + (self.x3 * m.z2) + (self.x4 * m.w2);
  this->y2 = (self.y1 * m.x2) + (self.y2 * m.y2) + (self.y3 * m.z2) + (self.y4 * m.w2);
  this->z2 = (self.z1 * m.x2) + (self.z2 * m.y2) + (self.z3 * m.z2) + (self.z4 * m.w2);
  this->w2 = (self.w1 * m.x2) + (self.w2 * m.y2) + (self.w3 * m.z2) + (self.w4 * m.w2);
  this->x3 = (self.x1 * m.x3) + (self.x2 * m.y3) + (self.x3 * m.z3) + (self.x4 * m.w3);
  this->y3 = (self.y1 * m.x3) + (self.y2 * m.y3) + (self.y3 * m.z3) + (self.y4 * m.w3);
  this->z3 = (self.z1 * m.x3) + (self.z2 * m.y3) + (self.z3 * m.z3) + (self.z4 * m.w3);
  this->w3 = (self.w1 * m.x3) + (self.w2 * m.y3) + (self.w3 * m.z3) + (self.w4 * m.w3);
  this->x4 = (self.x1 * m.x4) + (self.x2 * m.y4) + (self.x3 * m.z4) + (self.x4 * m.w4);
  this->y4 = (self.y1 * m.x4) + (self.y2 * m.y4) + (self.y3 * m.z4) + (self.y4 * m.w4);
  this->z4 = (self.z1 * m.x4) + (self.z2 * m.y4) + (self.z3 * m.z4) + (self.z4 * m.w4);
  this->w4 = (self.w1 * m.x4) + (self.w2 * m.y4) + (self.w3 * m.z4) + (self.w4 * m.w4);
  return *this;
}

template<meta::numeric_type T>
template<meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T>& Mat<4, 4, T>::operator/=(const Mat<4, 4, U>& other) noexcept {
  return (*this *= ::ran::inverse(other));
}

template<typename T>
RAN_DEF bool operator==(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept {
  return (a.x1 == b.x1) && (a.y1 == b.y1) && (a.z1 == b.z1) && (a.w1 == b.w1) && (a.x2 == b.x2) &&
         (a.y2 == b.y2) && (a.z2 == b.z2) && (a.w2 == b.w2) && (a.x3 == b.x3) && (a.y3 == b.y3) &&
         (a.z3 == b.z3) && (a.w3 == b.w3) && (a.x4 == b.x4) && (a.y4 == b.y4) && (a.z4 == b.z4) &&
         (a.w4 == b.w4);
}

template<typename T>
RAN_DEF bool operator!=(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept {
  return (a.x1 != b.x1) || (a.y1 != b.y1) || (a.z1 != b.z1) || (a.w1 != b.w1) || (a.x2 != b.x2) ||
         (a.y2 != b.y2) || (a.z2 != b.z2) || (a.w2 != b.w2) || (a.x3 != b.x3) || (a.y3 != b.y3) ||
         (a.z3 != b.z3) || (a.w3 != b.w3) || (a.x4 != b.x4) || (a.y4 != b.y4) || (a.z4 != b.z4) ||
         (a.w4 != b.w4);
}

template<typename T>
RAN_DEF Mat<4, 4, T> operator+(const Mat<4, 4, T>& mat) noexcept {
  Mat<4, 4, T> out;
  out.x1 = +mat.x1;
  out.y1 = +mat.y1;
  out.z1 = +mat.z1;
  out.w1 = +mat.w1;
  out.x2 = +mat.x2;
  out.y2 = +mat.y2;
  out.z2 = +mat.z2;
  out.w2 = +mat.w2;
  out.x3 = +mat.x3;
  out.y3 = +mat.y3;
  out.z3 = +mat.z3;
  out.w3 = +mat.w3;
  out.x4 = +mat.x4;
  out.y4 = +mat.y4;
  out.z4 = +mat.z4;
  out.w4 = +mat.w4;
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> operator+(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept {
  Mat<4, 4, T> out;
  out.x1 = a.x1 + b.x1;
  out.y1 = a.y1 + b.y1;
  out.z1 = a.z1 + b.z1;
  out.w1 = a.w1 + b.w1;
  out.x2 = a.x2 + b.x2;
  out.y2 = a.y2 + b.y2;
  out.z2 = a.z2 + b.z2;
  out.w2 = a.w2 + b.w2;
  out.x3 = a.x3 + b.x3;
  out.y3 = a.y3 + b.y3;
  out.z3 = a.z3 + b.z3;
  out.w3 = a.w3 + b.w3;
  out.x4 = a.x4 + b.x4;
  out.y4 = a.y4 + b.y4;
  out.z4 = a.z4 + b.z4;
  out.w4 = a.w4 + b.w4;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator+(const Mat<4, 4, T>& mat, U scalar) noexcept {
  Mat<4, 4, T> out;
  out.x1 = mat.x1 + static_cast<T>(scalar);
  out.y1 = mat.y1 + static_cast<T>(scalar);
  out.z1 = mat.z1 + static_cast<T>(scalar);
  out.w1 = mat.w1 + static_cast<T>(scalar);
  out.x2 = mat.x2 + static_cast<T>(scalar);
  out.y2 = mat.y2 + static_cast<T>(scalar);
  out.z2 = mat.z2 + static_cast<T>(scalar);
  out.w2 = mat.w2 + static_cast<T>(scalar);
  out.x3 = mat.x3 + static_cast<T>(scalar);
  out.y3 = mat.y3 + static_cast<T>(scalar);
  out.z3 = mat.z3 + static_cast<T>(scalar);
  out.w3 = mat.w3 + static_cast<T>(scalar);
  out.x4 = mat.x4 + static_cast<T>(scalar);
  out.y4 = mat.y4 + static_cast<T>(scalar);
  out.z4 = mat.z4 + static_cast<T>(scalar);
  out.w4 = mat.w4 + static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator+(U scalar, const Mat<4, 4, T>& mat) noexcept {
  Mat<4, 4, T> out;
  out.x1 = static_cast<T>(scalar) + mat.x1;
  out.y1 = static_cast<T>(scalar) + mat.y1;
  out.z1 = static_cast<T>(scalar) + mat.z1;
  out.w1 = static_cast<T>(scalar) + mat.w1;
  out.x2 = static_cast<T>(scalar) + mat.x2;
  out.y2 = static_cast<T>(scalar) + mat.y2;
  out.z2 = static_cast<T>(scalar) + mat.z2;
  out.w2 = static_cast<T>(scalar) + mat.w2;
  out.x3 = static_cast<T>(scalar) + mat.x3;
  out.y3 = static_cast<T>(scalar) + mat.y3;
  out.z3 = static_cast<T>(scalar) + mat.z3;
  out.w3 = static_cast<T>(scalar) + mat.w3;
  out.x4 = static_cast<T>(scalar) + mat.x4;
  out.y4 = static_cast<T>(scalar) + mat.y4;
  out.z4 = static_cast<T>(scalar) + mat.z4;
  out.w4 = static_cast<T>(scalar) + mat.w4;
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> operator-(const Mat<4, 4, T>& mat) noexcept {
  Mat<4, 4, T> out;
  out.x1 = -mat.x1;
  out.y1 = -mat.y1;
  out.z1 = -mat.z1;
  out.w1 = -mat.w1;
  out.x2 = -mat.x2;
  out.y2 = -mat.y2;
  out.z2 = -mat.z2;
  out.w2 = -mat.w2;
  out.x3 = -mat.x3;
  out.y3 = -mat.y3;
  out.z3 = -mat.z3;
  out.w3 = -mat.w3;
  out.x4 = -mat.x4;
  out.y4 = -mat.y4;
  out.z4 = -mat.z4;
  out.w4 = -mat.w4;
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> operator-(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept {
  Mat<4, 4, T> out;
  out.x1 = a.x1 - b.x1;
  out.y1 = a.y1 - b.y1;
  out.z1 = a.z1 - b.z1;
  out.w1 = a.w1 - b.w1;
  out.x2 = a.x2 - b.x2;
  out.y2 = a.y2 - b.y2;
  out.z2 = a.z2 - b.z2;
  out.w2 = a.w2 - b.w2;
  out.x3 = a.x3 - b.x3;
  out.y3 = a.y3 - b.y3;
  out.z3 = a.z3 - b.z3;
  out.w3 = a.w3 - b.w3;
  out.x4 = a.x4 - b.x4;
  out.y4 = a.y4 - b.y4;
  out.z4 = a.z4 - b.z4;
  out.w4 = a.w4 - b.w4;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator-(const Mat<4, 4, T>& mat, U scalar) noexcept {
  Mat<4, 4, T> out;
  out.x1 = mat.x1 - static_cast<T>(scalar);
  out.y1 = mat.y1 - static_cast<T>(scalar);
  out.z1 = mat.z1 - static_cast<T>(scalar);
  out.w1 = mat.w1 - static_cast<T>(scalar);
  out.x2 = mat.x2 - static_cast<T>(scalar);
  out.y2 = mat.y2 - static_cast<T>(scalar);
  out.z2 = mat.z2 - static_cast<T>(scalar);
  out.w2 = mat.w2 - static_cast<T>(scalar);
  out.x3 = mat.x3 - static_cast<T>(scalar);
  out.y3 = mat.y3 - static_cast<T>(scalar);
  out.z3 = mat.z3 - static_cast<T>(scalar);
  out.w3 = mat.w3 - static_cast<T>(scalar);
  out.x4 = mat.x4 - static_cast<T>(scalar);
  out.y4 = mat.y4 - static_cast<T>(scalar);
  out.z4 = mat.z4 - static_cast<T>(scalar);
  out.w4 = mat.w4 - static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator-(U scalar, const Mat<4, 4, T>& mat) noexcept {
  Mat<4, 4, T> out;
  out.x1 = static_cast<T>(scalar) - mat.x1;
  out.y1 = static_cast<T>(scalar) - mat.y1;
  out.z1 = static_cast<T>(scalar) - mat.z1;
  out.w1 = static_cast<T>(scalar) - mat.w1;
  out.x2 = static_cast<T>(scalar) - mat.x2;
  out.y2 = static_cast<T>(scalar) - mat.y2;
  out.z2 = static_cast<T>(scalar) - mat.z2;
  out.w2 = static_cast<T>(scalar) - mat.w2;
  out.x3 = static_cast<T>(scalar) - mat.x3;
  out.y3 = static_cast<T>(scalar) - mat.y3;
  out.z3 = static_cast<T>(scalar) - mat.z3;
  out.w3 = static_cast<T>(scalar) - mat.w3;
  out.x4 = static_cast<T>(scalar) - mat.x4;
  out.y4 = static_cast<T>(scalar) - mat.y4;
  out.z4 = static_cast<T>(scalar) - mat.z4;
  out.w4 = static_cast<T>(scalar) - mat.w4;
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> operator*(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept {
  Mat<4, 4, T> out;
  out.x1 = (a.x1 * b.x1) + (a.x2 * b.y1) + (a.x3 * b.z1) + (a.x4 * b.w1);
  out.y1 = (a.y1 * b.x1) + (a.y2 * b.y1) + (a.y3 * b.z1) + (a.y4 * b.w1);
  out.z1 = (a.z1 * b.x1) + (a.z2 * b.y1) + (a.z3 * b.z1) + (a.z4 * b.w1);
  out.w1 = (a.w1 * b.x1) + (a.w2 * b.y1) + (a.w3 * b.z1) + (a.w4 * b.w1);
  out.x2 = (a.x1 * b.x2) + (a.x2 * b.y2) + (a.x3 * b.z2) + (a.x4 * b.w2);
  out.y2 = (a.y1 * b.x2) + (a.y2 * b.y2) + (a.y3 * b.z2) + (a.y4 * b.w2);
  out.z2 = (a.z1 * b.x2) + (a.z2 * b.y2) + (a.z3 * b.z2) + (a.z4 * b.w2);
  out.w2 = (a.w1 * b.x2) + (a.w2 * b.y2) + (a.w3 * b.z2) + (a.w4 * b.w2);
  out.x3 = (a.x1 * b.x3) + (a.x2 * b.y3) + (a.x3 * b.z3) + (a.x4 * b.w3);
  out.y3 = (a.y1 * b.x3) + (a.y2 * b.y3) + (a.y3 * b.z3) + (a.y4 * b.w3);
  out.z3 = (a.z1 * b.x3) + (a.z2 * b.y3) + (a.z3 * b.z3) + (a.z4 * b.w3);
  out.w3 = (a.w1 * b.x3) + (a.w2 * b.y3) + (a.w3 * b.z3) + (a.w4 * b.w3);
  out.x4 = (a.x1 * b.x4) + (a.x2 * b.y4) + (a.x3 * b.z4) + (a.x4 * b.w4);
  out.y4 = (a.y1 * b.x4) + (a.y2 * b.y4) + (a.y3 * b.z4) + (a.y4 * b.w4);
  out.z4 = (a.z1 * b.x4) + (a.z2 * b.y4) + (a.z3 * b.z4) + (a.z4 * b.w4);
  out.w4 = (a.w1 * b.x4) + (a.w2 * b.y4) + (a.w3 * b.z4) + (a.w4 * b.w4);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator*(const Mat<4, 4, T>& mat, U scalar) noexcept {
  Mat<4, 4, T> out;
  out.x1 = mat.x1 * static_cast<T>(scalar);
  out.y1 = mat.y1 * static_cast<T>(scalar);
  out.z1 = mat.z1 * static_cast<T>(scalar);
  out.w1 = mat.w1 * static_cast<T>(scalar);
  out.x2 = mat.x2 * static_cast<T>(scalar);
  out.y2 = mat.y2 * static_cast<T>(scalar);
  out.z2 = mat.z2 * static_cast<T>(scalar);
  out.w2 = mat.w2 * static_cast<T>(scalar);
  out.x3 = mat.x3 * static_cast<T>(scalar);
  out.y3 = mat.y3 * static_cast<T>(scalar);
  out.z3 = mat.z3 * static_cast<T>(scalar);
  out.w3 = mat.w3 * static_cast<T>(scalar);
  out.x4 = mat.x4 * static_cast<T>(scalar);
  out.y4 = mat.y4 * static_cast<T>(scalar);
  out.z4 = mat.z4 * static_cast<T>(scalar);
  out.w4 = mat.w4 * static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator*(U scalar, const Mat<4, 4, T>& mat) noexcept {
  Mat<4, 4, T> out;
  out.x1 = static_cast<T>(scalar) * mat.x1;
  out.y1 = static_cast<T>(scalar) * mat.y1;
  out.z1 = static_cast<T>(scalar) * mat.z1;
  out.w1 = static_cast<T>(scalar) * mat.w1;
  out.x2 = static_cast<T>(scalar) * mat.x2;
  out.y2 = static_cast<T>(scalar) * mat.y2;
  out.z2 = static_cast<T>(scalar) * mat.z2;
  out.w2 = static_cast<T>(scalar) * mat.w2;
  out.x3 = static_cast<T>(scalar) * mat.x3;
  out.y3 = static_cast<T>(scalar) * mat.y3;
  out.z3 = static_cast<T>(scalar) * mat.z3;
  out.w3 = static_cast<T>(scalar) * mat.w3;
  out.x4 = static_cast<T>(scalar) * mat.x4;
  out.y4 = static_cast<T>(scalar) * mat.y4;
  out.z4 = static_cast<T>(scalar) * mat.z4;
  out.w4 = static_cast<T>(scalar) * mat.w4;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<4, 4, T>::col_type operator*(const Mat<4, 4, T>& m,
                                                  const Vec<4, U>& v) noexcept {
  typename Mat<4, 4, T>::col_type out;
  out.x = m.x1 * v.x + m.x2 * v.y + m.x3 * v.z + m.x4 * v.w;
  out.y = m.y1 * v.x + m.y2 * v.y + m.y3 * v.z + m.y4 * v.w;
  out.z = m.z1 * v.x + m.z2 * v.y + m.z3 * v.z + m.z4 * v.w;
  out.w = m.w1 * v.x + m.w2 * v.y + m.w3 * v.z + m.w4 * v.w;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<4, 4, T>::row_type operator*(const Vec<4, U>& v,
                                                  const Mat<4, 4, T>& m) noexcept {
  typename Mat<4, 4, T>::row_type out;
  out.x = v.x * m.x1 + v.y * m.y1 + v.z * m.z1 + v.w * m.w1;
  out.y = v.x * m.x2 + v.y * m.y2 + v.z * m.z2 + v.w * m.w2;
  out.z = v.x * m.x3 + v.y * m.y3 + v.z * m.z3 + v.w * m.w3;
  out.w = v.x * m.x4 + v.y * m.y4 + v.z * m.z4 + v.w * m.w4;
  return out;
}

template<typename T>
RAN_DEF Mat<4, 4, T> operator/(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept {
  return a * ::ran::inverse(b);
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator/(const Mat<4, 4, T>& mat, U scalar) noexcept {
  Mat<4, 4, T> out;
  out.x1 = mat.x1 / static_cast<T>(scalar);
  out.y1 = mat.y1 / static_cast<T>(scalar);
  out.z1 = mat.z1 / static_cast<T>(scalar);
  out.w1 = mat.w1 / static_cast<T>(scalar);
  out.x2 = mat.x2 / static_cast<T>(scalar);
  out.y2 = mat.y2 / static_cast<T>(scalar);
  out.z2 = mat.z2 / static_cast<T>(scalar);
  out.w2 = mat.w2 / static_cast<T>(scalar);
  out.x3 = mat.x3 / static_cast<T>(scalar);
  out.y3 = mat.y3 / static_cast<T>(scalar);
  out.z3 = mat.z3 / static_cast<T>(scalar);
  out.w3 = mat.w3 / static_cast<T>(scalar);
  out.x4 = mat.x4 / static_cast<T>(scalar);
  out.y4 = mat.y4 / static_cast<T>(scalar);
  out.z4 = mat.z4 / static_cast<T>(scalar);
  out.w4 = mat.w4 / static_cast<T>(scalar);
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<4, 4, T> operator/(U scalar, const Mat<4, 4, T>& mat) noexcept {
  Mat<4, 4, T> out;
  out.x1 = static_cast<T>(scalar) / mat.x1;
  out.y1 = static_cast<T>(scalar) / mat.y1;
  out.z1 = static_cast<T>(scalar) / mat.z1;
  out.w1 = static_cast<T>(scalar) / mat.w1;
  out.x2 = static_cast<T>(scalar) / mat.x2;
  out.y2 = static_cast<T>(scalar) / mat.y2;
  out.z2 = static_cast<T>(scalar) / mat.z2;
  out.w2 = static_cast<T>(scalar) / mat.w2;
  out.x3 = static_cast<T>(scalar) / mat.x3;
  out.y3 = static_cast<T>(scalar) / mat.y3;
  out.z3 = static_cast<T>(scalar) / mat.z3;
  out.w3 = static_cast<T>(scalar) / mat.w3;
  out.x4 = static_cast<T>(scalar) / mat.x4;
  out.y4 = static_cast<T>(scalar) / mat.y4;
  out.z4 = static_cast<T>(scalar) / mat.z4;
  out.w4 = static_cast<T>(scalar) / mat.w4;
  return out;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<4, 4, T>::col_type operator/(const Mat<4, 4, T>& mat,
                                                  const Vec<4, U>& vec) noexcept {
  return ::ran::inverse(mat) * vec;
}

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF typename Mat<4, 4, T>::row_type operator/(const Vec<4, U>& vec,
                                                  const Mat<4, 4, T>& mat) noexcept {
  return vec * ::ran::inverse(mat);
}

} // namespace ran

#endif // #ifndef RAN_MATRIX4X4_HPP_
