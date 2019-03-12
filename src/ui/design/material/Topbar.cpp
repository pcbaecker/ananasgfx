#include <ananasgfx/ui/design/material/Topbar.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>
#include <ananasgfx/d2/Rectangle.hpp>

namespace ui::design::material {

    Topbar::Topbar() noexcept {
        // Set fixed size
        this->setFixedSize(vec2(56,56));
    }

    bool Topbar::init() noexcept {
        // Set background
        auto bg = createChild<d2::Rectangle>();
        bg->setColor(MaterialDesign::getInstance().getPrimaryColor());
        this->setBackground(bg);

        return Container::init();
    }
}