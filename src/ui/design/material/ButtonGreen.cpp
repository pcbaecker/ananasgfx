#include <ananasgfx/ui/design/material/ButtonGreen.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>
#include <ananasgfx/d2/Label.hpp>
#include <ee/Log.hpp>

namespace ui::design::material {

    std::optional<d2::Node *> ButtonGreen::getBackgroundBlur() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.298f, 0.686f, 0.314f, 1.0f));
        return bg;
    }

    std::optional<d2::Node *> ButtonGreen::getBackgroundFocus() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.647f, 0.839f, 0.655f, 1.0f));
        return bg;
    }

    d2::Label *ButtonGreen::getLabel() noexcept {
        auto label = createChild<d2::Label>();
        label->setFontSize(static_cast<font::size_t>(toVerticalPixel(16)));
        if (!label->setFont(
                MaterialDesign::getInstance().getFontFamily(),
                MaterialDesign::getInstance().getFontSubMedium())) {
            WARN("Could not set font", {
                    ee::Note("Family", MaterialDesign::getInstance().getFontFamily()),
                    ee::Note("Sub", MaterialDesign::getInstance().getFontSubMedium())
            });
        }
        label->setColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
        return label;
    }
}