#include "../Catch.hpp"
#include <ananasgfx/font/Character.hpp>

TEST_CASE("font::Character") {
    font::Character character(1, 2, 3, 4, std::make_shared<gfx::Bitmap>(nullptr, 128,128,2));

    SECTION("const gfx::Bitmap& getBitmap() const noexcept") {
        auto& bitmap = character.getBitmap();
        REQUIRE(bitmap.getWidth() == 128);
        REQUIRE(bitmap.getHeight() == 128);
    }

    SECTION("long getCharCode() const noexcept") {
        REQUIRE(character.getCharCode() == 1);
    }

    SECTION("float getAdvanceX() const noexcept") {
        REQUIRE(character.getAdvanceX() == Approx(2.0f));
    }

    SECTION("float getUnderBaseline() const noexcept") {
        REQUIRE(character.getUnderBaseline() == Approx(3.0f));
    }

    SECTION("float getOverBaseline() const noexcept") {
        REQUIRE(character.getOverBaseline() == Approx(4.0f));
    }

}