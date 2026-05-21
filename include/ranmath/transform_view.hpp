#ifndef RAN_VIEW_HPP_
#define RAN_VIEW_HPP_

#include <ranmath/forward.hpp>

namespace ran {

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

} // namespace ran

#endif // #ifndef RAN_VIEW_HPP_
