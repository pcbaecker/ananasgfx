#include "../Catch.hpp"
#include <ananasgfx/gfx/TextureManager.hpp>

TEST_CASE("gfx::TextureManager") {

    // Correct behaviour can not be tested without a working OpenGL context
    gfx::TextureManager textureManager;

    SECTION("std::optional<Texture*> get(const std::string&) noexcept") {
        REQUIRE_FALSE(textureManager.get("unknown_file.png").has_value());
    }

}