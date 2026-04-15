#ifndef RAN_AABB_HPP_
#define RAN_AABB_HPP_

#include <ranmath/forward.hpp>

namespace ran {

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

// clang-format off
template<typename T>
RAN_DEF bool collision_aabb(const RectPos<T>& a, const RectPos<T>& b) {
  // AABB assumes pos is the lower left corner
  // Normalize scale, since obj.pos it's the quad's center
  const T a_width = a.width / T(2);
  const T a_height = a.height / T(2);
  const T b_width = a.width / T(2);
  const T b_height = a.height / T(2);
  const bool collision_x = a.x + a_width >= (b.x - b_width) && 
                           b.x + b_width >= (a.x - a_width);
  const bool collision_y = a.y + a_height >= (b.y - b_height) &&
                           b.y + b_height >= (a.y - a_height);

  return collision_x && collision_y;
}

// clang-format on

template<typename T>
RAN_DEF bool collision_aabb(const RectPos<T>& a, const CircPos<T>& b) {
  // No need to normalize pos1 to be the center
  const T sq_rad = b.radius * b.radius;
  const T half_rect_w = a.width / T(2);
  const T half_rect_h = a.height / T(2);

  const T diff_x = b.x - a.x;
  const T diff_y = b.y - a.y;

  const T closest_x = (a.x + ::ran::clamp(diff_x, -half_rect_w, half_rect_w)) - b.x;
  const T closest_y = (a.y + ::ran::clamp(diff_y, -half_rect_h, half_rect_h)) - b.y;

  const T sq_len = (closest_x * closest_x) + (closest_y * closest_y);

  return sq_len < sq_rad;
}

template<typename T>
RAN_DEF bool collision_aabb(const CircPos<T>& a, const RectPos<T>& b) {
  return collision_aabb(b, a);
}

template<typename T>
RAN_DEF bool collision_aabb(const CircPos<T>& a, const CircPos<T>& b) {
  const T diff_x = b.x - a.x;
  const T diff_y = b.y - a.y;
  const T sq_sum = (a.radius + b.radius) * (a.radius + b.radius);
  const T sq_len = (diff_x * diff_x) + (diff_y * diff_y);
  return sq_len < sq_sum;
}

} // namespace ran

#endif // #ifndef RAN_AABB_HPP_
