#ifndef UI_LISTITEM_H
#define UI_LISTITEM_H

#include "Touchable.hpp"
#include "Container.hpp"

namespace ui {

class ListItem : public Touchable, public ui::Container {
    public:
        bool init() noexcept override;

        virtual densityPixel_t getHeight() noexcept = 0;

    void onTouchBegan(float x, float y, const gfx::Touch &touch) noexcept override;

    void onTouchEnded(float x, float y, const gfx::Touch &touch) noexcept override;

    };
}

#endif