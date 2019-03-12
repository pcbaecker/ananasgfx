#ifndef UI_LAYOUT_LAYOUT_H
#define UI_LAYOUT_LAYOUT_H

namespace ui {
    class Container;
}

namespace ui::layout {

    class Layout {
    public:
        virtual ~Layout() noexcept {}
        virtual bool arrangeChildren(ui::Container* container) noexcept = 0;

    };

}

#endif