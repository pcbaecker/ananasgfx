#include <ananasgfx/ui/design/material/PopUpView.hpp>
#include <ananasgfx/d2/RectangleRoundCorner.hpp>

namespace ui::design::material {

    PopUpView::PopUpView() noexcept {
            this->setMinSize(vec2(320.0f, 8.0f));
            this->getMargin().set(16,16,16,16);
    }

    bool PopUpView::init() noexcept {
        auto bg = createChild<d2::RectangleRoundCorner>();
        bg->setRadius(toVerticalPixel(3));
        bg->setColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));
        this->setBackground(bg);

        return ui::PopUpView::init();
    }

}