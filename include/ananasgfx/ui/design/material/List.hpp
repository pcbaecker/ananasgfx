#ifndef UI_DESIGN_MATERIAL_LIST_H
#define UI_DESIGN_MATERIAL_LIST_H

#include <ananasgfx/ui/List.hpp>

namespace ui::design::material {

class List : public ui::List {
public:
    d2::Node* createDivider() noexcept override;
    ui::densityPixel_t getDividerHeight() noexcept override;
};

}

#endif