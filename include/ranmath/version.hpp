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

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

#ifndef RAN_ASSERT
#include <cassert>
#define RAN_ASSERT(_cond) assert(_cond)
#endif

#ifdef __cpp_exceptions
#define RAN_THROW(_ex) throw _ex
#else
#define RAN_THROW(_ex) RAN_ASSERT(false && "Thrown exception: " #_ex)
#endif

#define RAN_THROW_IF(_cond, _ex) \
  if ((_cond)) {                 \
    RAN_THROW(_ex);              \
  }

#include <algorithm>
#include <bit>
#include <complex>
#include <concepts>
#include <limits>
#include <memory>
#include <utility>

#define RAN_DEFAULT_SPECIAL(_typename)                                     \
  RAN_CONSTEXPR _typename() noexcept = default;                            \
  RAN_CONSTEXPR _typename(const _typename&) noexcept = default;            \
  RAN_CONSTEXPR _typename(_typename&&) noexcept = default;                 \
  RAN_CONSTEXPR _typename& operator=(const _typename&) noexcept = default; \
  RAN_CONSTEXPR _typename& operator=(_typename&&) noexcept = default

namespace ran {

class Error : public std::exception {
public:
  Error(const char* msg) noexcept : _msg(msg) {}

public:
  const char* what() const noexcept override { return _msg; }

private:
  const char* _msg;
};

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
static_assert(sizeof(f32) == 4);

using f64 = double;
static_assert(sizeof(f64) == 8);

} // namespace numdefs

using namespace numdefs;

} // namespace ran

#endif // #ifndef RAN_VERSION_HPP_
