#ifndef UI_DESIGN_MATERIAL_BUTTONFLAT_H
#define UI_DESIGN_MATERIAL_BUTTONFLAT_H

#include <ananasgfx/ui/TextButton.hpp>

namespace ui::design::material {

    class ButtonFlat : public ui::TextButton {
    public:
        std::optional<d2::Node *> getBackgroundBlur() noexcept override;

        std::optional<d2::Node *> getBackgroundFocus() noexcept override;

        d2::Label *getLabel() noexcept override;

        densityPixel_t getOptimalHeight(densityPixel_t width) noexcept override;
    };

}

#endif