#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Circle.hpp>

class TestCircleScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create a circle that is in the middle of the screen
        auto circle = createChild<d2::Circle>();
        circle->setId("circle");
        circle->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        circle->setAnchorPoint(0.5f, 0.5f);
        circle->setSize(64, 64);

        return gfx::Scene::init();
    }
};

class TestCircleApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(256);
        windowConfiguration.setHeight(256);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestCircleScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("d2::Circle", TestCircleApplication);

class TestCircleApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {

        Compare("window.scene", "fixtures/d2/circle/first.png");

        Control<d2::Circle>("window.scene.circle", [](gfx::Application *app, d2::Circle *circle) {
            circle->setPosition(0.0f, 0.0f);
            circle->setAnchorPoint(0.0f, 0.0f);
            circle->setSize(256, 256);
        });

        Compare("window.scene", "fixtures/d2/circle/second.png");
    }
};

REGISTER_APPLICATIONTEST("d2::Circle", TestCircleApplicationTest);