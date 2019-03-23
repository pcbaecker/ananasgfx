#ifndef UI_TEXTBUTTON_H
#define UI_TEXTBUTTON_H

#include "Button.hpp"

namespace d2 {
    class Label;
}

namespace ui {

    class TextButton : public Button {
    public:
        bool init() noexcept override;

        void setSize(float x, float y) noexcept override;

        void setText(std::string text) noexcept;
        const std::string& getText() const noexcept;

    protected:
        virtual d2::Label* getLabel() noexcept = 0;

    private:
        std::string mText;
        d2::Label* pLabel = nullptr;
    };

}

#endif