#include <ananasgfx/gfx/Touch.hpp>
#include <ananasgfx/d2/Node.hpp>

namespace gfx {

    Touch::Touch(uint8_t id, double x, double y) noexcept :
    mId(id), mStartX(x), mStartY(y), mLastX(x), mLastY(y) {

    }

    double Touch::getLastX() const noexcept {
        return this->mLastX;
    }

    double Touch::getLastY() const noexcept {
        return this->mLastY;
    }

    void Touch::move(double x, double y) noexcept {
        this->mLastX = x;
        this->mLastY = y;

        if (this->mCallbacks.count(Type::Move)) {
            for (auto& callback : this->mCallbacks[Type::Move]) {
                callback(*this);
            }
        }
    }

    void Touch::end(double x, double y) noexcept {
        this->mLastX = x;
        this->mLastY = y;

        if (this->mCallbacks.count(Type::End)) {
            for (auto& callback : this->mCallbacks[Type::End]) {
                callback(*this);
            }
        }
    }

    glm::vec2 Touch::getLocalLast(d2::Node *node) const noexcept {
        auto screen = node->getScreenPosition();
        return {
            this->mLastX - screen.x + node->getAnchorPoint().x * node->getSize().x,
            this->mLastY - screen.y + node->getAnchorPoint().y * node->getSize().y};
    }

    void Touch::registerHandler(Touch::Type type, std::function<void(Touch &)> callback) noexcept {
        this->mCallbacks[type].push_back(callback);
    }
}