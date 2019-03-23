#include <ananasgfx/ui/design/material/ButtonRed.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>
#include <ananasgfx/d2/Label.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>
#include <ee/Log.hpp>

namespace ui::design::material {

    std::optional<d2::Node *> ButtonRed::getBackgroundBlur() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.957f, 0.263f, 0.212f, 1.0f));
        return bg;
    }

    std::optional<d2::Node *> ButtonRed::getBackgroundFocus() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.937f, 0.604f, 0.604f, 1.0f));
        return bg;
    }

    d2::Label *ButtonRed::getLabel() noexcept {
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