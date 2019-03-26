#ifndef UI_LABEL_H
#define UI_LABEL_H

#include <ananasgfx/d2/Label.hpp>
#include "Node.hpp"

namespace ui {

    class Label : public Node {
    public:
        bool init() noexcept override;

        void setSize(float x, float y) noexcept override;
        bool setFont(const std::string& fontFamily, const std::string& fontSubFamily) noexcept;
        void setText(std::string text) noexcept;
        void setFontSize(font::size_t fontSize) noexcept;
        void setColor(const glm::vec4& color) noexcept;
        void setMultiline(bool value) noexcept;
        void setVerticalAlign(gfx::VerticalAlign verticalAlign) noexcept;
        void setHorizontalAlign(gfx::HorizontalAlign horizontalAlign) noexcept;

        densityPixel_t getOptimalHeight(densityPixel_t width) noexcept override;

        densityPixel_t getOptimalWidth(densityPixel_t height) noexcept override;

    private:
        void createInlineLabel() noexcept;

    private:
        d2::Label* pLabel = nullptr;
    };

}

#endif