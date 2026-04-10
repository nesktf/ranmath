#ifndef RAN_FORWARD_HPP_
#define RAN_FORWARD_HPP_

#include "./concepts.hpp"

namespace ran {

namespace numdefs {

using usize = std::size_t;
using ptrdiff_t = std::ptrdiff_t;
using uintptr_t = std::uintptr_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using f32 = float;
using f64 = double;

} // namespace numdefs

using namespace numdefs;

/* Common functions */

template<meta::numeric_type T>
RAN_DECL T sqrt(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T rsqrt(T x) noexcept;

template<usize Iters = 1, meta::floating_point T>
RAN_DECL T qrsqrt(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T cos(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T sin(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T tan(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T acos(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T asin(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T atan(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T atan2(T y, T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T rad(T degs) noexcept;

template<meta::numeric_type T>
RAN_DECL T deg(T rads) noexcept;

template<meta::numeric_type T>
RAN_DECL T epsilon_err(T a, T b) noexcept;

template<meta::numeric_type T>
RAN_DECL T abs(T x) noexcept;

template<meta::numeric_type T>
RAN_DECL T clamp(T x, T min, T max) noexcept;

template<meta::numeric_type T>
RAN_DECL T max(T a, T b) noexcept;

template<meta::numeric_type T>
RAN_DECL T min(T a, T b) noexcept;

template<meta::numeric_type TL, meta::numeric_type TR>
RAN_DECL auto periodic_add(const TL& a, const TR& b, decltype(a + b) min,
                           decltype(a + b) max) noexcept;

template<meta::floating_point T>
RAN_DECL bool fequal(T a, T b) noexcept;

/* Vector types */

template<usize N, meta::numeric_type T>
struct Vec;

template<usize N, usize M, meta::numeric_type T>
struct Mat;

template<meta::numeric_type T>
struct Quat;

using Vec2f32 = Vec<2, f32>;
using Vec3f32 = Vec<3, f32>;
using Vec4f32 = Vec<4, f32>;
using Vec2f64 = Vec<2, f64>;
using Vec3f64 = Vec<3, f64>;
using Vec4f64 = Vec<4, f64>;

using Vec2s32 = Vec<2, s32>;
using Vec3s32 = Vec<3, s32>;
using Vec4s32 = Vec<4, s32>;
using Vec2u32 = Vec<2, u32>;
using Vec3u32 = Vec<3, u32>;
using Vec4u32 = Vec<4, u32>;

using Mat3f32 = Mat<4, 4, f32>;
using Mat4f32 = Mat<4, 4, f32>;
using Mat3f64 = Mat<4, 4, f64>;
using Mat4f64 = Mat<4, 4, f64>;

using Quatf32 = Quat<f32>;
using Quatf64 = Quat<f64>;

/* Vec2 functions */

template<typename T>
RAN_DECL Vec<2, T> operator==(const Vec<2, T>& a, const Vec<2, T>& b) noexcept;

template<typename T>
RAN_DECL Vec<2, T> operator!=(const Vec<2, T>& a, const Vec<2, T>& b) noexcept;

template<typename T>
RAN_DECL Vec<2, T> operator+(const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<2, T> operator+(const Vec<2, T>& a, const Vec<2, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator+(const Vec<2, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator+(U scalar, const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<2, T> operator-(const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<2, T> operator-(const Vec<2, T>& a, const Vec<2, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator-(const Vec<2, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator-(U scalar, const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<2, T> operator*(const Vec<2, T>& a, const Vec<2, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator*(const Vec<2, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator*(U scalar, const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<2, T> operator/(const Vec<2, T>& a, const Vec<2, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator/(const Vec<2, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<2, T> operator/(U scalar, const Vec<2, T>& vec) noexcept;

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DECL Vec<2, U> vec_cast(const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL T length2(const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL T length(const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL void normalize_at(Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<2, T> normalize(const Vec<2, T>& vec) noexcept;

template<typename T>
RAN_DECL T dot(const Vec<2, T>& a, const Vec<2, T>& b) noexcept;

/* Vec3 functions */

template<typename T>
RAN_DECL bool operator==(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<typename T>
RAN_DECL bool operator!=(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<typename T>
RAN_DECL Vec<3, T> operator+(const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<3, T> operator+(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator+(const Vec<3, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator+(U scalar, const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<3, T> operator-(const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<3, T> operator-(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator-(const Vec<3, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator-(U scalar, const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<3, T> operator*(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator*(const Vec<3, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator*(U scalar, const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<3, T> operator/(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator/(const Vec<3, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator/(U scalar, const Vec<3, T>& vec) noexcept;

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DECL Vec<3, U> vec_cast(const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL T length2(const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL T length(const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL void normalize_at(Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<3, T> normalize(const Vec<3, T>& vec) noexcept;

template<typename T>
RAN_DECL T dot(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<typename T>
RAN_DECL Vec<3, T> cross(const Vec<3, T>& a, const Vec<3, T>& b) noexcept;

template<meta::numeric_type T>
RAN_DECL void gl_to_cartesian_at(Vec<3, T>& vec) noexcept;

template<meta::numeric_type T>
RAN_DECL Vec<3, T> gl_to_cartesian(const Vec<3, T>& vec) noexcept;

template<meta::numeric_type T>
RAN_DECL Vec<3, T> sph_to_cartesian(T rho, T theta, T phi) noexcept;

template<meta::numeric_type T>
RAN_DECL void cartesian_to_gl_at(Vec<3, T>& vec) noexcept;

template<meta::numeric_type T>
RAN_DECL Vec<3, T> cartesian_to_gl(const Vec<3, T>& vec) noexcept;

/* Vec4 functions */

template<typename T>
RAN_DECL bool operator==(const Vec<4, T>& a, const Vec<4, T>& b) noexcept;

template<typename T>
RAN_DECL bool operator!=(const Vec<4, T>& a, const Vec<4, T>& b) noexcept;

template<typename T>
RAN_DECL Vec<4, T> operator+(const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<4, T> operator+(const Vec<4, T>& a, const Vec<4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator+(const Vec<4, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator+(U scalar, const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<4, T> operator-(const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<4, T> operator-(const Vec<4, T>& a, const Vec<4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator-(const Vec<4, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator-(U scalar, const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<4, T> operator*(const Vec<4, T>& a, const Vec<4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator*(const Vec<4, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator*(U scalar, const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<4, T> operator/(const Vec<4, T>& a, const Vec<4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator/(const Vec<4, T>& vec, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator/(U scalar, const Vec<4, T>& vec) noexcept;

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DECL Vec<4, U> vec_cast(const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL T length2(const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL T length(const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL void normalize_at(Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL Vec<4, T> normalize(const Vec<4, T>& vec) noexcept;

template<typename T>
RAN_DECL T dot(const Vec<4, T>& a, const Vec<4, T>& b) noexcept;

/* Mat3 functions */

template<typename T>
RAN_DECL bool operator==(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept;

template<typename T>
RAN_DECL bool operator!=(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> operator+(const Mat<3, 3, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> operator+(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator+(const Mat<3, 3, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator+(U scalar, const Mat<3, 3, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> operator-(const Mat<3, 3, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> operator-(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator-(const Mat<3, 3, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator-(U scalar, const Mat<3, 3, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> operator*(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator*(const Mat<3, 3, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator*(U scalar, const Mat<3, 3, T>& mat) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<3, 3, T>::col_type operator*(const Mat<3, 3, T>& mat,
                                                   const Vec<3, U>& vec) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<3, 3, T>::row_type operator*(const Vec<3, U>& vec,
                                                   const Mat<3, 3, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> operator/(const Mat<3, 3, T>& a, const Mat<3, 3, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator/(const Mat<3, 3, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> operator/(U scalar, const Mat<3, 3, T>& mat) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<3, 3, T>::col_type operator/(const Mat<3, 3, T>& mat,
                                                   const Vec<3, U>& vec) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<3, 3, T>::row_type operator/(const Vec<3, U>& vec,
                                                   const Mat<3, 3, T>& mat) noexcept;

template<typename T>
RAN_DECL T determinant(const Mat<3, 3, T>& m) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> inverse(const Mat<3, 3, T>& m) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> transpose(const Mat<3, 3, T>& m) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> translate(const Mat<3, 3, T>& m, const Vec<2, U>& v) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> scale(const Mat<3, 3, T>& m, const Vec<2, U>& v) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> rotate(const Mat<3, 3, T>& m, U ang) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> lookat_rh(const Vec<3, T>& dir, const Vec<3, U>& up) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<3, 3, T> lookat_lh(const Vec<3, T>& dir, const Vec<3, U>& up) noexcept;

/* Mat4 functions */

template<typename T>
RAN_DECL bool operator==(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept;

template<typename T>
RAN_DECL bool operator!=(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> operator+(const Mat<4, 4, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> operator+(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator+(const Mat<4, 4, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator+(U scalar, const Mat<4, 4, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> operator-(const Mat<4, 4, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> operator-(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator-(const Mat<4, 4, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator-(U scalar, const Mat<4, 4, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> operator*(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator*(const Mat<4, 4, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator*(U scalar, const Mat<4, 4, T>& mat) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<4, 4, T>::col_type operator*(const Mat<4, 4, T>& mat,
                                                   const Vec<4, U>& vec) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<4, 4, T>::row_type operator*(const Vec<4, U>& vec,
                                                   const Mat<4, 4, T>& mat) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> operator/(const Mat<4, 4, T>& a, const Mat<4, 4, T>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator/(const Mat<4, 4, T>& mat, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> operator/(U scalar, const Mat<4, 4, T>& mat) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<4, 4, T>::col_type operator/(const Mat<4, 4, T>& mat,
                                                   const Vec<4, U>& vec) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL typename Mat<4, 4, T>::row_type operator/(const Vec<4, U>& vec,
                                                   const Mat<4, 4, T>& mat) noexcept;

template<typename T>
RAN_DECL T determinant(const Mat<4, 4, T>& m) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> inverse(const Mat<4, 4, T>& m) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> transpose(const Mat<4, 4, T>& m) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> translate(const Mat<4, 4, T>& m, const Vec<3, U>& v) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Mat<4, 4, T> scale(const Mat<4, 4, T>& m, const Vec<3, U>& v) noexcept;

template<typename T, meta::numeric_convertible<T> U, meta::numeric_convertible<T> V>
RAN_DECL Mat<4, 4, T> rotate(const Mat<4, 4, T>& m, U angle, const Vec<3, V>& axis) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> to_mat3(const Mat<4, 4, T>& m) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> to_mat4(const Mat<3, 3, T>& m) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> lookat_rh(const Vec<3, T>& pos, const Vec<3, T>& center,
                                const Vec<3, T>& up) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> lookat_lh(const Vec<3, T>& pos, const Vec<3, T>& center,
                                const Vec<3, T>& up) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> ortho(T left, T right, T bottom, T top) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> ortho(T left, T right, T bottom, T top, T znear, T zfar) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> perspective(T fov, T aspect, T znear, T zfar) noexcept;

/* Quat functions */

template<typename T>
RAN_DECL bool operator==(const Quat<T>& a, const Quat<T>& b) noexcept;

template<typename T>
RAN_DECL bool operator!=(const Quat<T>& a, const Quat<T>& b) noexcept;

template<typename T>
RAN_DECL Quat<T> operator+(const Quat<T>& q) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator+(const Quat<T>& a, const Quat<U>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator+(const Quat<T>& q, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator+(U scalar, const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL Quat<T> operator-(const Quat<T>& q) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator-(const Quat<T>& a, const Quat<U>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator-(const Quat<T>& q, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator-(U scalar, const Quat<T>& q) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator*(const Quat<T>& a, const Quat<U>& b) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator*(const Quat<T>& q, const Vec<3, U>& v) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<3, T> operator*(const Vec<3, U>& v, const Quat<T>& q) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator*(const Quat<T>& q, const Vec<4, U>& v) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Vec<4, T> operator*(const Vec<4, U>& v, const Quat<T>& q) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator*(const Quat<T>& q, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator*(U scalar, const Quat<T>& q) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator/(const Quat<T>& q, U scalar) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> operator/(U scalar, const Quat<T>& q) noexcept;

template<typename U, typename T>
requires(meta::numeric_convertible<U, T>)
RAN_DECL Quat<U> vec_cast(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL Quat<T> conjugate(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL Quat<T> inverse(const Quat<T>& q) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL T dot(const Quat<T>& a, const Quat<U>& b) noexcept;

template<typename T>
RAN_DECL Vec<3, T> to_euler(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL T roll(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL T pitch(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL T yaw(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL Mat<3, 3, T> to_mat3(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL Mat<4, 4, T> to_mat4(const Quat<T>& q) noexcept;

template<typename T>
RAN_DECL Quat<T> to_quat(const Mat<3, 3, T>& m) noexcept;

template<typename T>
RAN_DECL Quat<T> to_quat(const Mat<4, 4, T>& m) noexcept;

template<typename T>
RAN_DECL Quat<T> to_quat(const Vec<3, T>& euler) noexcept;

template<typename T, meta::numeric_convertible<T> U>
RAN_DECL Quat<T> to_quat(T angle, const Vec<3, U>& axis) noexcept;

template<typename T>
RAN_DECL Vec<3, T> to_vec3(const Quat<T>& q) noexcept;

/* AABB */

template<meta::numeric_type T>
struct RectPos {
  T x, y;
  T width, height;
};

template<meta::numeric_type T>
struct CircPos {
  T x, y;
  T radius;
};

template<meta::numeric_type T>
RAN_DECL bool collision_aabb(const RectPos<T>& a, const RectPos<T>& b);

template<meta::numeric_type T>
RAN_DECL bool collision_aabb(const RectPos<T>& a, const CircPos<T>& b);

template<meta::numeric_type T>
RAN_DECL bool collision_aabb(const CircPos<T>& a, const RectPos<T>& b);

template<meta::numeric_type T>
RAN_DECL bool collision_aabb(const CircPos<T>& a, const CircPos<T>& b);

/* Integrators */

template<meta::numeric_type T>
struct IntegratorTrap;

template<meta::numeric_type T>
struct IntegratorSimp13;

template<meta::numeric_type T>
struct IntegratorSimp38;

/* ODE solvers */

template<meta::numeric_type T>
struct OdeEuler;

template<meta::numeric_type T>
struct OdeRK4;

/* Easing functions */

template<typename T, meta::floating_point U>
struct EasingLinear;

template<typename T, meta::floating_point U>
struct EasingLinear;

template<typename T, meta::floating_point U>
struct EasingElasticIn;

template<typename T, meta::floating_point U>
struct EasingElasticInOut;

template<typename T, meta::floating_point U>
struct EasingPow;

/* Interpolators */

constexpr u32 dynamic_step = std::numeric_limits<u32>::max();

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn, u32 StepSize = dynamic_step>
struct StepLerp;

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn, u32 StepSize = dynamic_step>
struct StepLerpFn;

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn>
struct DeltaLerp;

template<typename T, meta::floating_point U, meta::lerp_fn<T, U> Fn>
struct DeltaLerpFn;

} // namespace ran

#endif // #ifndef RAN_FORWARD_HPP_
