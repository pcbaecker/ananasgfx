#include <ananasgfx/ui/Label.hpp>

namespace ui {

    bool Label::init() noexcept {
        return Node::init();
    }

    void Label::setSize(float x, float y) noexcept {
        Node::setSize(x, y);

        this->createInlineLabel();
        this->pLabel->setSize(x,y);
    }

    void Label::setText(std::string text) noexcept {
        this->createInlineLabel();
        this->pLabel->setText(std::move(text));
    }

    bool Label::setFont(const std::string &fontFamily, const std::string &fontSubFamily) noexcept {
        this->createInlineLabel();
        return this->pLabel->setFont(fontFamily, fontSubFamily);
    }

    void Label::createInlineLabel() noexcept {
        if (this->pLabel == nullptr) {
            this->pLabel = createChild<d2::Label>();
        }
    }

    void Label::setFontSize(font::size_t fontSize) noexcept {
        this->createInlineLabel();

        // We convert the dp font size to real pixel font size
        this->pLabel->setFontSize(static_cast<font::size_t>(toVerticalPixel(fontSize)));
    }

    void Label::setColor(const glm::vec4 &color) noexcept {
        this->createInlineLabel();

        this->pLabel->setColor(color);
    }

    void Label::setMultiline(bool value) noexcept {
        this->createInlineLabel();

        this->pLabel->setMultiline(value);
    }

    void Label::setVerticalAlign(gfx::VerticalAlign verticalAlign) noexcept {
        this->createInlineLabel();

        this->pLabel->setVerticalAlign(verticalAlign);
    }

    void Label::setHorizontalAlign(gfx::HorizontalAlign horizontalAlign) noexcept {
        this->createInlineLabel();

        this->pLabel->setHorizontalAlign(horizontalAlign);
    }

    densityPixel_t Label::getOptimalHeight(densityPixel_t width) noexcept {
        this->createInlineLabel();
        return toVerticalDp(this->pLabel->getHeight(width));
    }

    densityPixel_t Label::getOptimalWidth(densityPixel_t height) noexcept {
        this->createInlineLabel();
        return toHorizontalDp(this->pLabel->getWidth(height));
    }
}