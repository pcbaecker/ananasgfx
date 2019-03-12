#ifndef UI_TEXTBUTTON_H
#define UI_TEXTBUTTON_H

#include "Button.hpp"

namespace ui {

    class TextButton : public Button {
    public:
        void setText(std::string text) noexcept;
        const std::string& getText() const noexcept;

    private:
        std::string mText;
    };

}

#endif