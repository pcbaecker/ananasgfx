#include "../Catch.hpp"
#include <ananasgfx/gfx/Window.hpp>

TEST_CASE("gfx::Window") {

    SECTION("std::shared_ptr<Window> create(const WindowConfiguration&) noexcept") {
        auto pWindow = gfx::Window::create(gfx::WindowConfiguration());
        REQUIRE(pWindow.use_count() > 0);
    }

    gfx::WindowConfiguration conf;
    conf.setWidth(123);
    auto pWindow = gfx::Window::create(conf);

    SECTION("const WindowConfiguration& getConfiguration() const noexcept") {
        REQUIRE(123 == pWindow->getConfiguration().getWidth());
    }

    SECTION("void addRootNode(std::shared_ptr<Node> rootNode) noexcept") {
        REQUIRE_FALSE(pWindow->getRootNode().has_value());
        auto scene = std::make_shared<gfx::Node>();
        pWindow->addRootNode(scene);
        auto opt = pWindow->getRootNode();
        REQUIRE(opt.has_value());
        REQUIRE(scene->getWindow() == pWindow.get());
    }

    SECTION("Renderer* getRenderer() noexcept") {
        // Can not correctly be tested without an OpenGL context
        REQUIRE(nullptr == pWindow->getRenderer());
    }

    SECTION("void tick(float) noexcept") {
        pWindow->tick(0.0f);
    }

    SECTION("TextureManager& getTextureManager() noexcept") {
        REQUIRE_FALSE(pWindow->getTextureManager().get("some").has_value());
    }

    SECTION("unsigned int getWidth() const noexcept") {
        REQUIRE(1 == pWindow->getWidth());
    }

    SECTION("unsigned int getHeight() const noexcept") {
        REQUIRE(1 == pWindow->getHeight());
    }

    SECTION("const Camera& getCamera() const noexcept") {
        REQUIRE(INFINITY != pWindow->getCamera().getViewProjectionMatrix()[0][0]);
    }

    SECTION("const glm::mat4& getProjection2dMatrix() const noexcept") {
        REQUIRE(INFINITY != pWindow->getProjection2dMatrix()[0][0]);
    }

    SECTION("void setTemporaryProjection2dMatrix(const glm::mat4&) noexcept") {
        glm::mat4 tmp;
        tmp[0][0] = 33.33f;
        pWindow->setTemporaryProjection2dMatrix(tmp);
        REQUIRE(Approx(33.33f) == pWindow->getProjection2dMatrix()[0][0]);
    }

    SECTION("void removeTemporaryProjection2dMatrix() noexcept") {
        glm::mat4 tmp;
        tmp[0][0] = 33.33f;
        pWindow->setTemporaryProjection2dMatrix(tmp);
        REQUIRE(Approx(33.33f) == pWindow->getProjection2dMatrix()[0][0]);
        pWindow->removeTemporaryProjection2dMatrix();
        REQUIRE(Approx(33.33f) != pWindow->getProjection2dMatrix()[0][0]);
    }

    SECTION("std::optional<gfx::Node*> getRootNode() const noexcept") {
        REQUIRE_FALSE(pWindow->getRootNode().has_value());
        auto scene = std::make_shared<gfx::Node>();
        pWindow->addRootNode(scene);
        auto opt = pWindow->getRootNode();
        REQUIRE(opt.has_value());
        REQUIRE(scene->getWindow() == pWindow.get());
    }

    SECTION("font::FontManager& getFontManager() noexcept") {
        REQUIRE(pWindow->getFontManager().getFontFache().empty());
    }

    SECTION("const FileManager& getFileManager() const") {
        REQUIRE_THROWS_AS(pWindow->getFileManager(), gfx::WindowException);
    }

    SECTION("float getVerticalDpi() const noexcept") {
        REQUIRE(0 == pWindow->getVerticalDpi());
    }

    SECTION("float getHorizontalDpi() const noexcept") {
        REQUIRE(0 == pWindow->getHorizontalDpi());
    }

    SECTION("Application* getApplication() const noexcept") {
        // TODO
    }

}