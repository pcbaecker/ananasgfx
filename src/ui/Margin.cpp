#include <ananasgfx/ui/Margin.hpp>

namespace ui {

    densityPixel_t Margin::getTop() const noexcept {
        return this->mTop;
    }

    densityPixel_t Margin::getBottom() const noexcept {
        return this->mBottom;
    }

    densityPixel_t Margin::getLeft() const noexcept {
        return this->mLeft;
    }

    densityPixel_t Margin::getRight() const noexcept {
        return this->mRight;
    }

    void Margin::set(densityPixel_t top, densityPixel_t bottom, densityPixel_t left, densityPixel_t right) noexcept {
        setTop(top);
        setBottom(bottom);
        setLeft(left);
        setRight(right);
    }

    void Margin::setTop(densityPixel_t top) noexcept {
        this->mTop = top;
    }

    void Margin::setBottom(densityPixel_t bottom) noexcept {
        this->mBottom = bottom;
    }

    void Margin::setLeft(densityPixel_t left) noexcept {
        this->mLeft = left;
    }

    void Margin::setRight(densityPixel_t right) noexcept {
        this->mRight = right;
    }

    densityPixel_t Margin::getHorizontal() const noexcept {
        return this->mLeft + this->mRight;
    }

    densityPixel_t Margin::getVertical() const noexcept {
        return this->mTop + this->mBottom;
    }

}