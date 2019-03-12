#ifndef UI_DESIGN_MATERIAL_BUTTONGREEN_H
#define UI_DESIGN_MATERIAL_BUTTONGREEN_H

#include <ananasgfx/ui/TextButton.hpp>

namespace ui::design::material {

    class ButtonGreen : public ui::TextButton {
    private:
        std::optional<d2::Node *> getBlurBackground() noexcept override;

        std::optional<d2::Node *> getFocusBackground() noexcept override;
    };

}

#endif