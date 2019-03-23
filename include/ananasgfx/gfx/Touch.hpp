#ifndef GFX_TOUCH_H
#define GFX_TOUCH_H

#include <cstdint>
#include <functional>
#include <glm/glm.hpp>
#include <map>
#include <list>

namespace d2 {
    class Node;
}

namespace gfx {

    /**
     * @brief Holds information about a touch.
     */
    class Touch {
    public:

        /**
         * @brief Defines the different types of touch events.
         */
        enum Type {Begin = 0, Move = 1, End = 2};

        /**
         * @brief Constructor.
         *
         * @param id The touch id.
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         */
        Touch(uint8_t id, double x, double y) noexcept;

        /**
         * @brief Returns the last x coordinate.
         *
         * @return The last X-Coordinate.
         */
        double getLastX() const noexcept;

        /**
         * @brief Returns the last y coordinate.
         *
         * @return The last Y-Coordinate.
         */
        double getLastY() const noexcept;

        /**
         * @brief Set move coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         */
        void move(double x, double y) noexcept;

        /**
         * @brief Set end coordinates.
         *
         * @param x The X-Coordinate.
         * @param y The Y-Coordinate.
         */
        void end(double x, double y) noexcept;

        /**
         * @brief Converts the last coordinates to local coordinates of the given node.
         *
         * @param node The node where we want the local coordinates.
         * @return The local coordinates.
         */
        glm::vec2 getLocalLast(d2::Node* node) const noexcept;

        /**
         * @brief Registers a handler.
         *
         * @param type The type we want to handle.
         * @param callback The handler callback.
         */
        void registerHandler(Type type, std::function<void(Touch&)> callback) noexcept;

    private:
        /**
         * @brief The start x coordinate.
         */
        double mStartX = 0.0f;

        /**
         * @brief The start y coordinate.
         */
        double mStartY = 0.0f;

        /**
         * @brief The last x coordinate.
         */
        double mLastX = 0.0f;

        /**
         * @brief The last y coordinate.
         */
        double mLastY = 0.0f;

        /**
         * @brief The touch id.
         */
        uint8_t mId = 0;

        /**
         * @brief This map contains the handlers for the different types.
         */
        std::map<Type,std::list<std::function<void(Touch&)>>> mCallbacks;
    };
}

#endif