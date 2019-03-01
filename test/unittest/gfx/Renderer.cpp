#include "../Catch.hpp"
#include <ananasgfx/gfx/Renderer.hpp>

TEST_CASE("gfx::Renderer") {

    SECTION("std::shared_ptr<Renderer> create()") {
        // In unittest there is no renderer available
        REQUIRE(nullptr == gfx::Renderer::create());
    }

}