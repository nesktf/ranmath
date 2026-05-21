#ifndef RAN_TRANSFORM_HPP_
#define RAN_TRANSFORM_HPP_

#include <ranmath/forward.hpp>

namespace ran {

template<typename T, meta::numeric_convertible<T> U>
RAN_DEF Mat<3, 3, T> translate(const Mat<3, 3, T>& m, const Vec<2, U>& v) noexcept {
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

} // namespace ran

#endif // #ifndef RAN_TRANSFORM_HPP_
