#include "../Catch.hpp"
#include <ananasgfx/gfx/WindowConfiguration.hpp>

TEST_CASE("gfx::WindowConfiguration") {

    gfx::WindowConfiguration windowConfiguration;

    SECTION("void setTitle(std::string) noexcept") {
        // Default value
        REQUIRE(windowConfiguration.getTitle().empty());

        // Set value
        windowConfiguration.setTitle("mytitle");
        REQUIRE("mytitle" == windowConfiguration.getTitle());
    }

    SECTION("const std::string& getTitle() const noexcept") {
        // Default value
        REQUIRE(windowConfiguration.getTitle().empty());

        // Set value
        windowConfiguration.setTitle("mytitle");
        REQUIRE("mytitle" == windowConfiguration.getTitle());
    }

    SECTION("void setWidth(int) noexcept") {
        // Default value
        REQUIRE(0 == windowConfiguration.getWidth());

        // Set value
        windowConfiguration.setWidth(123);
        REQUIRE(123 == windowConfiguration.getWidth());
    }

    SECTION("int getWidth() const noexcept") {
        // Default value
        REQUIRE(0 == windowConfiguration.getWidth());

        // Set value
        windowConfiguration.setWidth(123);
        REQUIRE(123 == windowConfiguration.getWidth());
    }

    SECTION("void setHeight(int) noexcept") {
        // Default value
        REQUIRE(0 == windowConfiguration.getHeight());

        // Set value
        windowConfiguration.setHeight(234);
        REQUIRE(234 == windowConfiguration.getHeight());
    }

    SECTION("int getHeight() const noexcept") {
        // Default value
        REQUIRE(0 == windowConfiguration.getHeight());

        // Set value
        windowConfiguration.setHeight(234);
        REQUIRE(234 == windowConfiguration.getHeight());
    }

    SECTION("void setFullscreen(bool) noexcept") {
        // Default value
        REQUIRE_FALSE(windowConfiguration.fullscreen());

        // Set value
        windowConfiguration.setFullscreen(true);
        REQUIRE(windowConfiguration.fullscreen());
    }

    SECTION("bool fullscreen() const noexcept") {
        // Default value
        REQUIRE_FALSE(windowConfiguration.fullscreen());

        // Set value
        windowConfiguration.setFullscreen(true);
        REQUIRE(windowConfiguration.fullscreen());
    }

    SECTION("void setHideCursor(bool) noexcept") {
        // Default value
        REQUIRE_FALSE(windowConfiguration.hideCursor());

        // Set value
        windowConfiguration.setHideCursor(true);
        REQUIRE(windowConfiguration.hideCursor());
    }

    SECTION("bool hideCursor() const noexcept") {
        // Default value
        REQUIRE_FALSE(windowConfiguration.hideCursor());

        // Set value
        windowConfiguration.setHideCursor(true);
        REQUIRE(windowConfiguration.hideCursor());
    }

}