#include <ananasgfx/d2/Label.hpp>
#include "../Catch.hpp"

TEST_CASE("d2::Label") {

    d2::Label label;

    SECTION("bool init() noexcept") {
        // Because we do not provide a filename or a texture the labels init fails
        // We cannot provide that because we have no OpenGL context
        REQUIRE_FALSE(label.init());
    }

    SECTION("void setText(std::string) noexcept") {
        label.setText("mytext123");
        REQUIRE("mytext123" == label.getText());
    }

    SECTION("const std::string& getText() const noexcept") {
        label.setText("mytext123");
        REQUIRE("mytext123" == label.getText());
    }

    SECTION("void setHorizontalAlign(gfx::HorizontalAlign) noexcept") {
        label.setHorizontalAlign(gfx::HorizontalAlign::Right);
        REQUIRE(label.getHorizontalAlign() == gfx::HorizontalAlign::Right);
        label.setHorizontalAlign(gfx::HorizontalAlign::Left);
        REQUIRE(label.getHorizontalAlign() == gfx::HorizontalAlign::Left);
    }

    SECTION("gfx::HorizontalAlign getHorizontalAlign() const noexcept") {
        label.setHorizontalAlign(gfx::HorizontalAlign::Right);
        REQUIRE(label.getHorizontalAlign() == gfx::HorizontalAlign::Right);
        label.setHorizontalAlign(gfx::HorizontalAlign::Left);
        REQUIRE(label.getHorizontalAlign() == gfx::HorizontalAlign::Left);
    }

    SECTION("void setVerticalAlign(gfx::VerticalAlign align) noexcept") {
        label.setVerticalAlign(gfx::VerticalAlign::Top);
        REQUIRE(label.getVerticalAlign() == gfx::VerticalAlign::Top);
        label.setVerticalAlign(gfx::VerticalAlign::Bottom);
        REQUIRE(label.getVerticalAlign() == gfx::VerticalAlign::Bottom);
    }

    SECTION("gfx::VerticalAlign getVerticalAlign() const noexcept") {
        label.setVerticalAlign(gfx::VerticalAlign::Top);
        REQUIRE(label.getVerticalAlign() == gfx::VerticalAlign::Top);
        label.setVerticalAlign(gfx::VerticalAlign::Bottom);
        REQUIRE(label.getVerticalAlign() == gfx::VerticalAlign::Bottom);
    }

    SECTION("bool setFont(const std::string&, const std::string&) noexcept") {
        // We cannot test this method, because a full window context is required to handle font finding
    }

    SECTION("font::Font* getFont() const noexcept") {
        // Without a full window context we can not test this method correctly
        REQUIRE(label.getFont() == nullptr);
    }

    SECTION("void setSize(float, float) noexcept") {
        label.setSize(125.0f, 267.0f);
        REQUIRE(label.getSize().x == Approx(125.0f));
        REQUIRE(label.getSize().y == Approx(267.0f));
    }
}