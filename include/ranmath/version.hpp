#ifndef RAN_VERSION_HPP_
#define RAN_VERSION_HPP_

#ifdef RAN_DISABLE_CONSTEXPR
#define RAN_CONSTEXPR inline
#else
#define RAN_CONSTEXPR constexpr
#endif

#if defined(_MSC_VER)
#define RAN_ALWAYSINLINE __forceinline
#define RAN_NO_INLINE    __declspec((noinline))
#elif defined(__GNUC__) || defined(__MINGW32__)
#define RAN_ALWAYS_INLINE inline __attribute__((__always_inline__))
#define RAN_NO_INLINE     __attribute__((__noinline__))
#elif defined(__clang__)
#define RAN_ALWAYS_INLINE __forceinline__
#define RAN_NO_INLINE     __noinline__
#else
#define RAN_ALWAYS_INLINE inline
#define RAN_NO_INLINE
#endif

#ifdef RAN_FORCE_INLINE
#define RAN_INLINE RAN_ALWAYS_INLINE
#else
#define RAN_INLINE inline
#endif

#define RAN_DECL RAN_CONSTEXPR
#define RAN_DEF  RAN_CONSTEXPR RAN_INLINE

#define RAN_VER_MAJ 0
#define RAN_VER_MIN 0
#define RAN_VER_REV 1

#include <cstddef>
#include <cstdint>

#ifndef RAN_ASSERT
#include <cassert>
#define RAN_ASSERT(_cond) assert(_cond)
#endif

#include <algorithm>
#include <bit>
#include <cmath>
#include <concepts>
#include <limits>
#include <utility>

#define RAN_DEFAULT_SPECIAL(_typename)                                     \
  RAN_CONSTEXPR _typename() noexcept = default;                            \
  RAN_CONSTEXPR _typename(const _typename&) noexcept = default;            \
  RAN_CONSTEXPR _typename(_typename&&) noexcept = default;                 \
  RAN_CONSTEXPR _typename& operator=(const _typename&) noexcept = default; \
  RAN_CONSTEXPR _typename& operator=(_typename&&) noexcept = default

#endif // #ifndef RAN_VERSION_HPP_
