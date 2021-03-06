#ifndef UI_DESIGN_MATERIAL_BUTTONBLUE_H
#define UI_DESIGN_MATERIAL_BUTTONBLUE_H

#include <ananasgfx/ui/TextButton.hpp>

namespace ui::design::material {

class ButtonBlue : public ui::TextButton {
public:
    std::optional<d2::Node *> getBackgroundBlur() noexcept override;

    std::optional<d2::Node *> getBackgroundFocus() noexcept override;

    d2::Label* getLabel() noexcept override;
};

}

#endif