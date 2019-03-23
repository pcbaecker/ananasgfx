#include <ananasgfx/ui/design/material/MaterialDesign.hpp>

namespace ui::design::material {

    MaterialDesign MaterialDesign::INSTANCE;

    MaterialDesign::MaterialDesign() noexcept :
    mPrimaryColor(0.384f, 0.0f, 0.933f, 1.0f),
    mSecondaryColor(0.012f, 0.855f, 0.773f, 1.0f),
    mTextColor(0.0f, 0.0f, 0.0f, 0.87f),
    mMediumTextColor(0.0f, 0.0f, 0.0f, 0.6f),
    mDisabledTextColor(0.0f, 0.0f, 0.0f, 0.38f),
    mFontFamily("Roboto"),
    mFontSubMedium("Medium"),
    mFontSubBold("Bold") {

    }

    MaterialDesign &MaterialDesign::getInstance() noexcept {
        return INSTANCE;
    }

    const glm::vec4 &MaterialDesign::getPrimaryColor() const noexcept {
        return this->mPrimaryColor;
    }

    void MaterialDesign::setPrimaryColor(const glm::vec4 &color) noexcept {
        this->mPrimaryColor = color;
    }

    const glm::vec4 &MaterialDesign::getSecondaryColor() const noexcept {
        return this->mSecondaryColor;
    }

    void MaterialDesign::setSecondaryColor(const glm::vec4 &color) noexcept {
        this->mSecondaryColor = color;
    }

    const glm::vec4 &MaterialDesign::getTextColor() const noexcept {
        return this->mTextColor;
    }

    void MaterialDesign::setTextColor(const glm::vec4 &color) noexcept {
        this->mTextColor = color;
    }

    const glm::vec4 &MaterialDesign::getMediumTextColor() const noexcept {
        return this->mMediumTextColor;
    }

    void MaterialDesign::setMediumTextColor(const glm::vec4 &color) noexcept {
        this->mMediumTextColor = color;
    }

    const glm::vec4 &MaterialDesign::getDisabledTextColor() const noexcept {
        return this->mDisabledTextColor;
    }

    void MaterialDesign::setDisabledTextColor(const glm::vec4 &color) noexcept {
        this->mDisabledTextColor = color;
    }

    const std::string &MaterialDesign::getFontFamily() const noexcept {
        return this->mFontFamily;
    }

    void MaterialDesign::setFontFamily(std::string fontFamily) noexcept {
        this->mFontFamily = std::move(fontFamily);
    }

    const std::string &MaterialDesign::getFontSubBold() const noexcept {
        return this->mFontSubBold;
    }

    void MaterialDesign::setFontSubBold(std::string sub) noexcept {
        this->mFontSubBold = std::move(sub);
    }

    const std::string &MaterialDesign::getFontSubMedium() const noexcept {
        return this->mFontSubMedium;
    }

    void MaterialDesign::setFontSubMedium(std::string sub) noexcept {
        this->mFontSubMedium = std::move(sub);
    }
}