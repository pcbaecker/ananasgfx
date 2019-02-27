#include <ananasgfx/d2/RectangleRoundCorner.hpp>
#include "../Catch.hpp"

TEST_CASE("d2::RectangleRoundCorner") {

    d2::RectangleRoundCorner rrc;

    SECTION("void setRadius(float) noexcept") {
        // Test default value
        REQUIRE(Approx(8.0f) == rrc.getRadius());

        // Set the value
        rrc.setRadius(125.0f);
        REQUIRE(Approx(125.0f) == rrc.getRadius());
    }

    SECTION("float getRadius() const noexcept") {
        // Test default value
        REQUIRE(Approx(8.0f) == rrc.getRadius());

        // Set the value
        rrc.setRadius(125.0f);
        REQUIRE(Approx(125.0f) == rrc.getRadius());
    }

}