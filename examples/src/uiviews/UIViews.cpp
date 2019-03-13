#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/ui/Button.hpp>
#include <ananasgfx/ui/Label.hpp>
#include <ananasgfx/d2/Rectangle.hpp>
#include <ananasgfx/ui/design/material/ButtonGreen.hpp>
#include <ee/Log.hpp>

class UIViewsScene : public gfx::Node {
public:
    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);
/*
        auto layout = this->createChild<ui::VerticalLinearLayout>();
        layout->setSize(this->pWindow->getWidth(), this->pWindow->getHeight());
        auto bg = layout->createChild<d2::Rectangle>();
        bg->setColor(glm::vec4(0.5f, 0.1f, 0.0f, 1.0f));
        layout->setBackground(bg);

        auto buttonOne = layout->createChild<ui::design::material::ButtonGreen>();
        //buttonOne->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        buttonOne->setMaxSize(ui::vec2{16,16});
        buttonOne->getMargin().setLeft(16);
        buttonOne->getMargin().setTop(16);
        buttonOne->getMargin().setRight(16);
        buttonOne->getMargin().setBottom(16);

        auto buttonTwo = layout->createChild<ui::Label>();
        if (!buttonTwo->setFont("Roboto", "Bold")) {
                std::cerr << "NO FOND" << std::endl;
        }
        buttonTwo->setText("test213");
        //buttonTwo->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        //buttonTwo->setMaxSize(ui::vec2{16,16});
        buttonTwo->getMargin().setRight(32);
        buttonTwo->getMargin().setLeft(32);

        auto buttonThree = layout->createChild<ui::design::material::ButtonGreen>();
        //buttonThree->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        buttonThree->setMaxSize(ui::vec2{16,16});
        buttonThree->getMargin().setRight(32);
*/
        return gfx::Node::init();
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
        window->addRootNode(std::make_shared<UIViewsScene>());
        registerWindow(window);

            if (!window->getFontManager().registerFont(getFileManager().getResource("Roboto-Bold.ttf"), "Roboto", "Bold")) {
                    ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not load font", {
                            ee::Note("Filename", "Roboto-Bold.ttf")
                    });
                    return false;
            }

        return true;
    }
};

REGISTER_APPLICATION("UIViews", UIViewsApp);
