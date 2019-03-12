#include <ananasgfx/ui/design/material/ButtonGreen.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>

namespace ui::design::material {

    std::optional<d2::Node *> ButtonGreen::getBlurBackground() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.298f, 0.686f, 0.314f, 1.0f));
        return bg;
    }

    std::optional<d2::Node *> ButtonGreen::getFocusBackground() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.647f, 0.839f, 0.655f, 1.0f));
        return bg;
    }
}