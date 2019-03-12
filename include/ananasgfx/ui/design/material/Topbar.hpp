#ifndef UI_DESIGN_MATERIAL_H
#define UI_DESIGN_MATERIAL_H

#include <ananasgfx/ui/Container.hpp>

namespace ui::design::material {

class Topbar : public ui::Container {
public:
    Topbar() noexcept;
    bool init() noexcept override;
};

}

#endif