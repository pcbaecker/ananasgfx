#include <ananasgfx/ui/design/material/ListItemSimpleText.hpp>
#include <ananasgfx/ui/design/material/MaterialDesign.hpp>
#include <ee/Log.hpp>

namespace ui::design::material {

    bool ListItemSimpleText::init() noexcept {
        if (this->pLabel == nullptr) {
            this->pLabel = createChild<ui::Label>();
            this->pLabel->setText(this->mText);
            this->pLabel->setFontSize(16);
            this->pLabel->setColor(MaterialDesign::getInstance().getTextColor());
            if (!this->pLabel->setFont(
                    MaterialDesign::getInstance().getFontFamily(),
                    MaterialDesign::getInstance().getFontSubMedium())) {
                WARN("Could not set font", {
                    ee::Note("FontFamily", MaterialDesign::getInstance().getFontFamily()),
                    ee::Note("FontSubFamily", MaterialDesign::getInstance().getFontSubMedium())
                });
                return false;
            }
        }
        return ui::ListItem::init();
    }

    densityPixel_t ListItemSimpleText::getHeight() noexcept {
        return 48;
    }

    std::optional<d2::Node *> ListItemSimpleText::getBackgroundBlur() noexcept {
        return {};
    }

    std::optional<d2::Node *> ListItemSimpleText::getBackgroundFocus() noexcept {
        auto bg = createChild<d2::Rectangle>();
        bg->setColor(MaterialDesign::getInstance().getPrimaryColor());
        return bg;
    }

    void ListItemSimpleText::setText(std::string text) noexcept {
        this->mText = std::move(text);
    }
}