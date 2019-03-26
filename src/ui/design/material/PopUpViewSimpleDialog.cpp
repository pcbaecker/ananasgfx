#include <ananasgfx/ui/design/material/PopUpViewSimpleDialog.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>
#include <ananasgfx/ui/design/material/ButtonFlat.hpp>
#include <ananasgfx/ui/Label.hpp>
#include <ananasgfx/ui/layout/HorizontalLinear.hpp>

namespace ui::design::material {

    bool PopUpViewSimpleDialog::init() noexcept {
        // Title
        this->pTitle = createChild<ui::Label>();
        this->pTitle->setVerticalAlign(gfx::VerticalAlign::Middle);
        this->pTitle->setHorizontalAlign(gfx::HorizontalAlign::Left);
        this->pTitle->setText(this->mTitle);
        this->pTitle->setFontSize(21);
        this->pTitle->setColor(MaterialDesign::getInstance().getTextColor());
        if (!this->pTitle->setFont(
                MaterialDesign::getInstance().getFontFamily(),
                MaterialDesign::getInstance().getFontSubBold())) {
            WARN("Could not set title font", {
                ee::Note("FontFamily", MaterialDesign::getInstance().getFontFamily()),
                ee::Note("FontSub", MaterialDesign::getInstance().getFontSubBold())
            });
            return false;
        }

        // Text
        auto text = createChild<ui::Label>();
        text->setMultiline(true);
        text->setVerticalAlign(gfx::VerticalAlign::Middle);
        text->setHorizontalAlign(gfx::HorizontalAlign::Left);
        text->setText(this->mText);
        text->setFontSize(16);
        text->setColor(MaterialDesign::getInstance().getMediumTextColor());
        if (!text->setFont(
                MaterialDesign::getInstance().getFontFamily(),
                MaterialDesign::getInstance().getFontSubMedium())) {
            WARN("Could not set title font", {
                ee::Note("FontFamily", MaterialDesign::getInstance().getFontFamily()),
                ee::Note("FontSub", MaterialDesign::getInstance().getFontSubMedium())
            });
            return false;
        }

        // Buttons
        auto btns = createChild<ui::Container>();
        btns->createLayout<ui::layout::HorizontalLinear>();

        // ButtonLeft
        auto btnLeft = btns->createChild<ui::design::material::ButtonFlat>();
        btnLeft->setText(this->mButtonLeft);

        // ButtonRight
        auto btnRight = btns->createChild<ui::design::material::ButtonFlat>();
        btnRight->setText(this->mButtonRight);

        return PopUpView::init();
    }

    void PopUpViewSimpleDialog::setTitle(std::string title) noexcept {
        this->mTitle = std::move(title);

        if (this->pTitle) {
            this->pTitle->setText(this->mTitle);
        }
    }

    void PopUpViewSimpleDialog::setText(std::string text) noexcept {
        this->mText = std::move(text);
    }

    void PopUpViewSimpleDialog::setButtonLeft(std::string text) noexcept {
        this->mButtonLeft = std::move(text);
    }

    void PopUpViewSimpleDialog::setButtonRight(std::string text) noexcept {
        this->mButtonRight = std::move(text);
    }
}