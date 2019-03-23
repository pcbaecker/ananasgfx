#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/d2/Label.hpp>

class LabelsScene : public gfx::Node {
public:
    bool init() noexcept override {
        this->pLabel = createChild<d2::Label>();
        this->pLabel->setSize(static_cast<float>(this->pWindow->getWidth()), static_cast<float>(this->pWindow->getHeight()));
        if (!this->pLabel->setFont("Roboto", "Medium")) {
            WARN("Could not init font", {
                ee::Note("Family", "Roboto"),
                ee::Note("Sub", "Medium")
            });
            return false;
        }

        state();
        return gfx::Node::init();
    }

    void update(float dt) noexcept override {
        Node::update(dt);

        this->mTimer += dt;
        if (this->mTimer >= 1.0f) {
            this->mTimer = 0.0f;
            this->mState++;
            state();
        }
    }

    void state() noexcept {
        switch (this->mState) {
            default:
                this->mState = 0;
            case 0:
                this->pLabel->setText("Top - Left");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Left);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Top);
                break;
            case 1:
                this->pLabel->setText("Top - Center");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Center);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Top);
                break;
            case 2:
                this->pLabel->setText("Top - Right");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Right);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Top);
                break;
            case 3:
                this->pLabel->setText("Middle - Left");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Left);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Middle);
                break;
            case 4:
                this->pLabel->setText("Middle - Center");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Center);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Middle);
                break;
            case 5:
                this->pLabel->setText("Middle - Right");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Right);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Middle);
                break;
            case 6:
                this->pLabel->setText("Bottom - Left");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Left);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Bottom);
                break;
            case 7:
                this->pLabel->setText("Bottom - Center");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Center);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Bottom);
                break;
            case 8:
                this->pLabel->setText("Bottom - Right");
                this->pLabel->setFontSize(24);
                this->pLabel->setMultiline(false);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Right);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Bottom);
                break;
            case 9:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Left);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Top);
                this->pLabel->setText(LoremIpsum);
                break;
            case 10:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Center);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Top);
                this->pLabel->setText(LoremIpsum);
                break;
            case 11:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Right);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Top);
                this->pLabel->setText(LoremIpsum);
                break;
            case 12:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Left);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Middle);
                this->pLabel->setText(LoremIpsum);
                break;
            case 13:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Center);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Middle);
                this->pLabel->setText(LoremIpsum);
                break;
            case 14:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Right);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Middle);
                this->pLabel->setText(LoremIpsum);
                break;
            case 15:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Left);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Bottom);
                this->pLabel->setText(LoremIpsum);
                break;
            case 16:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Center);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Bottom);
                this->pLabel->setText(LoremIpsum);
                break;
            case 17:
                this->pLabel->setMultiline(true);
                this->pLabel->setFontSize(24);
                this->pLabel->setHorizontalAlign(gfx::HorizontalAlign::Right);
                this->pLabel->setVerticalAlign(gfx::VerticalAlign::Bottom);
                this->pLabel->setText(LoremIpsum);
                break;
        }
    }

private:
    d2::Label* pLabel = nullptr;
    float mTimer = 0.0f;
    uint8_t mState = 0;
    const std::string LoremIpsum = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";
};

class LabelsApp : public gfx::Application {
public:
    bool init() noexcept override {
        // Create window Configuration
        gfx::WindowConfiguration windowConfiguration;
        windowConfiguration.setWidth(640);
        windowConfiguration.setHeight(480);

        // Create window one
        windowConfiguration.setTitle("Label examples");
        auto windowOne = gfx::Window::create(windowConfiguration);
        windowOne->addRootNode(std::make_shared<LabelsScene>());
        registerWindow(windowOne);

        if (!windowOne->getFontManager().registerFont(getFileManager().getResource("Roboto-Medium.ttf"), "Roboto", "Medium")) {
            ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Could not load font", {
                    ee::Note("Filename", "Roboto-Medium.ttf")
            });
            return false;
        }

        return true;
    }
};
REGISTER_APPLICATION("LabelsApp", LabelsApp);