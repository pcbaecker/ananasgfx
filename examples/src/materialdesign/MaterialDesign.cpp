#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/gfx/Window.hpp>
#include <ananasgfx/font/FontManager.hpp>
#include <ananasgfx/ui/Label.hpp>
#include <ananasgfx/ui/layout/VerticalLinear.hpp>
#include <ananasgfx/ui/design/material/Topbar.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>
#include <ananasgfx/ui/design/material/ButtonGreen.hpp>
#include <ananasgfx/ui/design/material/ButtonBlue.hpp>
#include <ananasgfx/ui/design/material/ButtonRed.hpp>
#include <ananasgfx/ui/design/material/PopUpView.hpp>
#include <ee/Log.hpp>
#include <ananasgfx/ui/design/material/PopUpViewSimpleDialog.hpp>

class MaterialDesignScene : public ui::Container {
public:
    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Set layout
        createLayout<ui::layout::VerticalLinear>();

        // Set Topbar
        auto topbar = createChild<ui::design::material::Topbar>();
        auto topbarlabel = topbar->createChild<ui::Label>();
        topbarlabel->setColor(glm::vec4(1,1,1,1));
        topbarlabel->setFontSize(20);
        topbarlabel->setText("Material Design");
        if (!topbarlabel->setFont(
                ui::design::material::MaterialDesign::getInstance().getFontFamily(),
                ui::design::material::MaterialDesign::getInstance().getFontSubMedium())) {
            WARN("Could not set font", {
                ee::Note("FontFamily", ui::design::material::MaterialDesign::getInstance().getFontFamily()),
                ee::Note("FontSub", ui::design::material::MaterialDesign::getInstance().getFontSubMedium())
            });
            return false;
        }

        // Green button
        auto btnGreen = createChild<ui::design::material::ButtonGreen>();
        btnGreen->setText("The green button");
        btnGreen->getMargin().set(16,8,16,16);

        // Blue button
        auto btnBlue = createChild<ui::design::material::ButtonBlue>();
        btnBlue->setText("The blue button");
        btnBlue->getMargin().set(8,8,16,16);

        // Red button
        auto btnRed = createChild<ui::design::material::ButtonRed>();
        btnRed->setText("The red button");
        btnRed->getMargin().set(8,8,16,16);
        btnRed->setCallback([this]() {
            auto dialog = this->createChildLazy<ui::design::material::PopUpViewSimpleDialog>();
            dialog.get()->setTitle("This is my title");
            dialog.get()->setButtonLeft("Cancel");
            dialog.get()->setButtonRight("Agree");
            dialog.get()->setOutsideTouchCallback([](ui::PopUpView*popUpView) {
                popUpView->removeFromParent();
            });
        });

        return ui::Container::init();
    }

private:

};

class MaterialDesignApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);
        windowConfiguration.setTitle("Material design");
        auto window = gfx::Window::create(windowConfiguration);
        window->addRootNode(std::make_shared<MaterialDesignScene>());
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
REGISTER_APPLICATION("MaterialDesign", MaterialDesignApp);
