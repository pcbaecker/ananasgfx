#include "../Catch.hpp"
#include <ananasgfx/gfx/Camera.hpp>
#include <ananasgfx/gfx/WindowConfiguration.hpp>
#include <ananasgfx/gfx/Window.hpp>

TEST_CASE("gfx::Camera") {

    gfx::Camera camera;

    SECTION("void updateWindow(Window*) noexcept") {
        auto window = gfx::Window::create(gfx::WindowConfiguration());
        camera.updateWindow(window.get());
    }

    SECTION("const glm::mat4& getViewProjectionMatrix() const noexcept") {
        REQUIRE(camera.getViewProjectionMatrix().length() > 0);
    }

}