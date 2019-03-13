#include <ananasgfx/ui/design/material/ButtonBlue.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>

namespace ui::design::material {

    std::optional<d2::Node *> ButtonBlue::getBlurBackground() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.129f, 0.588f, 0.953f, 1.0f));
        return bg;
    }

    std::optional<d2::Node *> ButtonBlue::getFocusBackground() noexcept {
        auto bg = this->createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toHorizontalPixel(3));
        bg->setColor(glm::vec4(0.565f, 0.792f, 0.976f, 1.0f));
        return bg;
    }

}