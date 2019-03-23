#ifndef UI_DESIGN_MATERIAL_MATERIALDESIGN_
#define UI_DESIGN_MATERIAL_MATERIALDESIGN_

#include <glm/glm.hpp>
#include <string>

namespace ui::design::material {

    class MaterialDesign {
    public:
        static MaterialDesign& getInstance() noexcept;

        const glm::vec4& getPrimaryColor() const noexcept;
        void setPrimaryColor(const glm::vec4& color) noexcept;

        const glm::vec4& getSecondaryColor() const noexcept;
        void setSecondaryColor(const glm::vec4& color) noexcept;

        const glm::vec4& getTextColor() const noexcept;
        void setTextColor(const glm::vec4& color) noexcept;

        const glm::vec4& getMediumTextColor() const noexcept;
        void setMediumTextColor(const glm::vec4& color) noexcept;

        const glm::vec4& getDisabledTextColor() const noexcept;
        void setDisabledTextColor(const glm::vec4& color) noexcept;

        const std::string& getFontFamily() const noexcept;
        void setFontFamily(std::string fontFamily) noexcept;

        const std::string& getFontSubBold() const noexcept;
        void setFontSubBold(std::string sub) noexcept;

        const std::string& getFontSubMedium() const noexcept;
        void setFontSubMedium(std::string sub) noexcept;

    private:
        MaterialDesign() noexcept;

    private:
        static MaterialDesign INSTANCE;
        glm::vec4 mPrimaryColor;
        glm::vec4 mSecondaryColor;
        glm::vec4 mTextColor;
        glm::vec4 mMediumTextColor;
        glm::vec4 mDisabledTextColor;
        std::string mFontFamily;
        std::string mFontSubBold;
        std::string mFontSubMedium;
    };

}

#endif