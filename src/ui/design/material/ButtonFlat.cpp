#include <ananasgfx/ui/design/material/ButtonFlat.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>
#include <ananasgfx/d2/Label.hpp>

namespace ui::design::material {

    std::optional<d2::Node *> ButtonFlat::getBackgroundBlur() noexcept {
        return {};
    }

    std::optional<d2::Node *> ButtonFlat::getBackgroundFocus() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(MaterialDesign::getInstance().getPrimaryColor());
        return bg;
    }

    d2::Label *ButtonFlat::getLabel() noexcept {
        auto label = createChild<d2::Label>();
        label->setFontSize(static_cast<font::size_t>(toVerticalPixel(15)));
        if (!label->setFont(
                MaterialDesign::getInstance().getFontFamily(),
                MaterialDesign::getInstance().getFontSubBold())) {
            WARN("Could not set font", {
                ee::Note("Family", MaterialDesign::getInstance().getFontFamily()),
                ee::Note("Sub", MaterialDesign::getInstance().getFontSubBold())
            });
        }
        label->setColor(MaterialDesign::getInstance().getPrimaryColor());
        return label;
    }

    densityPixel_t ButtonFlat::getOptimalHeight(densityPixel_t width) noexcept {
        return 52;
    }

}