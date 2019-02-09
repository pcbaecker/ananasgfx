#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/d2/Label.hpp>
#include <ee/Log.hpp>

class TestLabelScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Create a label that is in the middle of the screen
        auto label = createChild<d2::Label>();
        label->setId("label");
        label->setPosition(this->getWindow()->getWidth() * 0.5f, this->getWindow()->getHeight() * 0.5f);
        label->setAnchorPoint(0.5f, 0.5f);
        label->setSize(256, 256);
        label->setText("Lörem ipsüm dolir");
        label->setFont("Roboto", "Bold");
        label->setVerticalAlign(gfx::VerticalAlign::Top);
        label->setHorizontalAlign(gfx::HorizontalAlign::Left);
        label->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        return gfx::Scene::init();
    }
};

class TestLabelApplication : public gfx::Application {

    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(256);
        windowConfiguration.setHeight(256);
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<TestLabelScene>());
        registerWindow(window);
        if (!window->getFontManager().registerFont("fixtures/d2/label/Roboto-Bold.ttf", "Roboto", "Bold")) {
                ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not register font", {});
                return false;
        }

        return true;
    }

};

REGISTER_APPLICATION("d2::Label", TestLabelApplication);

class TestLabelApplicationTest : public test::ApplicationTest {
public:
    void run() noexcept override {
            // TOP-LEFT
        Compare("window.scene", "fixtures/d2/label/top-left.png");

            // TOP-CENTER
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setHorizontalAlign(gfx::HorizontalAlign::Center);
            });
            Compare("window.scene", "fixtures/d2/label/top-center.png");

            // TOP-RIGHT
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setHorizontalAlign(gfx::HorizontalAlign::Right);
            });
            Compare("window.scene", "fixtures/d2/label/top-right.png");

            // MIDDLE-LEFT
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setVerticalAlign(gfx::VerticalAlign::Middle);
                label->setHorizontalAlign(gfx::HorizontalAlign::Left);
            });
            Compare("window.scene", "fixtures/d2/label/middle-left.png");

            // MIDDLE-CENTER
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setHorizontalAlign(gfx::HorizontalAlign::Center);
            });
            Compare("window.scene", "fixtures/d2/label/middle-center.png");

            // MIDDLE-RIGHT
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setHorizontalAlign(gfx::HorizontalAlign::Right);
            });
            Compare("window.scene", "fixtures/d2/label/middle-right.png");

            // BOTTOM-LEFT
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setVerticalAlign(gfx::VerticalAlign::Bottom);
                label->setHorizontalAlign(gfx::HorizontalAlign::Left);
            });
            Compare("window.scene", "fixtures/d2/label/bottom-left.png");

            // BOTTOM-CENTER
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setHorizontalAlign(gfx::HorizontalAlign::Center);
            });
            Compare("window.scene", "fixtures/d2/label/bottom-center.png");

            // BOTTOM-RIGHT
            Control<d2::Label>("window.scene.label", [](gfx::Application *app, d2::Label *label) {
                label->setHorizontalAlign(gfx::HorizontalAlign::Right);
            });
            Compare("window.scene", "fixtures/d2/label/bottom-right.png");
    }
};

REGISTER_APPLICATIONTEST("d2::Label", TestLabelApplicationTest);