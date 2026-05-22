#ifndef RAN_AABB_HPP_
#define RAN_AABB_HPP_

#include <ranmath/forward.hpp>

namespace ran {

template<meta::numeric_type T>
struct Rect2D {
  T x, y;
  T width, height;
};

template<meta::numeric_type T>
struct Circ2D {
  T x, y;
  T radius;
};

template<meta::numeric_type T, meta::numeric_convertible<T> U>
RAN_DEF bool collision_aabb(const Rect2D<T>& rect_a, const Rect2D<U>& rect_b) {
  // AABB assumes pos is the lower left corner
  // Normalize scale, since obj.pos it's the quad's center
  const auto a_width = rect_a.width / T(2);
  const auto a_height = rect_a.height / T(2);
  const auto b_width = static_cast<T>(rect_b.width) / T(2);
  const auto b_height = static_cast<T>(rect_b.height) / T(2);

  const bool collision_x = rect_a.x + a_width >= (static_cast<T>(rect_b.x) - b_width) &&
                           static_cast<T>(rect_b.x) + b_width >= (rect_a.x - a_width);
  const bool collision_y = rect_a.y + a_height >= (static_cast<T>(rect_b.y) - b_height) &&
                           static_cast<T>(rect_b.y) + b_height >= (rect_a.y - a_height);
  return collision_x && collision_y;
}

template<meta::numeric_type T, meta::numeric_convertible<T> U>
RAN_DEF bool collision_aabb(const Rect2D<T>& rect, const Circ2D<U>& circ) {
  // No need to normalize rect to be the center
  const auto half_w = rect.width / T(2);
  const auto half_h = rect.height / T(2);
  const auto dx = static_cast<T>(circ.x) - rect.x;
  const auto dy = static_cast<T>(circ.y) - rect.y;
  const auto sq_rad = static_cast<T>(circ.radius * circ.radius);

  const auto closest_x = (rect.x + ::ran::clamp(dx, -half_w, half_w)) - static_cast<T>(circ.x);
  const auto closest_y = (rect.y + ::ran::clamp(dy, -half_h, half_h)) - static_cast<T>(circ.y);
  const auto sq_len = (closest_x * closest_x) + (closest_y * closest_y);
  return sq_len < sq_rad;
}

template<meta::numeric_type T, meta::numeric_convertible<T> U>
RAN_DEF bool collision_aabb(const Circ2D<T>& circ, const Rect2D<U>& rect) {
  return collision_aabb(rect, circ);
}

template<meta::numeric_type T, meta::numeric_convertible<T> U>
RAN_DEF bool collision_aabb(const Circ2D<T>& circ_a, const Circ2D<U>& circ_b) {
  const auto dx = static_cast<T>(circ_b.x) - circ_a.x;
  const auto dy = static_cast<T>(circ_b.y) - circ_a.y;
  const auto sq_sum = (circ_a.radius + static_cast<T>(circ_b.radius)) *
                      (circ_a.radius + static_cast<T>(circ_b.radius));
  const auto sq_len = (dx * dx) + (dy * dy);
  return sq_len < sq_sum;
}

template<meta::numeric_type T, meta::numeric_type U, meta::numeric_convertible<T> V>
RAN_DEF bool collision_aabb(const Rect2D<T> rect, U angle, const Circ2D<V>& circ) {
  const auto dx = static_cast<T>(circ.x) - rect.x;
  const auto dy = static_cast<T>(circ.y) - rect.y;
  const auto half_w = rect.width / T(2);
  const auto half_h = rect.height / T(2);
  const auto sq_rad = static_cast<T>(circ.radius * circ.radius);

  const auto s = ::ran::sin(-static_cast<T>(angle));
  const auto c = ::ran::cos(-static_cast<T>(angle));
  const auto local_x = c * dx - s * dy;
  const auto local_y = s * dx + c * dy;

  const auto closest_x = local_x - ::ran::clamp(local_x, -half_w, half_w);
  const auto closest_y = local_y - ::ran::clamp(local_y, -half_h, half_h);
  const auto sq_len = (closest_x * closest_x) + (closest_y * closest_y);
  return sq_len < sq_rad;
}

} // namespace ran

#endif // #ifndef RAN_AABB_HPP_
