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

template<meta::bone_metadata BoneMetadata, meta::numeric_type T, typename Alloc>
struct SkelRigTransform {
public:
  using matrix_type = Mat<4, 4, T>;
  using allocator_type = Alloc;
  using bone_metadata_type = BoneMetadata;

public:
  RAN_INLINE SkelRigTransform(usize count, const BoneMetadata* bones, const matrix_type* locals,
                              const matrix_type* invs, const Alloc& alloc = {}) :
      _alloc(alloc), _locals(locals), _invs(invs), _bones(bones), _count(count) {
    RAN_THROW_IF(!_count, ::ran::Error("No bone count"));
    RAN_THROW_IF(!_bones, ::ran::Error("No bone metadata array"));
    RAN_THROW_IF(!_locals, ::ran::Error("No local matrix array"));
    RAN_THROW_IF(!_invs, ::ran::Error("No inverse model matrix array"));

    _cache = _alloc.allocate(2 * count);
    RAN_THROW_IF(!_cache, std::bad_alloc());
  }

public:
  RAN_INLINE void update_bones(const matrix_type& root_transform,
                               const matrix_type* bone_transforms, matrix_type* output) {
    matrix_type* locals = _cache;
    matrix_type* models = _cache + _count;

    // Populate bone local transforms
    locals[0] = root_transform * _locals[0] * bone_transforms[0];
    for (usize i = 1; i < _count; ++i) {
      locals[i] = _locals[i] * bone_transforms[i];
    }

    // Populate bone model transforms
    models[0] = locals[0]; // Root transform
    for (usize i = 1; i < _count; ++i) {
      const s32 parent = static_cast<s32>(_bones[i].parent);
      // Since the bone hierarchy is sorted, we should be able to read the
      // parent model matrix safely
      RAN_ASSERT(parent < (s32)_count);
      models[i] = models[parent] * locals[i];
    }

    // Fill output
    for (usize i = 0; i < _count; ++i) {
      output[i] = models[i] * _invs[i];
    }
  }

  RAN_INLINE void operator()(const matrix_type& root_transform, const matrix_type* transforms,
                             matrix_type* output) {
    update_bones(root_transform, transforms, output);
  }

public:
  RAN_INLINE ~SkelRigTransform() noexcept {
    if (_cache) {
      _alloc.deallocate(_cache, 2 * _count);
    }
  }

  RAN_INLINE SkelRigTransform(SkelRigTransform&& other) noexcept(
    std::is_nothrow_move_constructible_v<Alloc>) :
      _alloc(std::move(other._alloc)), _locals(other._locals), _invs(other._invs),
      _bones(other._bones), _count(other._count) {
    other._cache = nullptr;
  }

  RAN_INLINE SkelRigTransform&
  operator=(SkelRigTransform&& other) noexcept(std::is_nothrow_move_assignable_v<Alloc>) {
    if (&other == this) {
      return *this;
    }
    if (_cache) {
      _alloc.deallocate(_cache, 2 * _count);
    }

    _alloc = std::move(other._alloc);
    _locals = other._locals;
    _invs = other._invs;
    _bones = other._bones;
    _cache = other._cache;
    _count = other._count;

    other._cache = nullptr;

    return *this;
  }

  SkelRigTransform(const SkelRigTransform&) = delete;
  SkelRigTransform& operator=(const SkelRigTransform&) = delete;

public:
  usize bone_count() const noexcept { return _count; }

private:
  [[no_unique_address]] Alloc _alloc;
  const matrix_type* _locals;
  const matrix_type* _invs;
  const BoneMetadata* _bones;
  matrix_type* _cache;
  usize _count;
};

} // namespace ran

#endif // #ifndef RAN_TRANSFORM_HPP_
