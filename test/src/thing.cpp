#include <catch2/catch_test_macros.hpp>

#include <ranmath/ran.hpp>

TEST_CASE("thing", "[thing]") {
  ran::Vec3f32 c{};
  REQUIRE(ran::fequal(c.x, 0.f));
}
