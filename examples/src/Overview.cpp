#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/gfx/internal/ApplicationManager.hpp>
#include <ananasgfx/d2/Rectangle.hpp>
#include <ananasgfx/ui/List.hpp>
#include <ananasgfx/ui/Label.hpp>
#include <ee/Log.hpp>
#include <ananasgfx/ui/design/material/ButtonGreen.hpp>
#include <ananasgfx/ui/design/material/List.hpp>
#include <ananasgfx/ui/layout/HorizontalLinear.hpp>
#include <ananasgfx/ui/Scrollable.hpp>
#include <ananasgfx/ui/layout/VerticalLinear.hpp>
#include <ananasgfx/ui/design/material/Topbar.hpp>
#include <ananasgfx/ui/design/material/ListItemSimpleText.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>

class OverviewScene : public ui::Container {
public:
    bool init() noexcept override {
        // Set background color
        this->pWindow->getRenderer()->setClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Set the layout
        createLayout<ui::layout::VerticalLinear>();

        // Create topbar
        auto topbar = createChild<ui::design::material::Topbar>();
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

        // Create the list
        auto list = createChild<ui::design::material::List>();

        // Rendertexture
        auto liRendertexture = list->createListItem<ui::design::material::ListItemSimpleText>();
        liRendertexture->setText("Rendertexture");
        liRendertexture->setCallback([this](){
            this->pWindow->getApplication()->getApplicationManager()->setNextApplication("Rendertexture");
            this->pWindow->getApplication()->gracefulClose();
        });

        // Primitives 3d
        auto liPrimitives3d = list->createListItem<ui::design::material::ListItemSimpleText>();
        liPrimitives3d->setText("Primitives 3d");
        liPrimitives3d->setCallback([this](){
            this->pWindow->getApplication()->getApplicationManager()->setNextApplication("Primitives3d");
            this->pWindow->getApplication()->gracefulClose();
        });

        // Primitives 2d
        auto liPrimitives2d = list->createListItem<ui::design::material::ListItemSimpleText>();
        liPrimitives2d->setText("Primitives 2d");
        liPrimitives2d->setCallback([this](){
            this->pWindow->getApplication()->getApplicationManager()->setNextApplication("Primitives2d");
            this->pWindow->getApplication()->gracefulClose();
        });

        // MaterialDesignApp
        auto liMaterialDesign = list->createListItem<ui::design::material::ListItemSimpleText>();
        liMaterialDesign->setText("Material design");
        liMaterialDesign->setCallback([this](){
            this->pWindow->getApplication()->getApplicationManager()->setNextApplication("MaterialDesign");
            this->pWindow->getApplication()->gracefulClose();
        });

#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
        // Multiwindow
        auto liMultiwindow = list->createListItem<ui::design::material::ListItemSimpleText>();
        liMultiwindow->setText("Multiple windows");
        liMultiwindow->setCallback([this](){
            this->pWindow->getApplication()->getApplicationManager()->setNextApplication("MultiWindowApp");
            this->pWindow->getApplication()->gracefulClose();
        });
#endif

        return ui::Container::init();
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
        window->addRootNode(std::make_shared<OverviewScene>());
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