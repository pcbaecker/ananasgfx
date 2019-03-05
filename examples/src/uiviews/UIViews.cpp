#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/gfx/Scene.hpp>
#include <ananasgfx/ui/View.hpp>
#include <ananasgfx/ui/Button.hpp>

class UIViewsScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        auto layout = this->createChild<ui::LinearLayout>();
        layout->setSize(this->pWindow->getWidth(), this->pWindow->getHeight());

        auto buttonOne = layout->createChild<ui::Button>();
        buttonOne->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        buttonOne->setMaxSize(ui::vec2{16,16});
        buttonOne->getMargin().setLeft(16);
        buttonOne->getMargin().setTop(16);
        buttonOne->getMargin().setRight(16);
        buttonOne->getMargin().setBottom(16);

        auto buttonTwo = layout->createChild<ui::Button>();
        buttonTwo->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        //buttonTwo->setMaxSize(ui::vec2{16,16});
        buttonTwo->getMargin().setBottom(32);

        auto buttonThree = layout->createChild<ui::Button>();
        buttonThree->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        buttonThree->setMaxSize(ui::vec2{16,16});
        buttonThree->getMargin().setRight(32);

        return gfx::Scene::init();
    }
};

class UIViewsApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);
        windowConfiguration.setTitle("UIViews example");
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<UIViewsScene>());
        registerWindow(window);

        return true;
    }
};

REGISTER_APPLICATION("UIViews", UIViewsApp);
