#include <ananasgfx/ui/design/material/List.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

namespace ui::design::material {

    d2::Node *List::createDivider() noexcept {
        auto rect = createChild<d2::Rectangle>();
        rect->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.37f));
        return rect;
    }

    ui::densityPixel_t List::getDividerHeight() noexcept {
        return 1;
    }

}