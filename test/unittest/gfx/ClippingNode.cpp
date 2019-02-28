#include "../Catch.hpp"
#include <ananasgfx/gfx/ClippingNode.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

TEST_CASE("gfx::ClippingNode") {

    gfx::ClippingNode clippingNode;

    SECTION("template<class T> T* createStencil() noexcept") {
        auto rect = clippingNode.createStencil<d2::Rectangle>();
        REQUIRE(rect->getParent() == &clippingNode);
    }

    SECTION("bool init() noexcept") {
        // No stenctils or children registered thats why it works without a context
        REQUIRE(clippingNode.init());
    }

    SECTION("void draw() noexcept") {
        // We need an active OpenGL context to draw()
    }

}
