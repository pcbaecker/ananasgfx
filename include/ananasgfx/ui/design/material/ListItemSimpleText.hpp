#ifndef UI_DESIGN_MATERIAL_LISTITEMSIMPLETEXT_H
#define UI_DESIGN_MATERIAL_LISTITEMSIMPLETEXT_H

#include <ananasgfx/ui/ListItem.hpp>
#include <ananasgfx/ui/Label.hpp>

namespace ui::design::material {

    class ListItemSimpleText : public ui::ListItem {
    public:
        bool init() noexcept override;
        densityPixel_t getHeight() noexcept override;
        std::optional<d2::Node*> getBackgroundBlur() noexcept override;
        std::optional<d2::Node*> getBackgroundFocus() noexcept override;

        void setText(std::string text) noexcept;

    private:
        std::string mText;
        ui::Label* pLabel = nullptr;
    };

}

#endif