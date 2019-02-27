#include <ananasgfx/d2/Sprite.hpp>
#include "../Catch.hpp"

TEST_CASE("d2::Sprite") {

    d2::Sprite sprite;

    SECTION("bool init() noexcept") {
        // Can not be tested without a working OpenGL context
    }

    SECTION("void setFilename(const std::string&) noexcept") {
        // Test default value
        REQUIRE(sprite.getFilename().empty());

        // Set value
        sprite.setFilename("myfilename");
        REQUIRE("myfilename" == sprite.getFilename());
    }

    SECTION("const std::string& getFilename() const noexcept") {
        // Test default value
        REQUIRE(sprite.getFilename().empty());

        // Set value
        sprite.setFilename("myfilename");
        REQUIRE("myfilename" == sprite.getFilename());
    }

    SECTION("void setTexture(gfx::Texture*) noexcept") {
        // Test default value
        REQUIRE(nullptr == sprite.getTexture());

        // set value (Fake pointer because we cant construct a texture without OpenGL context)
        gfx::Texture* pTexture = (gfx::Texture*)123;
        sprite.setTexture(pTexture);
        REQUIRE(pTexture == sprite.getTexture());
    }

    SECTION("gfx::Texture* getTexture() const noexcept") {
        // Test default value
        REQUIRE(nullptr == sprite.getTexture());

        // set value (Fake pointer because we cant construct a texture without OpenGL context)
        gfx::Texture* pTexture = (gfx::Texture*)123;
        sprite.setTexture(pTexture);
        REQUIRE(pTexture == sprite.getTexture());
    }

    SECTION("void setVerticalFlip(bool) noexcept") {
        // Test default value
        REQUIRE_FALSE(sprite.isVerticallyFlipped());

        // Set value
        sprite.setVerticalFlip(true);
        REQUIRE(sprite.isVerticallyFlipped());
    }

    SECTION("bool isVerticallyFlipped() const noexcept") {
        // Test default value
        REQUIRE_FALSE(sprite.isVerticallyFlipped());

        // Set value
        sprite.setVerticalFlip(true);
        REQUIRE(sprite.isVerticallyFlipped());
    }

    SECTION("void draw() noexcept") {
        // Cannot test this method without OpenGL context
    }
}