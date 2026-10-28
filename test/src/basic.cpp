#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <ranmath/ran.hpp>

TEST_CASE("ranmath Vec3f32 default constructor", "[ranmath]") {
  const ran::Vec3f32 c{};
  REQUIRE(ran::fequal(c.x, 0.f));
  REQUIRE(ran::fequal(c.y, 0.f));
  REQUIRE(ran::fequal(c.z, 0.f));
}

TEST_CASE("ranmath Vec3f32 operations", "[ranmath]") {
  const ran::Vec3f32 a{1.0f, 2.0f, 3.0f};
  const ran::Vec3f32 b{4.0f, 5.0f, 6.0f};

  SECTION("addition and subtraction") {
    const ran::Vec3f32 sum = a + b;
    REQUIRE_THAT(sum.x, Catch::Matchers::WithinAbs(5.0f, 0.0001f));
    REQUIRE_THAT(sum.y, Catch::Matchers::WithinAbs(7.0f, 0.0001f));
    REQUIRE_THAT(sum.z, Catch::Matchers::WithinAbs(9.0f, 0.0001f));

    const ran::Vec3f32 diff = b - a;
    REQUIRE_THAT(diff.x, Catch::Matchers::WithinAbs(3.0f, 0.0001f));
    REQUIRE_THAT(diff.y, Catch::Matchers::WithinAbs(3.0f, 0.0001f));
    REQUIRE_THAT(diff.z, Catch::Matchers::WithinAbs(3.0f, 0.0001f));
  }

  SECTION("scalar multiplication") {
    const ran::Vec3f32 scaled = a * 2.0f;
    REQUIRE_THAT(scaled.x, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(scaled.y, Catch::Matchers::WithinAbs(4.0f, 0.0001f));
    REQUIRE_THAT(scaled.z, Catch::Matchers::WithinAbs(6.0f, 0.0001f));
  }

  SECTION("dot product") {
    const auto d = ran::dot(a, b);
    REQUIRE_THAT(d, Catch::Matchers::WithinAbs(32.0f, 0.0001f));
  }

  SECTION("cross product") {
    const ran::Vec3f32 c = ran::cross(a, b);
    REQUIRE_THAT(c.x, Catch::Matchers::WithinAbs(-3.0f, 0.0001f));
    REQUIRE_THAT(c.y, Catch::Matchers::WithinAbs(6.0f, 0.0001f));
    REQUIRE_THAT(c.z, Catch::Matchers::WithinAbs(-3.0f, 0.0001f));
  }

  SECTION("normalization and length") {
    const ran::Vec3f32 v{3.0f, 0.0f, 4.0f};
    const float len = ran::length(v);
    REQUIRE_THAT(len, Catch::Matchers::WithinAbs(5.0f, 0.0001f));

    const ran::Vec3f32 norm = ran::normalize(v);
    REQUIRE_THAT(norm.x, Catch::Matchers::WithinAbs(0.6f, 0.0001f));
    REQUIRE_THAT(norm.y, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(norm.z, Catch::Matchers::WithinAbs(0.8f, 0.0001f));
    REQUIRE_THAT(ran::length(norm), Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  }
}

TEST_CASE("ranmath Mat4f32 operations", "[ranmath]") {
  SECTION("identity matrix") {
    const ran::Mat4f32 id = ran::Mat4f32::identity();
    REQUIRE_THAT(id.x1, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(id.y2, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(id.z3, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(id.w4, Catch::Matchers::WithinAbs(1.0f, 0.0001f));

    REQUIRE_THAT(id.y1, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(id.z1, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(id.w1, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  }

  SECTION("matrix multiplication with identity") {
    const ran::Mat4f32 id = ran::Mat4f32::identity();
    const ran::Mat4f32 m{1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
                         9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

    const ran::Mat4f32 res = m * id;
    for (size_t i = 0; i < 16; ++i) {
      REQUIRE_THAT(res[i], Catch::Matchers::WithinAbs(m[i], 0.0001f));
    }
  }

  SECTION("matrix vector multiplication") {
    const ran::Mat4f32 id = ran::Mat4f32::identity();
    const ran::Vec4f32 v{1.0f, 2.0f, 3.0f, 1.0f};
    const ran::Vec4f32 res = id * v;

    REQUIRE_THAT(res.x, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(res.y, Catch::Matchers::WithinAbs(2.0f, 0.0001f));
    REQUIRE_THAT(res.z, Catch::Matchers::WithinAbs(3.0f, 0.0001f));
    REQUIRE_THAT(res.w, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  }
}

TEST_CASE("ranmath Quatf32 operations", "[ranmath]") {
  SECTION("identity quaternion") {
    const ran::Quatf32 q = ran::Quatf32::identity();
    REQUIRE_THAT(q.w, Catch::Matchers::WithinAbs(1.0f, 0.0001f));
    REQUIRE_THAT(q.x, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(q.y, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
    REQUIRE_THAT(q.z, Catch::Matchers::WithinAbs(0.0f, 0.0001f));
  }

  SECTION("quaternion dot product") {
    const ran::Quatf32 q1{1.0f, 0.0f, 0.0f, 0.0f};
    const ran::Quatf32 q2{1.0f, 0.0f, 0.0f, 0.0f};
    REQUIRE_THAT(ran::dot(q1, q2), Catch::Matchers::WithinAbs(1.0f, 0.0001f));
  }
}
