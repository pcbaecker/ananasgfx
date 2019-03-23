#ifndef UI_POPUPVIEW_H
#define UI_POPUPVIEW_H

#include <functional>

#include "Container.hpp"

namespace ui {

    class PopUpView : public Container {
    public:
        bool init() noexcept override;
        void outsideTouched() noexcept;

        void setOutsideTouchCallback(std::function<void(PopUpView*)> callback);

    private:
        d2::Node* pBackground = nullptr;
        std::function<void(PopUpView*)> mOutsideTouchCallback;
    };
}

#endif