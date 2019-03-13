#ifndef UI_MARGIN_H
#define UI_MARGIN_H

#include "Defines.hpp"

namespace ui {

    class Margin {
    public:

        densityPixel_t getTop() const noexcept;
        densityPixel_t getBottom() const noexcept;
        densityPixel_t getLeft() const noexcept;
        densityPixel_t getRight() const noexcept;

        void set(densityPixel_t top, densityPixel_t bottom, densityPixel_t left, densityPixel_t right) noexcept;
        void setTop(densityPixel_t top) noexcept;
        void setBottom(densityPixel_t bottom) noexcept;
        void setLeft(densityPixel_t left) noexcept;
        void setRight(densityPixel_t right) noexcept;

        densityPixel_t getHorizontal() const noexcept;
        densityPixel_t getVertical() const noexcept;

    private:
        densityPixel_t mTop = 0;
        densityPixel_t mBottom = 0;
        densityPixel_t mLeft = 0;
        densityPixel_t mRight = 0;
    };

}

#endif