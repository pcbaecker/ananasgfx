#ifdef __ANDROID__

#include <android/configuration.h>
#include <native_app_glue/android_native_app_glue.h>
#include <glm/gtc/matrix_transform.hpp>

#include <ee/Log.hpp>
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
        EGLint w, h, dummy, format, hdpi;
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

        // Query the DPI of the surface
        AConfiguration* tmpConfig = AConfiguration_new();
        AConfiguration_fromAssetManager(tmpConfig, pAndroidApp->activity->assetManager);
        this->mHorizontalDpi = AConfiguration_getDensity(tmpConfig);
        this->mVerticalDpi = this->mHorizontalDpi;
        AConfiguration_delete(tmpConfig);

        // Update camera
        this->mCamera.updateWindow(this);
        this->mProjection2dMatrix = glm::ortho(0.0f, static_cast<float>(this->mWidth), static_cast<float>(this->mHeight), 0.0f);

        // Make this window the current context
        this->makeContext();

        // Window successfully created
        ee::Log::log(ee::LogLevel::Info, "", __PRETTY_FUNCTION__, "Window created", {
                ee::Note("Width", this->mWidth),
                ee::Note("Height", this->mHeight),
                ee::Note("hDPI", this->mHorizontalDpi),
                ee::Note("vDPI", this->mVerticalDpi)
        });
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

    void AndroidWindow::onTouchBegins(int id, float x, float y) noexcept {
        // Check if we already have a touch with that id
        if (this->mTouches.count(id)) {
            WARN("We already have a touch with that id", {ee::Note("Id", id)});
            return;
        }

        // Create the touch object
        this->mTouches.emplace(id, gfx::Touch(static_cast<uint8_t>(id), static_cast<double>(x), static_cast<double>(y)));

        // Propagate the touch object
        this->onTouchBegan(this->mTouches.at(id));
    }

    void AndroidWindow::onTouchMoves(int id, float x, float y) noexcept {
        // Try to find the touch object
        if (this->mTouches.count(id)) {
            auto touch = this->mTouches.at(id);
            touch.setLast(x, y);
            this->onTouchMoved(touch);
        } else {
            WARN("Could not find touch object", {ee::Note("Id", id)});
        }
    }

    void AndroidWindow::onTouchEnds(int id, float x, float y) noexcept {
        // Try to find the touch object
        if (this->mTouches.count(id)) {
            auto touch = this->mTouches.at(id);
            touch.setLast(x, y);
            this->onTouchEnded(touch);
            this->mTouches.erase(id);
        } else {
            WARN("Could not find touch object", {ee::Note("Id", id)});
        }
    }

    void AndroidWindow::handleEvents() noexcept {

    }

}

#endif