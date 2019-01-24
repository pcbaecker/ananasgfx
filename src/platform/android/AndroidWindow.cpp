#ifdef __ANDROID__

#include <iostream>
#include <native_app_glue/android_native_app_glue.h>
#include <glm/gtc/matrix_transform.hpp>

#include <ananasgfx/platform/android/AndroidWindow.hpp>

namespace platform::android {

    struct android_app* AndroidWindow::pAndroidApp = nullptr;

    AndroidWindow::AndroidWindow(const gfx::WindowConfiguration& config) : ::gfx::Window(config) {

    }

    bool AndroidWindow::init() noexcept {
        if (pAndroidApp == nullptr) {
            std::cerr << __PRETTY_FUNCTION__ << ": AndroidApp pointer must not be null" << std::endl;
            return false;
        }


        /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
        const EGLint attribs[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_BLUE_SIZE, 5,
                EGL_GREEN_SIZE, 6,
                EGL_RED_SIZE, 5,
                EGL_DEPTH_SIZE, 16,
                EGL_STENCIL_SIZE, 8,
                EGL_NONE
        };
        EGLint w, h, dummy, format;
        EGLint numConfigs;
        EGLConfig config;


        this->pDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(this->pDisplay, 0, 0);

        /* Here, the application chooses the configuration it desires. In this
         * sample, we have a very simplified selection process, where we pick
         * the first EGLConfig that matches our criteria */
        eglChooseConfig(this->pDisplay, attribs, &config, 1, &numConfigs);

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib(this->pDisplay, config, EGL_NATIVE_VISUAL_ID, &format);

        ANativeWindow_setBuffersGeometry(pAndroidApp->window, 0, 0, format);

        const EGLint attrib_list [] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        this->pSurface = eglCreateWindowSurface(this->pDisplay, config, pAndroidApp->window, NULL);
        this->pContext = eglCreateContext(this->pDisplay, config, NULL, attrib_list);



        eglQuerySurface(this->pDisplay, this->pSurface, EGL_WIDTH, &w);
        this->mWidth = w;
        eglQuerySurface(this->pDisplay, this->pSurface, EGL_HEIGHT, &h);
        this->mHeight = h;

        // Update camera
        this->mCamera.updateWindow(this);
        this->mProjection2dMatrix = glm::ortho(0.0f, static_cast<float>(this->mWidth), static_cast<float>(480.0f), 0.0f);

        // Make this window the current context
        this->makeContext();

/*
    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;*/

        // Initialize GL state.
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
        //glEnable(GL_CULL_FACE);
        //glShadeModel(GL_SMOOTH);
        //glDisable(GL_DEPTH_TEST);

        //glClearColor(1.0f, 0.0f, 0.0f, 1.0);
        //glClear(GL_COLOR_BUFFER_BIT);

        return true;
    }

    bool AndroidWindow::shouldClose() noexcept {
        return false;
    }

    void AndroidWindow::makeContext() noexcept {
        if (eglMakeCurrent(this->pDisplay, this->pSurface, this->pSurface, this->pContext) == EGL_FALSE) {
            std::cerr << __PRETTY_FUNCTION__ << ": Unable to make this the current context" << std::endl;
        }
    }

    void AndroidWindow::swapBuffers() noexcept {
        eglSwapBuffers(this->pDisplay, this->pSurface);
    }

}

#endif