#ifndef PLATFORM_ANDROID_ANDROIDWINDOW_H
#define PLATFORM_ANDROID_ANDROIDWINDOW_H
#ifdef __ANDROID__

#include <EGL/egl.h>
#include <map>

#include <ananasgfx/gfx/Window.hpp>

namespace platform::android {

    class AndroidWindow : public ::gfx::Window {
    public:
        static struct android_app* pAndroidApp;

        AndroidWindow(const gfx::WindowConfiguration& config);

        bool init() noexcept override;

        bool shouldClose() noexcept override;

        void makeContext() noexcept override;

        void swapBuffers() noexcept override;

        void handleEvents() noexcept override;

        void onTouchBegins(int id, float x, float y) noexcept;
        void onTouchMoves(int id, float x, float y) noexcept;
        void onTouchEnds(int id, float x, float y) noexcept;

    private:
        EGLSurface pSurface = nullptr;
        EGLContext pContext = nullptr;
        EGLDisplay pDisplay = nullptr;
        std::map<int, gfx::Touch> mTouches;
    };

}

#endif
#endif