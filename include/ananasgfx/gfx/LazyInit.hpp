#ifndef GFX_LAZYINIT_H
#define GFX_LAZYINIT_H

namespace gfx {

    class Node;

    template<class T> class LazyInit {
    public:
        explicit LazyInit(T* pointer) noexcept : mPointer(pointer) {
            static_assert(std::is_base_of<gfx::Node, T>::value, "Must derive from gfx::Node");
        }

        LazyInit(LazyInit&& lazyInit) noexcept {
            // Get the pointer from the moved instance
            this->mPointer = lazyInit.mPointer;

            // Disengange the moved instance by nulling the pointer
            lazyInit.mPointer = nullptr;
        }

        virtual ~LazyInit() noexcept {
            if (this->mPointer && !this->mPointer->isInitialized()) {
                if (!this->mPointer->init()) {
                    WARN("Could not init gfx::Node", {});
                    // TODO handle this case
                }
            }
        }

        T* get() const noexcept {
            return this->mPointer;
        }

    private:
        T* mPointer;
    };

}

#endif