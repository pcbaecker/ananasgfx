#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Circle.hpp>

class TestCircleScene : public gfx::Scene {
public:
    bool init() noexcept override {

        // Create a circle that is in the middle of the screen
        auto circle = createChild<d2::Circle>();
        circle->setId("CenterCircle");
        circle->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        circle->setAnchorPoint(0.5f, 0.5f);
        circle->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        circle->setSize(128, 128);
        circle->setColor(glm::vec4(0.33f, 0.9f, 0.01f, 1.0f));

        return gfx::Scene::init();
    }
};

class TestCircleApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);
        windowConfiguration.setTitle("My first window");
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestCircleScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("d2::Circle", TestCircleApplication);

APPLICATION_TEST("d2::Circle") {
public:
    void run() noexcept override {

        Compare("window.scene", "fixtures/d2/circle/first.png");

        Control<d2::Circle>("window.scene.CenterCircle", [](gfx::Application *app, d2::Circle *circle) {
            circle->setPosition(0, 0);
        });

        Compare("window.scene", "fixtures/d2/circle/second.png");
    }
};