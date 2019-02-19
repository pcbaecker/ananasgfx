#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

class TestRectangleScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create a rectangle that is in the middle of the screen
        auto rect = createChild<d2::Rectangle>();
        rect->setId("rect");
        rect->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        rect->setAnchorPoint(0.5f, 0.5f);
        rect->setSize(64, 64);

        return gfx::Scene::init();
    }
};

class TestRectangleApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(256);
        windowConfiguration.setHeight(256);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestRectangleScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("d2::Rectangle", TestRectangleApplication);

class TestRectangleApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {

        Compare("window.scene", "fixtures/d2/rectangle/first.png");

        Control<d2::Rectangle>("window.scene.rect", [](gfx::Application *app, d2::Rectangle *rect) {
            rect->setPosition(20.0f, 20.0f);
            rect->setAnchorPoint(0.0f, 0.0f);
            rect->setSize(200, 200);
        });

        Compare("window.scene", "fixtures/d2/rectangle/second.png");
    }
};

REGISTER_APPLICATIONTEST("d2::Rectangle", TestRectangleApplicationTest);