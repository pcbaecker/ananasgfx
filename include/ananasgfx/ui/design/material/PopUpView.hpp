#ifndef UI_DESIGN_MATERIAL_POPUPVIEW_H
#define UI_DESIGN_MATERIAL_POPUPVIEW_H

#include <ananasgfx/ui/PopUpView.hpp>

namespace ui::design::material {

class PopUpView : public ui::PopUpView {
public:
    PopUpView() noexcept;

    bool init() noexcept override;
};

}

#endif