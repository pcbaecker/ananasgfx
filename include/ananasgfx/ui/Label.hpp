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

    private:
        void createInlineLabel() noexcept;

    private:
        d2::Label* pLabel = nullptr;
    };

}

#endif