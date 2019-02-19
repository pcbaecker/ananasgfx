#ifndef PLATFORM_ANDROID_ANDROIDWINDOW_H
#define PLATFORM_ANDROID_ANDROIDWINDOW_H
#ifdef __ANDROID__

#include <EGL/egl.h>

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

    private:
        EGLSurface pSurface = nullptr;
        EGLContext pContext = nullptr;
        EGLDisplay pDisplay = nullptr;
    };

}

#endif
#endif