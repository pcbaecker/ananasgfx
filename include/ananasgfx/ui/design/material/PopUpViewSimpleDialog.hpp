#ifndef UI_DESIGN_MATERIAL_POPUPVIEWSIMPLEDIALOG_H
#define UI_DESIGN_MATERIAL_POPUPVIEWSIMPLEDIALOG_H

#include "PopUpView.hpp"

namespace ui {
    class Label;
}

namespace ui::design::material {

    class PopUpViewSimpleDialog : public PopUpView {
    public:
        bool init() noexcept override;

        void setTitle(std::string title) noexcept;
        void setText(std::string text) noexcept;
        void setButtonLeft(std::string text) noexcept;
        void setButtonRight(std::string text) noexcept;

    private:
        std::string mTitle;
        std::string mText;
        std::string mButtonLeft;
        std::string mButtonRight;

        ui::Label* pTitle = nullptr;
    };
}

#endif