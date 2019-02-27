#include <ananasgfx/d2/Ring.hpp>
#include "../Catch.hpp"

TEST_CASE("d2::Ring") {

    d2::Ring ring;

    SECTION("void setThickness(float) noexcept") {
        // Test default value
        REQUIRE(Approx(10.0f) == ring.getThickness());

        // Set value
        ring.setThickness(16.0f);
        REQUIRE(Approx(16.0f) == ring.getThickness());
    }

    SECTION("float getThickness() const noexcept") {
        // Test default value
        REQUIRE(Approx(10.0f) == ring.getThickness());

        // Set value
        ring.setThickness(16.0f);
        REQUIRE(Approx(16.0f) == ring.getThickness());
    }

    SECTION("void setAngle(float) noexcept") {
        // Test default value
        REQUIRE(Approx(360.0f) == ring.getAngle());

        // Set value
        ring.setAngle(12.0f);
        REQUIRE(Approx(12.0f) == ring.getAngle());
    }

    SECTION("float getAngle() const noexcept") {
        // Test default value
        REQUIRE(Approx(360.0f) == ring.getAngle());

        // Set value
        ring.setAngle(12.0f);
        REQUIRE(Approx(12.0f) == ring.getAngle());
    }

    SECTION("void setStartAngle(float) noexcept") {
        // Test default value
        REQUIRE(Approx(0.0f) == ring.getStartAngle());

        // Set value
        ring.setStartAngle(145.0f);
        REQUIRE(Approx(145.0f) == ring.getStartAngle());
    }

}