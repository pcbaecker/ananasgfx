#include "../Catch.hpp"
#include <ananasgfx/gfx/Touch.hpp>

TEST_CASE("gfx::Touch") {

    gfx::Touch touch(1, 2.3, 3.4);

    SECTION("double getLastX() const noexcept") {
        // Default value
        REQUIRE(Approx(0.0) == touch.getLastX());

        // Set value
        touch.setLast(5.6, 7.8);
        REQUIRE(Approx(5.6) == touch.getLastX());
    }

    SECTION("double getLastY() const noexcept") {
        // Default value
        REQUIRE(Approx(0.0) == touch.getLastY());

        // Set value
        touch.setLast(5.6, 7.8);
        REQUIRE(Approx(7.8) == touch.getLastY());
    }

    SECTION("void setLast(double, double) noexcept") {
        // Default value
        REQUIRE(Approx(0.0) == touch.getLastX());
        REQUIRE(Approx(0.0) == touch.getLastY());

        // Set value
        touch.setLast(5.6, 7.8);
        REQUIRE(Approx(5.6) == touch.getLastX());
        REQUIRE(Approx(7.8) == touch.getLastY());
    }

    SECTION("glm::vec2 getLocalLast(d2::Node* node) noexcept") {

    }

}