#ifdef __ANDROID__

#include <native_app_glue/android_native_app_glue.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ananasgfx/gfx/ApplicationManager.hpp>
#include <ananasgfx/platform/android/AndroidWindow.hpp>

#define NN_LOGGER_NAME "AnanasGfx"
gfx::_internal::ApplicationManager* pApplicationManager = nullptr;
static int pfd[2];
static pthread_t thr;

/***
 *  thread func to redirect cout
 **/
static void *redirect_stdout_thread_func(void*) {
    ssize_t rdsz;
    char buf[256];
    while((rdsz = read(pfd[0], buf, sizeof buf - 1)) > 0) {
        //if(buf[rdsz - 1] == '\n') --rdsz;
        buf[rdsz - 1] = 0;  /* add null-terminator */
        __android_log_write(ANDROID_LOG_DEBUG, NN_LOGGER_NAME, buf);
    }
}

/***
 *  redirect stdcout
 **/
void redirectStdout() {
    /* make stdout line-buffered and stderr unbuffered */
    setvbuf(stdout, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);

    /* create the pipe and redirect stdout and stderr */
    pipe(pfd);
    dup2(pfd[1], 1);
    dup2(pfd[1], 2);

    // spawn the logging thread
    if(pthread_create(&thr, 0, redirect_stdout_thread_func, 0) == -1) {
        __android_log_print(ANDROID_LOG_ERROR, NN_LOGGER_NAME, "%s: Unable to create thread for redirect of stdout", __PRETTY_FUNCTION__);
        return;
    }
    pthread_detach(thr);
}

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {

}

static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: APP_CMD_SAVE_STATE", __PRETTY_FUNCTION__);
            // The system has asked us to save our current state.
            // Currently nothing will be done here, in future maybe we can continue the app at the exact same point it exited.
            return;

        case APP_CMD_INIT_WINDOW:
            __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: APP_CMD_INIT_WINDOW", __PRETTY_FUNCTION__);
            // The window (display) is ready to be used, we can begin using our application
            if (pApplicationManager == nullptr) {
                // Because the android window needs a pointer to the app struct we provide it here
                platform::android::AndroidWindow::pAndroidApp = app;

                // Create the ApplicationManager, so that it will manage creating and update of the applications
                pApplicationManager = new gfx::_internal::ApplicationManager();
            }
            return;

        case APP_CMD_TERM_WINDOW:
            __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: APP_CMD_TERM_WINDOW", __PRETTY_FUNCTION__);
            // The window is being hidden or closed, clean it up.
            //engine_term_display(engine);
            //unuse_jni(app);
            return;

        case APP_CMD_GAINED_FOCUS:
            __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: APP_CMD_GAINED_FOCUS", __PRETTY_FUNCTION__);
            // When our app gains focus, we restart animation
            return;

        case APP_CMD_LOST_FOCUS:
            __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: APP_CMD_LOST_FOCUS", __PRETTY_FUNCTION__);
            // When our app loses focus, we stop animation
            return;
    }
}

void android_main(struct android_app* state) {
    __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: Start initializing", __PRETTY_FUNCTION__);

    // Redirect the std::cout and std::cerr to android-logcat
    redirectStdout();

    // Register the command and event listener
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;

    __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: Enter main loop", __PRETTY_FUNCTION__);
    while (1) {


        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(pApplicationManager != nullptr ? 0 : -1, NULL, &events, (void**)&source)) >= 0) {
            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // Seems to be never called, but tutorial recommends to do it
            if (state->destroyRequested != 0) {
                __android_log_print(ANDROID_LOG_INFO, NN_LOGGER_NAME, "%s: Leaving main loop", __PRETTY_FUNCTION__);
                return;
            }
        }

        if (pApplicationManager != nullptr) {
            pApplicationManager->tick();
        }
    }
}

#endif