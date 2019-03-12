#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/gfx/Scene.hpp>
#include <ananasgfx/d2/Rectangle.hpp>
#include <ananasgfx/ui/List.hpp>
#include <ananasgfx/ui/Label.hpp>
#include <ee/Log.hpp>
#include <ananasgfx/ui/design/material/ButtonGreen.hpp>
#include <ananasgfx/ui/layout/HorizontalLinear.hpp>
#include <ananasgfx/ui/Scrollable.hpp>
#include <ananasgfx/ui/layout/VerticalLinear.hpp>
#include <ananasgfx/ui/design/material/Topbar.hpp>
#include <ananasgfx/ui/design/material/ListItemSimpleText.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>

class MyList : public ui::List {
public:

    d2::Node* createDivider() noexcept override {
        auto rect = createChild<d2::Rectangle>();
        rect->setColor(glm::vec4(0,0,1,1));
        return rect;
    }

    ui::densityPixel_t getDividerHeight() noexcept override {
        return 2;
    }
};
/*
class MyListItem : public ui::ListItem {
public:
    bool init() noexcept override {
        createLayout<ui::layout::HorizontalLinear>();

        auto label = this->createChild<ui::Label>();
        label->setText("One");
        label->setFont("Roboto", "Bold");

        auto labelTwo = this->createChild<ui::Label>();
        labelTwo->setText("Two");
        labelTwo->setFont("Roboto", "Bold");

        return ui::ListItem::init();
    }

    ui::densityPixel_t getHeight() noexcept override {
        return 48;
    }

    std::optional<d2::Node*> getBackgroundBlur() noexcept override {
        auto bg = createChild<d2::Rectangle>();
        bg->setColor(glm::vec4(0.0f, 1.0f, 0.25f, 1.0f));
        return bg;
    }

    std::optional<d2::Node*> getBackgroundFocus() noexcept override {
        auto bg = createChild<d2::Rectangle>();
        bg->setColor(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        return bg;
    }

};*/

class OverviewScene : public gfx::Scene {
public:
    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        auto layout = this->createChild<ui::Container>();
        layout->createLayout<ui::layout::VerticalLinear>();
        layout->setSize(this->pWindow->getWidth(), this->pWindow->getHeight());

        auto topbar = layout->createChild<ui::design::material::Topbar>();
        auto title = topbar->createChild<ui::Label>();
        title->setColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
        title->setText("AnanasGfx examples");
        title->setFontSize(20);
        if (!title->setFont(
                ui::design::material::MaterialDesign::getInstance().getFontFamily(),
                ui::design::material::MaterialDesign::getInstance().getFontSubMedium())) {
            WARN("Could not set title font", {
                ee::Note("FontFamily", ui::design::material::MaterialDesign::getInstance().getFontFamily()),
                ee::Note("FontSub", ui::design::material::MaterialDesign::getInstance().getFontSubMedium()),
            });
            return false;
        }

        auto list = layout->createChild<MyList>();
        for (int i = 0; i < 10; i++) {
            auto listItem = list->createListItem<ui::design::material::ListItemSimpleText>();
            listItem->setText("I am listitem number " + std::to_string(i + 1));
        }

        return gfx::Scene::init();
    }
};

class OverviewApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);
        windowConfiguration.setTitle("Overview example");
        auto window = gfx::Window::create(windowConfiguration);
        window->addScene(std::make_shared<OverviewScene>());
        registerWindow(window);

        if (!window->getFontManager().registerFont(getFileManager().getResource("Roboto-Bold.ttf"), "Roboto", "Bold")) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not load font", {
                    ee::Note("Filename", "Roboto-Bold.ttf")
            });
            return false;
        }

        if (!window->getFontManager().registerFont(getFileManager().getResource("Roboto-Medium.ttf"), "Roboto", "Medium")) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not load font", {
                    ee::Note("Filename", "Roboto-Medium.ttf")
            });
            return false;
        }

        return true;
    }
};

REGISTER_APPLICATION("overview", OverviewApp);