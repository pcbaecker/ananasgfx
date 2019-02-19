#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Ring.hpp>

class TestRingScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create a ring that is in the middle of the screen
        auto rect = createChild<d2::Ring>();
        rect->setId("ring");
        rect->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        rect->setAnchorPoint(0.5f, 0.5f);
        rect->setSize(64, 64);

        return gfx::Scene::init();
    }
};

class TestRingApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(256);
        windowConfiguration.setHeight(256);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestRingScene>());
        registerWindow(window);

        return true;
    }

};

REGISTER_APPLICATION("d2::Ring", TestRingApplication);

class TestRingApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {

        Compare("window.scene", "fixtures/d2/ring/first.png");

        Control<d2::Ring>("window.scene.ring", [](gfx::Application *app, d2::Ring *ring) {
            ring->setPosition(20.0f, 20.0f);
            ring->setAnchorPoint(0.0f, 0.0f);
            ring->setSize(200, 200);
        });

        Compare("window.scene", "fixtures/d2/ring/second.png");
    }
};

REGISTER_APPLICATIONTEST("d2::Ring", TestRingApplicationTest);