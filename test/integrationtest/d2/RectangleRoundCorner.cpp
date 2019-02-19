#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>

class TestRectangleRoundCornerScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create a rectangleRoundCorner that is in the middle of the screen
        auto rect = createChild<d2::RectangleRoundCorner>();
        rect->setId("rrc");
        rect->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        rect->setAnchorPoint(0.5f, 0.5f);
        rect->setSize(64, 64);
        rect->setRadius(8.0f);

        return gfx::Scene::init();
    }
};

class TestRectangleRoundCornerApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(256);
        windowConfiguration.setHeight(256);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestRectangleRoundCornerScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("d2::RectangleRoundCorner", TestRectangleRoundCornerApplication);

class TestRectangleRoundCornerApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {

        Compare("window.scene", "fixtures/d2/rectangleRoundCorner/first.png");

        Control<d2::RectangleRoundCorner>("window.scene.rrc", [](gfx::Application *app, d2::RectangleRoundCorner *rect) {
            rect->setPosition(20.0f, 20.0f);
            rect->setAnchorPoint(0.0f, 0.0f);
            rect->setSize(200, 200);
        });

        Compare("window.scene", "fixtures/d2/rectangleRoundCorner/second.png");
    }
};

REGISTER_APPLICATIONTEST("d2::RectangleRoundCorner", TestRectangleRoundCornerApplicationTest);